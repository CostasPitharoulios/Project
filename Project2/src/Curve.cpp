#include <iostream>
#include "../include/Curve.hpp"
#include "../include/Point.hpp"

using namespace std;

Curve::Curve(){
    numberOfCoordinates = 0;
    cluster = nullptr;
    //id = "0";
   // vector<Point> get_listOfCoordinates;
    //printf("Curve was created\n");
}

Curve::~Curve(){

    for (int i=0; i<listOfCoordinates.size(); i++){
        delete listOfCoordinates.at(i);
    }
    //printf("Curve was destroyed\n");
}


void Curve::setId(string newId){
    id = newId;
}

string Curve::getId(void){
    return id;
}

/*vector<Point> Curve::get_listOfCoordinates(void){
    return listOfCoordinates;
}*/

void Curve::DisplayVectorContents(void){
    for( vector<Point*>::iterator i = listOfCoordinates.begin(); i != listOfCoordinates.end(); i++ )
    {
        cout << (*i)->getX() << "-" << (*i)->getY() << "\n";
    }
}

void Curve::PushToVector(Point* aPoint){
    listOfCoordinates.push_back(aPoint);
    numberOfCoordinates++;
}

void Curve::setNumberOfCoordinates(int number){
    //numberOfCoordinates = number; //TODO del
}

void Curve::setNumber(int number){
    numberOfCoordinates = number;
}

int Curve::getNumberOfCoordinates(void){
    return numberOfCoordinates;
} 
double Curve::getSpecificXCoord(int position){
    return listOfCoordinates.at(position)->getX();
}

double Curve::getSpecificYCoord(int position){
    return listOfCoordinates.at(position)->getY();
}

void Curve::setSpecificXCoord(int position, double x){
    return listOfCoordinates.at(position)->changeX(x);
}

void Curve::setSpecificYCoord(int position, double y){
    return listOfCoordinates.at(position)->changeY(y);
}

void Curve::printCoordinates(){
//    cout << "Curve Points: ";
    for(int i=0; i<listOfCoordinates.size(); i++){
        cout << "     (" << listOfCoordinates.at(i)->getX() << "," <<  listOfCoordinates.at(i)->getY() << ")";
    }    
    cout << endl;
}

void Curve::setCluster(Cluster *cluster){
    this->cluster = cluster;
}

Cluster *Curve::getCluster(){
    return this->cluster;
}

vector<Point*> Curve:: getListOfCoordinates(void){
    return listOfCoordinates;
}

void Curve::setListOfCoordinates(vector <Point*> newListOfCoordinates){
    this->listOfCoordinates = newListOfCoordinates;
}

/*Curve* Curve::copyCurve(Curve* beforeCurve){
    Curve* destCurve = new Curve;
    for (int i=0; i< beforeCurve->getListOfCoordinates().size(); i++){
        destCurve->listOfCoordinates.push_back(beforeCurve->getListOfCoordinates().at(i));
    }
    destCurve->numberOfCoordinates = beforeCurve->numberOfCoordinates;
    destCurve->cluster = beforeCurve->cluster;
}*/

Point* Curve::getSpecificPoint(int position){
    return listOfCoordinates.at(position);
}
