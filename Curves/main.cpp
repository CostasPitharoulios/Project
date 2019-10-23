#include <iostream>
#include <fstream>
#include <vector>

#include "Curve.hpp"
#include "../Point.hpp"
#include "readingFunctions.hpp"
#include "DTW.hpp"
/*#include "curveHashing.hpp"*/
#include "Grid.hpp"
#include "LSHC.hpp"

using namespace std;

int main(){
    
    //=======================================================================================================
    //      *** BEGINNING OF GETTING INFO FROM USER ***
    //=======================================================================================================
#if 0
    string dataSetPath;     // stores the data to dataSet
    
    // getting the path for dataset
    cout << "Hello! Please give path to dataset\n ";
    getline(cin, dataSetPath);  // storing path to dataSet
    cout << "The path you gave for dataset file is: " << dataSetPath << "\n";
    
    // getting the type of algorith for curve searching
    string curveSearchingAlgorithm;
    cout << "Now please give the algorithm you want for curve searching (1 or 2)\n";
    getline(cin, curveSearchingAlgorithm);
    while (curveSearchingAlgorithm != "1" && curveSearchingAlgorithm !="2"){
        cout << "You should give 1 or 2.Try again with 1 or 2:\n";
        getline(cin, curveSearchingAlgorithm);
    }
    cout << "You chose  curve searching algorithm: " << curveSearchingAlgorithm << "\n" ;
    
    // getting LSH or Hypercube
    string vectorSearchingAlgorithm;
    cout << "Now please give the algorithm you want for vector searching (LSH or Hypercube)";
    getline(cin, vectorSearchingAlgorithm);
    while (vectorSearchingAlgorithm != "LSH" && vectorSearchingAlgorithm !="Hypercube"){
        cout << "You should give LSH or Hypercube.Try again typing LSH or Hypercube:\n";
        getline(cin, vectorSearchingAlgorithm);
    }
    cout << "You chose vector searching algorithm: " << vectorSearchingAlgorithm << "\n" ;
    
    // getting path to query file (arxeio anazhthshs)
    string queryFile;
    cout << "Now please give the path to query file\n";
    getline(cin, queryFile);
    cout << "The path you gave for query file is:  " << queryFile << "\n" ;
    
    // getting path to output file
    string outputFile;
    cout << "Now please give the path to output file\n";
    getline(cin, outputFile);
    cout << "The path you gave for output file is:  " << outputFile << "\n" ;
#endif
    

    string dataSetPath = "mydataset1.txt";
    string queryFilePath = "myquery1.txt";
    
    //=======================================================================================================
    //      *** END OF INFO FROM USER ***
    //=======================================================================================================
    

    //=======================================================================================================
    //      *** CREATING A VECTOR OF CLASS CURVES FOR DATASET***
    // Info: We are going to make a vector of Curve classes. So its item of the vector will include a curve
    //=======================================================================================================
    vector<Curve*>* listOfInputCurves;           // this is a pointer to list of curves
    listOfInputCurves = makeVectorFromData(dataSetPath);     // returns the pointer to list of curves
    // JUST PRINTING ALL CURVES AND THEIR Coordinates to check if everything is  fine
    cout << "Printing all vector curve ids\n";
    for(vector<Curve*>::iterator i = listOfInputCurves->begin(); i != listOfInputCurves->end(); i++)
    {
        cout << (*i)->getId() << endl;
        cout << "COORDINATES OF THIS CURVE\n";
        (*i)->DisplayVectorContents();
    }


    //=======================================================================================================
    //      *** CREATING A VECTOR OF CLASS CURVES FOR QUERY CURVES ***
    // Info: We are going to make a vector of Curve classes. So its item of the vector will include a curve
    //=======================================================================================================
    
    vector<Curve*>* listOfQueryCurves;           // this is a pointer to list of curves
    listOfQueryCurves = makeVectorFromData(queryFilePath);     // returns the pointer to list of curves
    // JUST PRINTING ALL CURVES AND THEIR Coordinates to check if everything is  fine
    cout << "Printing all vector  QUERY curve ids\n";
    for(vector<Curve*>::iterator i = listOfQueryCurves->begin(); i != listOfQueryCurves->end(); i++)
    {
        cout << (*i)->getId() << endl;
        cout << "COORDINTES OF THIS CURVE\n";
        (*i)->DisplayVectorContents();
    }

    //=======================================================================================================
    //      *** DYNAMIC PRGRAMMING: CREATING ARRAY TO FIND DTW FOR EACH QUERY CURVE***
    // Info:
    //=======================================================================================================
    
    for(vector<Curve*>::iterator queryCurve = listOfQueryCurves->begin(); queryCurve != listOfQueryCurves->end(); queryCurve++){ // for each query curve
        
        for(vector<Curve*>::iterator inputCurve = listOfInputCurves->begin(); inputCurve != listOfInputCurves->end(); inputCurve++){ // for each input curve
            double  valueDTW = getValueDTW(queryCurve, inputCurve);
            
            cout << "\n\nDTW= " << valueDTW << "\n";
        }
        
    }

    //=======================================================================================================
    //      *** HASHING: Going to take all curves and calculate a vector which express them ***
    // Info:
    //=======================================================================================================
    
   /* for(vector<Curve*>::iterator queryCurve = listOfQueryCurves->begin(); queryCurve != listOfQueryCurves->end(); queryCurve++){
        Curve* aCurve;
        aCurve = curveHashing(queryCurve);
        //cout << "Displaying vector contents: \n";
        //aCurve->DisplayVectorContents();
        
    }*/
    
    LSHC* newLSHC;
    newLSHC = new LSHC(0.5,2);
    newLSHC->readData(queryFilePath);
    
    Curve* testCurve;
    testCurve = new Curve;
    
    
    
    
    
    
    
    
    return 0;
    
}
