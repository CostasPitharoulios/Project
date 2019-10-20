#include <iostream>
#include "Point.hpp"

using namespace std;

Point::Point():d(0){
    //printf("Point was created\n");
}

Point::~Point(){
    //printf("Point was destroyed\n");
}

void Point::addCoordinate(double x){
    listOfCoordinates.push_back(x);
    d++;
}

double Point::getCoordinate(int i){
    return listOfCoordinates.at(i);
}

void Point::setId(int x){
    id = x;
}

int Point::getId(){
    return id;
}

int Point::getD(){
    return d;
}

void Point::printPoint(){
    cout << "id:" << (this->id) << "<";
    for (int i=0; i< listOfCoordinates.size(); i++)
        cout << listOfCoordinates.at(i) << ',';
    cout << ">";
}


vector<double> Point::getCoordinates(){
    return listOfCoordinates;
}

void Point::setX(double X){
    listOfCoordinates.push_back(X);
    //x = X;
}

void Point::setY(double Y){
    listOfCoordinates.push_back(Y);
}


double Point::getX(void){
    return listOfCoordinates[0];
}


double Point::getY(void){
    return listOfCoordinates[1];
}
