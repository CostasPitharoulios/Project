#include "readingFunctions.hpp"
#include <iostream>
#include <fstream>
#include <vector>

#include "Curve.hpp"
#include "../Point.hpp"

using namespace std;



vector<Curve*>* makeVectorFromData(string path){
    //=======================================================================================================
    //      *** CREATING A VECTOR OF CLASS CURVES ***
    // Info: We are going to make a vector of Curve classes. So its item of vector will include a curve
    //=======================================================================================================
    
    vector<Curve*>* listOfCurves = new vector<Curve*>;  // creating a pointer to vector of pointers to curves
    Curve *aCurve;
    Point *aPoint;
    
    
    //=======================================================================================================
    //      *** OPEN FILE with DATA AND CREATE A LIST OF CURVE CLASSES ***
    //  Info: We are going to create a list of curve classes. Each class is going to have  the id of the curve
    // and a vector with all the points of the curved stored inside and
    //=======================================================================================================
    
    
    // Opening dataSet file
    ifstream dataSet;
    dataSet.open(path);
    if (!dataSet){
        cerr << "ERROR: Unable to open file with path:" << path << "\n";
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
        listOfCurves->push_back(aCurve);    //!!! pushing new object at the end of the list
        
        
        dataSet >> word;                        // reading second word -> number of coordinates
        int numberOfCords = std::stoi(word);    // storing number of cords
        cout << "number of coordinates is: " << numberOfCords << "\n";
        
        float x,y;
        for (int i=0; i< numberOfCords; i++){   // reading each coordinate
            
            dataSet >> word;
            sscanf(word.c_str(), "(%f, %f)", &x, &y);       // storing x and y Coordinates in separete variables
            
            aPoint = new Point();                 // creating new Point for curve
            aPoint->setX(x);                       // storing x in new Point
            aPoint->setY(y);                        //storing y in new Point
            
            aCurve->PushToVector(aPoint);          // pushes newPoint to vector of points of curve object
            
        }
        
        
    }
    
    return listOfCurves;
    
}
