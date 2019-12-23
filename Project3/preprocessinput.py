import numpy as np
import getopt, sys
import warnings
from keras.models import Model
from keras.models import load_model
from numpy import genfromtxt

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


    # Read data
    x_test = genfromtxt(inputFile, delimiter=',')

    # Delete timestamps
    x_test = np.delete(x_test,0,1)

    # Read timestamps in string format
    fp = open(inputFile, 'r')
    line = fp.readline()
    timestamps = list()
    while line:
        timestamps.append(line.split(',')[0].replace(' ','-'))
        line = fp.readline()
    fp.close()
    
    # Concatinate timestamps with dataset
    results = np.concatenate((np.array(timestamps).reshape(len(timestamps),1),x_test),axis=1)
    

    f = open(outputFile, "w")
    f.write("vectors\n")
    f.close()

    # Write predicitons to file
    f = open(outputFile, "ab")
    np.savetxt(f,results,delimiter='\t',fmt='%s')
    f.close()

    print("New dataset written in file " + outputFile)
