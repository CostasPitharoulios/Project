#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
//#include <string>
#include "../include/util.hpp"
#include "../include/Curve.hpp"
#include "../include/Point.hpp"

using namespace std;

void readDataset(string inputFile, vector<void*> &dataset, bool &curvesFlag){
    string str,token;
    // Open input file
    ifstream in(inputFile.c_str());
    if (!in){
        cerr << "Cannot open the input file " << inputFile << endl;
        exit(1);
    }

    // Read the first line
    //Point p1;
    if(getline(in,str)){
        if(!str.compare("vectors")){
            curvesFlag = false;
        }
        else if(!str.compare("curves")){
            curvesFlag = true;
        }
        else{
            cerr << "Expected \"curves\" or \"vectors\" as the first line of the input file " << inputFile << endl;
            exit(1);
        }
    }else{
        cerr << "Input file " << inputFile << " is empty." << endl;
        exit(1);
    }

    if(!curvesFlag){ 
        // Read input file of points line by line
        while(getline(in,str)){
            istringstream ss(str);
            ss >> token;

            //Read item id
            //int id;
            //sscanf(token.c_str(),"item%d",&id);
            //Point p(id);
            Point p(token);

            //Read coordinates
            while( ss >> token )
                p.addCoordinate(stod(token));

            // Save it to the dataset list
            dataset.push_back((void*)new Point(p));
        }
    }
    else{ 
        // Read input file of Curves line by line
        while (getline(in,str)){
            stringstream linestream(str);
           
            // The first token is the id 
            getline(linestream, token, '\t');
            Curve *c = new Curve;
            c->setId(token);
            //cout << ":::Id= " << token << "\n";
            
            // The second token is the number of coordinates
            getline(linestream, token, '\t');
            //cout << ":::Num of cords: " << token << endl;
            int numberOfCords = stoi(token);
            c->setNumberOfCoordinates(numberOfCords);
             
            // Reading each coordinate
            double x,y;
            for (int i=0; i< numberOfCords; i++){
               
                // Read x 
                getline(linestream, token, ' ');
                sscanf(token.c_str(), "(%lf,", &x);

                // Read y
                getline(linestream, token, ' ');
                sscanf(token.c_str(), "%lf)", &y);
               
                // Make a point 
                Point *aPoint = new Point();
                aPoint->setX(x);
                aPoint->setY(y);

                // Push it to the Curve 
                c->PushToVector(aPoint);
            }
            //cout << ":::";
            //c->printCoordinates();
            //cout << endl;

            // Save curve to the dataset list
            dataset.push_back((void*)c);
        }
    }
    in.close();
}
