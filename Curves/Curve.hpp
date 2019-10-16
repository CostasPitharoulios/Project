#pragma once
#include <vector>
#include <string>

#include "../Point.hpp"

using namespace std;

class Curve{
    private:
        string id;
        vector<Point*> listOfCordinates;

    public:
        Curve();
        ~Curve();
        void setId(string Id);
        string getId(void);
        //vector<Point*> get_listOfCordinates();
        void DisplayVectorContents();
        void PushToVector(Point* aPoint);
};
