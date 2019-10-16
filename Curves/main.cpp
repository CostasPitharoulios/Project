#include <iostream>
#include <fstream>
#include <vector>

#include "Curve.hpp"
#include "../Point.hpp"

using namespace std;

int main(){
    
    //=======================================================================================================
    //      *** BEGINNING OF GETTING INFO FROM USER ***
    //=======================================================================================================
#if 0
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
#endif
    
    string dataSetPath = "mydataset.txt";
    
    //=======================================================================================================
    //      *** END OF INFO FROM USER ***
    //=======================================================================================================
    
    
    //=======================================================================================================
    //      *** CREATING A VECTOR OF CLASS CURVES ***
    // Info: We are going to make a vector of Curve classes. So its item of the vector will include a curve
    //=======================================================================================================
    
    vector<Curve*> listOfInputCurves;
    Curve *aCurve;
    Point *aPoint;

    
    //=======================================================================================================
    //      *** OPEN DATASET FILE AND CREATE A LIST OF CURVE CLASSES ***
    //  Info: We are going to create a list of curve classes. Each class is going to have  the id of the curve
    // and a vector with all the points of the curved stored inside and
    //=======================================================================================================
    
    
    // Opening dataSet file
    ifstream dataSet;
    dataSet.open(dataSetPath);
    if (!dataSet){
        cerr << "ERROR: Unable to open file with path:" << dataSetPath << "\n";
        exit(1);
    }

    // reading dataSet file line by line
   
    while (true){
        string word;                             // stores every single word of file
        string id;                               // stores the id of curve
        
        dataSet >> word;                         // reading first word of line (maybe id or eof)
        if ( dataSet.eof()) break;               // if this this the end of file
        
        id = word;                               // storing id
        cout << "Id= " << id << "\n";
        
        aCurve = new Curve();                        //!!! creating a new object class
        aCurve->setId(id);                        //!!! storing id in new object
        listOfInputCurves.push_back(aCurve);    //!!! pushing new object at the end of the list
        
        
        dataSet >> word;                        // reading second word -> number of coordinates
        int numberOfCords = std::stoi(word);    // storing number of cords
        cout << "number of coordinates is: " << numberOfCords << "\n";
        
        float x,y;
        for (int i=0; i< numberOfCords; i++){   // reading each coordinate
            
            dataSet >> word;
            sscanf(word.c_str(), "(%f, %f)", &x, &y);       // storing x and y cordinates in separete variables
            
            aPoint = new Point();                 // creating new Point for curve
            aPoint->setX(x);                       // storing x in new Point
            aPoint->setY(y);                        //storing y in new Point
            
            aCurve->PushToVector(aPoint);          // pushes newPoint to vector of points of curve object
           
        
        }
       
        
    }
    // JUST PRINTING ALL CURVES AND THEIR Cordinates to check if everything is  fine
    cout << "Printing all vector curve ids\n";
    for(vector<Curve*>::iterator i = listOfInputCurves.begin(); i != listOfInputCurves.end(); i++)
    {
        cout << (*i)->getId() << endl;
        cout << "COORDINTES OF THIS CURVE\n";
        (*i)->DisplayVectorContents();
    }
        
       
    
    
    
    
    
    
    
    return 0;
    
}
