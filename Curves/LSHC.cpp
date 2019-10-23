#include <iostream>
#include <fstream>
#include <sstream>
#include "LSHC.hpp"
#include "Curve.hpp"
#include "Grid.hpp"
#include "../Point.hpp"

using namespace std;

LSHC::LSHC(double delta, int d):d(d){
    cout << "New LSH for curves bitch" << endl;
}

void LSHC::readData(string path){
    //=======================================================================================================
    //      *** CREATING A VECTOR OF CLASS CURVES ***
    // Info: We are going to make a vector of Curve classes. So its item of vector will include a curve
    //=======================================================================================================
    
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
    string line;
    while (getline(dataSet,line)){
        stringstream linestream(line);
        string id;
        string word;
        
        getline(linestream, id, '\t');
        aCurve = new Curve();                        //!!! creating a new object class
        aCurve->setId(id);                        //!!! storing id in new object
        allCurves.push_back(aCurve);    //!!! pushing new object at the end of the list
        //cout << "Id= " << id << "\n";
        
        getline(linestream, word, '\t');                    // reading second word -> number of coordinates
        //cout << "word: " << word << endl;
        int numberOfCords = std::stoi(word);    // storing number of cords
        aCurve->setNumberOfCoordinates(numberOfCords);
        //cout << "number of coordinates is: " << aCurve->getNumberOfCoordinates() << "\n";
        
        float x,y;
        for (int i=0; i< numberOfCords; i++){   // reading each coordinate
            
            getline(linestream, word, '\t');
            sscanf(word.c_str(), "(%f, %f)", &x, &y);       // storing x and y Coordinates in separete variables
            
            aPoint = new Point();                 // creating new Point for curve
            aPoint->setX(x);                       // storing x in new Point
            aPoint->setY(y);                        //storing y in new Point
            
            aCurve->PushToVector(aPoint);          // pushes newPoint to vector of points of curve object
            
        }
    }
    
    dataSet.close(); //closing opened file
}


Point* LSHC::vectorCurveToPoint(Curve* hashedCurve){
    Point* newPoint;
    newPoint= new Point();  // creating a new point to represent vector of curve
    
    int numberOfCords = hashedCurve->getNumberOfCoordinates(); //in order to know how many points there are in the vector of hashed Curve
    cout << "numerofcoors:" << numberOfCords << "\n";

    int coordinatesCounter=0;
    for(int i=0; i< numberOfCords; i++){ // adding x,y to the list of coordinates of pointer
        newPoint->addCoordinate(hashedCurve->getSpecificXCoord(i));
        newPoint->addCoordinate(hashedCurve->getSpecificYCoord(i));
        coordinatesCounter+=2;
    }
    
    return newPoint;
}

int LSHC::maxCurveLength(){
    int max = -1;
    for(vector<Curve*>::iterator it = allCurves.begin(); it != allCurves.end(); it++){
        if ( (*it)->getNumberOfCoordinates() > max )
            max = (*it)->getNumberOfCoordinates();
    }
    return max;
}

void LSHC::lshInsertAll(){
    int maxD = maxCurveLength();
    cout << "MaxD:" << maxD << endl;
    int w = 4000, k=4; //TODO arguments?
    //lsh = new LSH(w, maxD, k, 1);

    // For every Curve
    for(vector<Curve*>::iterator it = allCurves.begin(); it != allCurves.end(); it++){
        (*it)->printCoordinates();
        Point *ptr = vectorCurveToPoint(*it);
        cout << "Point of curve: ";
        ptr->printPoint();
        cout << endl;

        ptr->addPadding(d*maxD);
        cout << "Point after padding: ";
        ptr->printPoint();
        cout << endl;

        //lsh->insert( *ptr?);
    }
}
