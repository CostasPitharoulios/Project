#include <iostream>
#include "Point.hpp"

using namespace std;

Point::Point(){
    printf("Point was created\n");
}

Point::~Point(){
    printf("Point was destroyed\n");
}


void Point::setX(double X){
    listOfCordinates.push_back(X);
    //x = X;
}

void Point::setY(double Y){
    listOfCordinates.push_back(Y);
}


double Point::getX(void){
    return listOfCordinates[0];
}


double Point::getY(void){
    return listOfCordinates[1];
}
