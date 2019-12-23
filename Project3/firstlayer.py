import numpy as np
from keras.models import Model
from keras.models import load_model
from numpy import genfromtxt

if __name__ == "__main__":

    # Load Pretrained model
    model = load_model('WindDenseNN.h5')
    model.compile(optimizer='rmsprop', loss='mse')

    # TODO read file names from cmd
    inputFile = 'nn_representations.csv'
    # Read x_test
    x_test = genfromtxt(inputFile, delimiter=',')

    # Delete id column
    x_test = np.delete(x_test,0,1)


    # Create new model that consists of only the dense_1 layer
    model_new = Model(input=model.layers[0].input, 
                      output=model.layers[0].output)
    model_new.compile(optimizer='rmsprop', loss='mse')

    model_new.summary()


    # Predict 64 diemsional output
    y_pred = model_new.predict(x_test)
    #print(y_pred.shape)
    
    outputFile="d64.csv"

    # Read timestamps
    fp = open(inputFile, 'r')
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
