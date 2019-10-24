#include "Grid.hpp"
#include <iostream>
#include <limits>
#include <math.h>
#include "DTW.hpp"
#include "../Point.hpp"
#include "../dist.hpp"

using namespace std;

Grid::Grid(double delta, int d, vector<double> t):delta(delta){
    cout << "New grid : delta=" << delta << ", t1=" << t.at(0) << ", t2=" << t.at(1) << endl;
    this->t = t;
}


Curve* Grid::curveHashing(Curve *queryCurve){
    
    // first of all we need to caldulate delta
    int m1,m2;
    int coordinatesCounter = 0;
    m1 = queryCurve->getNumberOfCoordinates(); // m1 keeps the number of coordinates of query curve
    //m2 = (*inputCurve)->getNumberOfCoordinates(); // m2 keeps the number of coordinates of input curve
    
    //===============================================================================================
    //          *** SOME INFO FOR WHAT WE ARE GOING TO DO ***
    //===============================================================================================
    // we know begin to take each point of the curve
    // we divide x,y with delta and the two quotient shows as which bucket of the grid, current point belogs to
    // now we know in which bucket the points belogs to, we find the minimum of the four distances
    // between point and the points of the grid - the four corners of the bucket
    //===============================================================================================
    
    double x,y; //coordinates of a point of curve
    double previousMinX = numeric_limits<double>::min();;   // stores minX of the previous point of curve
    double previousMinY = numeric_limits<double>::min();;   // stores minY of the precious point of curve
    Point *aPoint;
    Curve* hashedCurve = new Curve();   // creating a vector to store all hashed points
    for (int i=0; i< m1; i++){
        x = queryCurve->getSpecificXCoord(i);
        y = queryCurve->getSpecificYCoord(i);
        int xStartOfBucket = (x-t.at(0))/delta;
        int yStartOfBucket = (y-t.at(1))/delta;
        
        double x1  = xStartOfBucket * delta; // x start of bucket
        double x2  = (xStartOfBucket+1) * delta; // x end of bucket
        double y1  = yStartOfBucket * delta; // y start of bucket
        double y2  = (yStartOfBucket +1) * delta; // y end of bucket
        
        double minX;      // stores the x of the bucket corner closest to point of curve
        double minY;      // stores the y of the bucket corner closest to point of curve
        
        
        if (distance(x,x1, y,y1) < distance(x,x1,y,y2)){
            minX = x1;
            minY = y1;
        }
        else{
            minX = x1;
            minY = y2;
        }
        if (distance(x, minX, y,minY) > distance(x,x2,y,y1)){
            minX = x2;
            minY = y1;
        }
        if(distance(x,minX, y,minY) > distance(x,x2,y,y2)){
            minX = x2;
            minY = y2;
        }
        
        // now we are going to check if minx,miny of the previous point of curve is the same
        // with current point's minx miny
        // if it is the same, we do not store it again. We go to the next point of curve
        
        if (minX == previousMinX && minY == previousMinY){
            //cout << "Previous had the same point\n";
            //cout << previousMinX << " " << minX << " " << previousMinY << " " << minY <<"\n";
            // cout << "Point of vector is: " << minX << "-" << minY << "\n";
        }
        else{
            
            aPoint = new Point();
            aPoint->setX(minX);
            aPoint->setY(minY);
            
            hashedCurve->PushToVector(aPoint);
            
            coordinatesCounter++;
            
            // cout << "Point of vector is: " << minX << "-" << minY << "\n";
        }
        previousMinX = minX;
        previousMinY = minY;
        
        
    }
    
    hashedCurve->setNumberOfCoordinates(coordinatesCounter);
    
    return hashedCurve;
    
    
    
}
