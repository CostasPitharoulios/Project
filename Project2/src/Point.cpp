#include <iostream>
#include "Point.hpp"

using namespace std;

Point::Point(string id):d(0),id(id){
    //printf("Point was created\n");
    cluster = nullptr;
}

//Point::~Point(){
    //printf("Point was destroyed\n");
//}

void Point::addCoordinate(double x){
    listOfCoordinates.push_back(x);
    d++;
}

double Point::getCoordinate(int i){
    return listOfCoordinates.at(i);
}

void Point::setId(string x){
    this->id = x;
}

string Point::getId(){
    return id;
}

int Point::getD(){
    return d;
}

void Point::printPoint(){
    cout << "Id:" << (this->id) << "<";
    for (int i=0; i< listOfCoordinates.size(); i++)
        cout << listOfCoordinates.at(i) << ',';
    cout << ">";
}


vector<double> Point::getCoordinates(){
    return listOfCoordinates;
}

void Point::setCoordinates(vector<double> Coordinates){
    listOfCoordinates = Coordinates;
}

void Point::setX(double X){
    listOfCoordinates.push_back(X);
    //x = X;
}

void Point::setY(double Y){
    listOfCoordinates.push_back(Y);
}

void Point::changeX(double X){
    listOfCoordinates.at(0) = X;
}

void Point::changeY(double Y){
    //listOfCoordinates.push_back(Y);
    listOfCoordinates.at(1) = Y;
    
}



double Point::getX(void){
    return listOfCoordinates[0];
}


double Point::getY(void){
    return listOfCoordinates[1];
}

void Point::setD(int dim){
    this->d = dim;
}

void Point::addPadding(int new_d){
    int space = new_d-d;
    for (int i=0; i < space ; i++){
        addCoordinate(0);
    }
}

void Point::setCluster(Cluster *cluster){
    this->cluster = cluster;
}

Cluster *Point::getCluster(){
    return this->cluster;
}

Point* Point::copyPoint(void){
    Point* P = new Point();
    P->setD(this->getD());
    for (int i=0; i<this->getD(); i++){
        P->listOfCoordinates.push_back(this->getCoordinates().at(i));
    }
    P->setId(this->getId());
    P->setCluster(this->getCluster());
    return P;
    
}

Point* Point::dublicatePoint(void){
    Point* tempP = new Point();
    tempP->setD(this->getD());
    for (int i=0; i<this->getD(); i++){
        tempP->listOfCoordinates.push_back(this->getCoordinates().at(i));
    }
    return tempP;
}

