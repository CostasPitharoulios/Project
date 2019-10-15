#include <iostream>
using namespace std;

int main(){
    
    string dataSetPath;     // stores the data to dataSet
    
    // getting the path for dataset
    cout << "Hello! Please give path to datashet\n ";
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
    
    
    
    return 0;
    
}
