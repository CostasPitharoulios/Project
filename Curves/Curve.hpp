#pragma once
#include <vector>
#include <string>

#include "../Point.hpp"

using namespace std;

class Curve{
    private:
        string id;
        int numberOfCoordinates; /* TODO number and listOfPoints? */
        vector<Point*> listOfCoordinates;

    public:
        Curve();
        ~Curve();
        void setId(string Id);
        string getId(void);
        void setNumberOfCoordinates(int number);
        int getNumberOfCoordinates(void);
        //vector<Point*> get_listOfCoordinates();
        void DisplayVectorContents();
        void PushToVector(Point* aPoint);
    double getSpecificXCoord(int position);
    double getSpecificYCoord(int position);
};

