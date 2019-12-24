import numpy as np
import getopt, sys
import warnings
from keras.models import load_model
from sklearn.metrics import mean_squared_error, mean_absolute_error 
from numpy import genfromtxt

# Mean Absolute Percentage Error
def mape(y_true, y_pred):
    y_true = np.array(y_true)
    y_pred = np.array(y_pred)

    # Avoid division with 0
    a = []
    for i in range(len(y_true)):
        if(0 not in y_true[i]):
            a.append((y_true[i]-y_pred[i])/y_true[i])
    a = np.array(a)
    
    return np.mean(np.abs(a)) * 100

if __name__ == "__main__":
    warnings.filterwarnings("ignore")

    # Read cmd arguments
    argumentList = sys.argv[1:]
    unixOptions = "ho:i:"
    gnuOptions = ["help", "output=", "input="]

    try:
        arguments, values = getopt.getopt(argumentList, unixOptions, gnuOptions)
    except getopt.error as err:
        print (str(err))
        sys.exit(2)

    outputFile = 'output.csv'
    inputFile = 'nn_representations.csv'
    for currentArgument, currentValue in arguments:
        if currentArgument in ("-h", "--help"):
            print ("python3 evaluate.py --input='nn_representations.csv' --output='output.csv'")
        elif currentArgument in ("-o", "--output"):
            outputFile = currentValue
        elif currentArgument in ("-i", "--input"):
            inputFile = currentValue


    # Load Pretrained model
    model = load_model('WindDenseNN.h5')

    model.compile(optimizer='rmsprop', loss='mse')

    # Read x_test and delete id column
    x_test = genfromtxt(inputFile, delimiter=',')
    x_test = np.delete(x_test,0,1)

    # Make prediction
    y_pred = model.predict(x_test)

    # Read actual y_test and delete id column
    y_test = np.genfromtxt('actual.csv', delimiter=',')
    y_test = np.delete(y_test,0,1)

    mse = mean_squared_error(y_test,y_pred)
    mae = mean_absolute_error(y_test,y_pred)
    mape = mape(y_test,y_pred)

    # Write in output file
    f = open(outputFile, "w")
    f.write("MAE:"+ str(mae) +"  MAPE:"+ str(mape)+"  MSE:"+ str(mse) + "\n")
    f.close()

    # Read timestamps in string format
    fp = open('actual.csv', 'r')
    line = fp.readline()
    timestamps = list()
    while line:
        timestamps.append(line.split(',')[0])
        line = fp.readline()
    fp.close()

    # Concatinate timestamps with predictions
    results = np.concatenate((np.array(timestamps).reshape(len(timestamps),1),y_pred),axis=1)

    # Write predicitons to file
    f = open(outputFile, "ab")
    np.savetxt(f,results,delimiter=',',fmt='%s')
    f.close()

    print("Process complete successfuly. Output written in file " + outputFile)
