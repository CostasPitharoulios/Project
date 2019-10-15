#include <iostream>
#include "Point.hpp"

using namespace std;

Point::Point(){
    id = 1;
    printf("Point was created\n");
}

Point::~Point(){
    printf("Point was destroyed\n");
}
