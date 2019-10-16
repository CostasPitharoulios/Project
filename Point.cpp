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
    x = X;
}

void Point::setY(double Y){
    y = Y;
}


double Point::getX(void){
    return x;
}


double Point::getY(void){
    return y;
}
