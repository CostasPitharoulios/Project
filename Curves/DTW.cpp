#include "DTW.hpp"
#include "Curve.hpp"
#include <math.h>

#include <iostream>


using namespace std;


double getValueDTW(vector<Curve *>::iterator queryCurve,vector<Curve *>::iterator inputCurve){
    int m1,m2;
    m1 = (*queryCurve)->getNumberOfCoordinates(); // m1 keeps the number of coordinates of query curve
    m2 = (*inputCurve)->getNumberOfCoordinates(); // m2 keeps the number of coordinates of input curve
    
    double arrayDTW[m1][m2];
    
    
     // initialization  first line
    double previousSum = 0.0; // keeps the sum of previous items
    int x1,y1; // cordinates of first point of query curve
    x1 = (*queryCurve)->getSpecificXCoord(0);
    y1 = (*queryCurve)->getSpecificYCoord(0);
    for (int i=0; i< m2; i++){
        int x2,y2;
        x2 = (*inputCurve)->getSpecificXCoord(i);
        y2 = (*inputCurve)->getSpecificYCoord(i);
        arrayDTW[0][i] = previousSum + distance(x1,x2,y1,y2);
        
        previousSum += arrayDTW[0][i];
    }
    
    //initializing first column
    previousSum = arrayDTW[0][0];
    int x2, y2;
    x2 = (*inputCurve)->getSpecificXCoord(0);
    y2 = (*inputCurve)->getSpecificYCoord(0);
    for (int i=1; i<m1; i++){
        x1 = (*queryCurve)->getSpecificXCoord(i);
        y1 = (*queryCurve)->getSpecificYCoord(i);
        arrayDTW[i][0] = previousSum + distance(x1,x2,y1,y2);
        
        previousSum += arrayDTW[i][0];
    }
    
    for (int i=1; i<m1; i++ ){
        for (int j=1; j<m2; j++){
            x1 = (*queryCurve)->getSpecificXCoord(i);
            x2 = (*inputCurve)->getSpecificXCoord(j);
            y1 = (*queryCurve)->getSpecificYCoord(i);
            y2 = (*inputCurve)->getSpecificYCoord(j);
            arrayDTW[i][j] = min(min(arrayDTW[i-1][j],arrayDTW[i-1][j-1]), arrayDTW[i][j-1]) + distance(x1,x2,y1,y2);
        }
    }
    
    //cout << "dtw of curve is: " << arrayDTW[m1-1][m2-1];
    
    return arrayDTW[m1-1][m2-1];
    
    
}



// returns the distance between two points
double distance(float x1, float x2, float y1, float y2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}
