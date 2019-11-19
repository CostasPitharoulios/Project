#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>

#include "Curve.hpp"
#include "../Point.hpp"
#include "readingFunctions.hpp"
#include "DTW.hpp"
#include "curveHashing.hpp"
#include "LSHC.hpp"
#include "../dist.hpp"

using namespace std;


void BruteNearest(Curve *queryCurve){
    double min = numeric_limits<double>::min();;
    
    
    
    
    
}


int main(int argc,char *argv[]){
    string inputFile, outputFile, queryFile;
    int r=-1;

    // Handling arguments
    if (argc == 5 || argc == 7){
        int i;
        for(i=1 ; i<argc ; i++){
            if(!strcmp(argv[i],"-d"))
                inputFile = argv[i+1];
            if(!strcmp(argv[i],"-q"))
                queryFile = argv[i+1];
            if(!strcmp(argv[i],"-o"))
                outputFile = argv[i+1];
            if(!strcmp(argv[i],"-r"))
                r = stoi(argv[i+1]);
        }
    }
    else{
        cerr << "Wrong number of arguments" << endl;
        return 1;
    }
    
    
    LSHC lshc(0.001,2);
    cout << "Reading input file..." << endl;
    lshc.readData(inputFile);
    cout << "Reading complete." << endl;
    lshc.printAllCurves();
   // cout << "Inserting data to the hashtable..." << endl;
    //lshc.lshInsertAll();
    //cout << "Inserting complete." << endl;
    
    // >>>>>>>>>>>>>>>>>>>>
    // *** READING QUERY CURVE ***
    // >>>>>>>>>>>>>>>>>>>
    
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
    
    
    // Opening queries file
    ifstream queries;
    queries.open(queryFile);
    if (!queries){
        cerr << "ERROR: Unable to open file with path:" << queryFile << "\n";
        exit(1);
    }
    
    // reading queries file line by line
    string line;
    while (getline(queries,line)){
        stringstream linestream(line);
        string id;
        string word;
        
        getline(linestream, id, '\t');
        aCurve = new Curve();       // creating a new object class
        aCurve->setId(id);          // storing id in new object
        
        getline(linestream, word, '\t');                    // reading second word -> number of coordinates
        //cout << "word: " << word << endl;
        int numberOfCords = std::stoi(word);    // storing number of cords
        aCurve->setNumberOfCoordinates(numberOfCords);
        //cout << "number of coordinates is: " << aCurve->getNumberOfCoordinates() << "\n";
        
        double x,y;
        for (int i=0; i< numberOfCords; i++){   // reading each coordinate
            
            getline(linestream, word, ' ');
            //cout << ":::"<< word << endl;
            sscanf(word.c_str(), "(%lf,", &x);       // storing x and y Coordinates in separete variables
            
            getline(linestream, word, ' ');
            //cout << ":::"<< word << endl;
            sscanf(word.c_str(), "%lf)", &y);       // storing x and y Coordinates in separete variables
            cout << ":::x,y: " << x << ", " << y << endl;
            
            aPoint = new Point();                 // creating new Point for curve
            aPoint->setX(x);                       // storing x in new Point
            aPoint->setY(y);                        //storing y in new Point
            
            aCurve->PushToVector(aPoint);          // pushes newPoint to vector of points of curve object
            
        }
        
        // Find its nearest neighbour curve
        //BruteNearest(aCurve);
        
        
        /// *** BRUTE FOR NEAREST CURVE ***
        
        double min = numeric_limits<double>::max();;
        Curve* nearestCurve;
        vector<Curve*> listOfCurves = lshc.getAllCurves();
        for ( vector<Curve*>::iterator dataCurve = listOfCurves.begin(); dataCurve != listOfCurves.end(); dataCurve++){
            
           /* (*dataCurve)->DisplayVectorContents();
            cout << "\n\n\n" ;
            aCurve->DisplayVectorContents();*/
            double distance = getValueDTW(aCurve, (*dataCurve));
            cout << "dISTANCE IS: " << distance << "\n";
            if (distance < min){
                min = distance;
                nearestCurve = (*dataCurve);
            }
            
        }
        
        cout << "FINDING NEAREST CURVE WITH BRUT\n";
        cout << "----------------------------------\n";
        cout << "Minimum distance is: " << min << "\n";
        cout << "Id of nearest curve is: " << nearestCurve->getId() << "\n";
        
        ///////////////////////////////////////////
        break; //TODO TODO TODO TODO TODO TODO TODO
        ///////////////////////////////////////////
    }
    
    queries.close(); //closing opened file
    
    
    

    return 0;
}
