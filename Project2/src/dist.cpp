#include <cmath>
#include <iostream>
#include <vector>
#include "../include/dist.hpp"
#include "../include/Curve.hpp"

using namespace std;

double manhattanDistance(vector<double> a, vector<double> b){
    double dist = 0;
    if (a.size() != b.size())
        return -1;

    for (int i=0; i<a.size(); i++)
        dist += abs(a.at(i) - b.at(i));

    return dist;
}


double getValueDTW(Curve *queryCurve,Curve *inputCurve){
    cout << "HELLOOOOOOOOO" << endl;
    int m1,m2;
   
    m1 = queryCurve->getNumberOfCoordinates(); // m1 keeps the number of coordinates of query curve
    m2 = inputCurve->getNumberOfCoordinates(); // m2 keeps the number of coordinates of input curve

    cout << "m1 = " << m1 << " m2 = " << m2 << endl;
    
    double arrayDTW[m1][m2];
    
    
    // initialization  first line
    double previousSum = 0.0; // keeps the sum of previous items
    double x1,y1; // cordinates of first point of query curve
    x1 = queryCurve->getSpecificXCoord(0);
    y1 = queryCurve->getSpecificYCoord(0);
    for (int i=0; i< m2; i++){
        double x2,y2;
        x2 = inputCurve->getSpecificXCoord(i);
        y2 = inputCurve->getSpecificYCoord(i);
        arrayDTW[0][i] = previousSum + distance(x1,x2,y1,y2);
        
        previousSum += arrayDTW[0][i];
    }
    
    //initializing first column
    previousSum = arrayDTW[0][0];
    double x2, y2;
    x2 = inputCurve->getSpecificXCoord(0);
    y2 = inputCurve->getSpecificYCoord(0);
    for (int i=1; i<m1; i++){
        x1 = queryCurve->getSpecificXCoord(i);
        y1 = queryCurve->getSpecificYCoord(i);
        arrayDTW[i][0] = previousSum + distance(x1,x2,y1,y2);
        
        previousSum += arrayDTW[i][0];
    }
    
    for (int i=1; i<m1; i++ ){
        for (int j=1; j<m2; j++){
            x1 = queryCurve->getSpecificXCoord(i);
            x2 = inputCurve->getSpecificXCoord(j);
            y1 = queryCurve->getSpecificYCoord(i);
            y2 = inputCurve->getSpecificYCoord(j);
            arrayDTW[i][j] = min(min(arrayDTW[i-1][j],arrayDTW[i-1][j-1]), arrayDTW[i][j-1]) + distance(x1,x2,y1,y2);
        }
    }
    
    
    cout << "\n\n\nDTW ARRAY CHECK!!!!!\n\n" << endl;
    for (int i=0; i< m1; i++){
        for (int j=0; j< m2; j++){
            cout << arrayDTW[i][j] << " ";
        }
        cout << endl;
    }
    
    //cout << "dtw of curve is: " << arrayDTW[m1-1][m2-1];
    
    return arrayDTW[m1-1][m2-1];
    
}

vector <Point*> getBestTraversalDTW(Curve *queryCurve,Curve *inputCurve){
    cout << "HELLOOOOOOOOO2" << endl;
    int m1,m2;
    
    m1 = queryCurve->getNumberOfCoordinates(); // m1 keeps the number of coordinates of query curve
    m2 = inputCurve->getNumberOfCoordinates(); // m2 keeps the number of coordinates of input curve
    
    cout << "m1 = " << m1 << " m2 = " << m2 << endl;
    
    vector<Point*> setIPairs;
    
    double arrayDTW[m1][m2];
    
    // creating first point of setIPairs
    Point* aPoint = new Point();
    aPoint->setX(0.0);
    aPoint->setY(0.0);
    
    setIPairs.push_back(aPoint);
    
    cout << "SKATA" << endl;
    
    
    // initialization  first line
    double previousSum = 0.0; // keeps the sum of previous items
    double x1,y1; // cordinates of first point of query curve
    x1 = queryCurve->getSpecificXCoord(0);
    y1 = queryCurve->getSpecificYCoord(0);
    for (int i=0; i< m2; i++){
        double x2,y2;
        x2 = inputCurve->getSpecificXCoord(i);
        y2 = inputCurve->getSpecificYCoord(i);
        arrayDTW[0][i] = previousSum + distance(x1,x2,y1,y2);
        
        previousSum += arrayDTW[0][i];
    }
    
    //initializing first column
    previousSum = arrayDTW[0][0];
    double x2, y2;
    x2 = inputCurve->getSpecificXCoord(0);
    y2 = inputCurve->getSpecificYCoord(0);
    for (int i=1; i<m1; i++){
        x1 = queryCurve->getSpecificXCoord(i);
        y1 = queryCurve->getSpecificYCoord(i);
        arrayDTW[i][0] = previousSum + distance(x1,x2,y1,y2);
        
        previousSum += arrayDTW[i][0];
    }
    
    cout << "\nDTW ARRAY:" << endl;
    
    for (int i=1; i<m1; i++ ){
        for (int j=1; j<m2; j++){
            x1 = queryCurve->getSpecificXCoord(i);
            x2 = inputCurve->getSpecificXCoord(j);
            y1 = queryCurve->getSpecificYCoord(i);
            y2 = inputCurve->getSpecificYCoord(j);
            arrayDTW[i][j] = min(min(arrayDTW[i-1][j],arrayDTW[i-1][j-1]), arrayDTW[i][j-1]) + distance(x1,x2,y1,y2);
        }
    }
    
    for (int i=0; i< m1; i++){
        for (int j=0; j< m2; j++){
            cout << arrayDTW[i][j] << " ";
        }
        cout << endl;
    }
    
    
    int i = 0;
    int j = 0;
    cout << "hELLO" << endl;
    while (1){
        int min1, min2;
        int finalX, finalY;
        if (i == (m1-1) && j == (m2-1))
            break;
        else if (i == m1-1){
            min2 = arrayDTW[i][j+1];
            finalX = i;
            finalY = j+1;
        }
        else if ( j == m2-1){
            min2 = arrayDTW[i+1][j];
            finalX = i+1;
            finalY = j;
        }
        else{
            if (arrayDTW[i+1][j] < arrayDTW[i+1][j+1]){
                min1 = arrayDTW[i+1][j];
                finalX =  i+1;
                finalY =  j;
            }
            else{
                min1 = arrayDTW[i+1][j+1];
                finalX = i+1;
                finalY = j+1;
            }
            
            if (min1 < arrayDTW[i][j+1]){
                min2 = min1;
            }
            else{
                min2 = arrayDTW[i][j+1];
                finalX =  i;
                finalY =  j+1;
            }
        }
        
        i = finalX;
        j = finalY;
        
        cout << "new i: " << i << " new j: " << j << endl;
        
        Point* newPoint = new Point();
        newPoint->setX((double)finalX);
        newPoint->setY((double)finalY);
        setIPairs.push_back(newPoint);
    }
    
    //cout << "dtw of curve is: " << arrayDTW[m1-1][m2-1];
    
    //return arrayDTW[m1-1][m2-1];
    cout << "BYE" << endl;
    
    return setIPairs;
    
}

// returns the distance between two points
double distance(double x1, double x2, double y1, double y2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}
