#include <iostream>
#include <fstream>
#include <random>
#include <set>
#include <sstream>
#include "LSHC.hpp"
#include "Curve.hpp"
#include "Grid.hpp"
#include "../Point.hpp"
#include "../dist.hpp"

using namespace std;

CurveHashing::~CurveHashing(){
    //cout << "  CurveHashing destructor" << endl;
    for(int i=0; i<allCurves.size(); i++){
        delete allCurves.at(i);
    }
}

LSHC::LSHC(double delta, int d, int L):CurveHashing(delta,d,L){
    cout << "New LSHC bitch" << endl;
}

LSHC::~LSHC(){
    //cout << "  LSHC destructor" << endl;
    for (int i=0; i<lsh.size(); i++){
        delete lsh.at(i);
    }
}

HCC::HCC(double delta, int d, int L, int dd, int hd):CurveHashing(delta,d,L), dd(dd), hd(hd){
    cout << "New HCC bitch" << endl;
}

HCC::~HCC(){
    //cout << "  HCC destructor" << endl;
    for (int i=0; i<hc.size(); i++){
        delete hc.at(i);
    }
}

CurveHashing::CurveHashing(double delta, int d, int L):d(d), L(L){
    cout << "New CurveHashing bitch" << endl;
   
    random_device rd; //seed
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0,d); 

    for(int j=0; j<L; j++){
        vector<double> t;
        for (int i=0; i<d; i++){
            t.push_back(dis(gen));
        }
        Grid g_j(delta,d,t);
        grids.push_back(g_j);
    }
}

vector<Curve*> CurveHashing::getAllCurves(void){
    return allCurves;
}

void CurveHashing::readData(string path){
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
        //cout << ":::Id= " << id << "\n";
        
        getline(linestream, word, '\t');                    // reading second word -> number of coordinates
        //cout << ":::word: " << word << endl;
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
            
            aPoint = new Point();                 // creating new Point for curve
            aPoint->setX(x);                       // storing x in new Point
            aPoint->setY(y);                        //storing y in new Point
            
            aCurve->PushToVector(aPoint);          // pushes newPoint to vector of points of curve object
            
        }

        allCurves.push_back(aCurve);    // Save it to The vector
    }
    
    dataSet.close(); //closing opened file
}

void CurveHashing::readQueries(string path){
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
    queries.open(path);
    if (!queries){
        cerr << "ERROR: Unable to open file with path:" << path << "\n";
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
            //cout << ":::x,y: " << x << ", " << y << endl;
            
            aPoint = new Point();                 // creating new Point for curve
            aPoint->setX(x);                       // storing x in new Point
            aPoint->setY(y);                        //storing y in new Point
            
            aCurve->PushToVector(aPoint);          // pushes newPoint to vector of points of curve object
            
        }

        // Find its nearest neighbour curve
        nearestNeighbourCurve(aCurve);

        delete aCurve;


        ///////////////////////////////////////////
        break; //TODO TODO TODO TODO TODO TODO TODO
        ///////////////////////////////////////////
    }
    
    queries.close(); //closing opened file
}




Point* CurveHashing::vectorCurveToPoint(Curve* hashedCurve, Curve *origin){
    Point* newPoint;
    newPoint = new Point(stoi(origin->getId()));  // creating a new point to represent vector of curve with the same id as the curve
    
    int numberOfCords = hashedCurve->getNumberOfCoordinates(); //in order to know how many points there are in the vector of hashed Curve
    //cout << "numOfCoords:" << numberOfCords << "\n";

    int coordinatesCounter=0;
    for(int i=0; i< numberOfCords; i++){ // adding x,y to the list of coordinates of pointer
        newPoint->addCoordinate(hashedCurve->getSpecificXCoord(i));
        newPoint->addCoordinate(hashedCurve->getSpecificYCoord(i));
        coordinatesCounter+=2;
    }
    newPoint->setOrigin(origin);
    
    return newPoint;
}

int CurveHashing::maxCurveLength(){
    int max = -1;
    for(vector<Curve*>::iterator it = allCurves.begin(); it != allCurves.end(); it++){
        if ( (*it)->getNumberOfCoordinates() > max )
            max = (*it)->getNumberOfCoordinates();
    }
    return max;
}

void LSHC::hashAll(){
    int maxD = maxCurveLength();
    cout << "MaxD:" << maxD << endl;
    int w = 4000, k=4; //TODO arguments?


    // For every grid
    for(int i=0; i<L; i++){

        // Make an instance of lsh
        //LSH lsh_i(w, maxD, k, 1);
        lsh.push_back(new LSH(w, maxD, k, 1));

        // For every Curve
        for(vector<Curve*>::iterator it = allCurves.begin(); it != allCurves.end(); it++){
            //cout << "Initial curve:";
            //(*it)->printCoordinates();

            // Convert the curve into grid Curve
            Curve *gridCurve = grids.at(i).curveHashing(*it);
            //cout << "Grid curve:";
            //gridCurve->printCoordinates();

            // Convert the curve into a point
            Point *ptr = vectorCurveToPoint(gridCurve,*it);
            //cout << "Point of curve: ";
            //ptr->printPoint();
            //cout << endl;

            // Add padding so that all points have the same ammout of dimensions
            ptr->addPadding(d*maxD);
            //cout << "Point after padding: ";
            //ptr->printPoint();
            //cout << endl;

            // Insert it to the lsh HashTable
            lsh.at(i)->insert(*ptr);
            delete ptr;
            delete gridCurve;
        }
    }
}

void LSHC::nearestNeighbourCurve(Curve *query){
    int maxD = maxCurveLength(); //TODO if query is bigger than maxD she should get it cut i think
    //set<Curve*> nearestCurves; // Set of the nearest curves found in each grid

    //cout << "Initial curve:";
    //query->printCoordinates();

    double dist,min = numeric_limits<double>::max();   // stores minY of the precious point of curve
    Point *nn;
    for(int i=0; i<L; i++){
        // Convert the curve into grid Curve
        Curve *gridCurve = grids.at(i).curveHashing(query);
        //cout << "Grid curve:";
        //gridCurve->printCoordinates();

        // Convert the curve into a point
        Point *p = vectorCurveToPoint(gridCurve,query);
        //cout << "Point of curve: ";
        //ptr->printPoint();
        //cout << endl;

        // Add padding so that all points have the same ammout of dimensions
        p->addPadding(d*maxD);
        //cout << "Point after padding: ";
        //ptr->printPoint();
        //cout << endl;

        // Find its nearestNeighbour point using lsh
        Point *ptr = lsh.at(i)->nearestNeighbour(*p, "dtw", dist);
        cout << "Nearest curve in grids["<<i<<"] : " << ptr->getId() << endl;
        //nearestCurves.insert(nn->getOrigin());
        if (dist < min){
            min = dist;
            nn = ptr;
        }
        delete p;
        delete gridCurve;
    }

    //cout << "NEAREST OF THE NEAREST: Id:" << nn->getOrigin()->getId();
   // nn->getOrigin()->printCoordinates();
    cout << " with distance : " << min << endl;
}

void HCC::hashAll(){
    int maxD = maxCurveLength();
    cout << "MaxD:" << maxD << endl;
    int w = 4000, k=1; //TODO arguments?


    // For every grid
    for(int i=0; i<L; i++){

        // Make an instance of lsh
        //LSH lsh_i(w, maxD, k, 1);
        hc.push_back(new HC(w, maxD, k, dd, hd));

        // For every Curve
        for(vector<Curve*>::iterator it = allCurves.begin(); it != allCurves.end(); it++){
            //cout << "Initial curve:";
            //(*it)->printCoordinates();

            // Convert the curve into grid Curve
            Curve *gridCurve = grids.at(i).curveHashing(*it);
            //cout << "Grid curve:";
            //gridCurve->printCoordinates();

            // Convert the curve into a point
            Point *ptr = vectorCurveToPoint(gridCurve,*it);
            //cout << "Point of curve: ";
            //ptr->printPoint();
            //cout << endl;

            // Add padding so that all points have the same ammout of dimensions
            ptr->addPadding(d*maxD);
            //cout << "Point after padding: ";
            //ptr->printPoint();
            //cout << endl;

            // Insert it to the lsh HashTable
            hc.at(i)->insert(*ptr);
            delete ptr;
            delete gridCurve;
        }
    }
}

void HCC::nearestNeighbourCurve(Curve *query){
    int maxD = maxCurveLength(); //TODO if query is bigger than maxD she should get it cut i think
    //set<Curve*> nearestCurves; // Set of the nearest curves found in each grid

    //cout << "Initial curve:";
    //query->printCoordinates();

    double dist,min = numeric_limits<double>::max();   // stores minY of the precious point of curve
    Point *nn;
    for(int i=0; i<L; i++){
        // Convert the curve into grid Curve
        Curve *gridCurve = grids.at(i).curveHashing(query);
        //cout << "Grid curve:";
        //gridCurve->printCoordinates();

        // Convert the curve into a point
        Point *p = vectorCurveToPoint(gridCurve,query);
        //cout << "Point of curve: ";
        //ptr->printPoint();
        //cout << endl;

        // Add padding so that all points have the same ammout of dimensions
        p->addPadding(d*maxD);
        //cout << "Point after padding: ";
        //ptr->printPoint();
        //cout << endl;

        // Find its nearestNeighbour point using lsh
        Point *ptr = hc.at(i)->nearestNeighbour(*p, "dtw", dist);
        cout << "Nearest curve in grids["<<i<<"] : " << ptr->getId() << endl;
        //nearestCurves.insert(nn->getOrigin());
        if (dist < min){
            min = dist;
            nn = ptr;
        }
        delete p;
        delete gridCurve;
    }

    cout << "NEAREST OF THE NEAREST: Id:" << nn->getOrigin()->getId();
    nn->getOrigin()->printCoordinates();
    cout << " with distance : " << min << endl;
}


void CurveHashing::printAllCurves(){
    cout << "ALL CURVES:" << endl;
    for(vector<Curve*>::iterator it = allCurves.begin(); it != allCurves.end(); it++){
        cout << "numOfCoordinates: " << (*it)->getNumberOfCoordinates();
        (*it)->printCoordinates();
        cout << endl;
    }
}
