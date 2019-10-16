#include <iostream>
#include "Curve.hpp"
#include "../Point.hpp"

using namespace std;

Curve::Curve(){
    //id = "0";
   // vector<Point> get_listOfCoordinates;
    printf("Curve was created\n");
}

Curve::~Curve(){
    printf("Curve was destroyed\n");
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
}






