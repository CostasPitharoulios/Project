#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include "../Point.hpp"
#include "../dist.hpp"

using namespace std;

int main(int argc,char *argv[]){
    string inputFile, outputFile, queryFile;

    // Handling arguments TODO safety checks
    if (argc>1){
        int i;
        for(i=1 ; i<argc ; i++){
            if(!strcmp(argv[i],"-d"))
                inputFile = argv[i+1];
            if(!strcmp(argv[i],"-o"))
                outputFile = argv[i+1];
            if(!strcmp(argv[i],"-q"))
                queryFile = argv[i+1];
        }
    }

    // Open file
    ifstream in(inputFile.c_str());
    if (!in){
        cerr << "Cannot open the input file : " << inputFile << endl;
        return 1;
    }
    cout << inputFile << endl;

    ifstream qin(queryFile.c_str());
    if (!qin){
        cerr << "Cannot open the query file : " << queryFile << endl;
        return 1;
    }
    cout << queryFile << endl;

    vector<Point> listOfPoints;
    vector<Point> listOfQueryPoints;

    // Read input file
    string str,token;
    while(getline(in,str)){
        istringstream ss(str);
        Point p;

        ss >> token;
        p.setId(stoi(token));

        while( ss >> token )
            p.addCoordinate(stod(token));

        listOfPoints.push_back(p);
    }

    // Read query file
    while(getline(qin,str)){
        istringstream ss(str);
        Point p;

        ss >> token;
        p.setId(stoi(token));

        while( ss >> token )
            p.addCoordinate(stod(token));

        listOfQueryPoints.push_back(p);
    }

    // Find the nearest point for every query point
    for (int i=0; i<listOfQueryPoints.size(); i++){
        double min = numeric_limits<double>::max();
        int min_id=-1;
        for (int j=0; j<listOfPoints.size(); j++){
            double dist = manhattanDistance(listOfPoints.at(j).getCoordinates(), listOfQueryPoints.at(i).getCoordinates());
            if (dist < min){
                min = dist;
                min_id = listOfPoints.at(j).getId();
            }
        }
        cout << "NN of " << listOfQueryPoints.at(i).getId() << " is " << min_id << " with distance " << min << endl;
    }

    in.close();
    qin.close();
    return 0;
}
