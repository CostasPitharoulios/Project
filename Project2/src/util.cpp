#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
//#include <string>
#include "../include/util.hpp"
#include "../include/Curve.hpp"
#include "../include/Point.hpp"
#include "../include/Clustering.hpp"

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
        cout << "Dataset size: " << dataset.size() << endl;
    }

    in.close();
}

bool isCentroid(void* item, bool curvesFlag){
    if(!curvesFlag)
        if(((Point*)item)->getCluster() == nullptr)
            return false;
        else
            return (((Point*)((Point*)item)->getCluster()->getCentroid())->getId() == ((Point*)item)->getId());
    else
        if(((Curve*)item)->getCluster() == nullptr)
            return false;
        else
            return (((Curve*)((Curve*)item)->getCluster()->getCentroid())->getId() == ((Curve*)item)->getId());
}

// a%b but positive
int mod(int a, int b){
    return (a%b + b) % b;
}

void printOutput(ofstream& out, string q_id, string nn_id, double dist, double true_dist, double time, double true_time, vector<Point*> rnn){
    if (!out)
        return;

    out << "Query: " << q_id << endl;
    out << "Nearest neighbour: " << nn_id << endl;
    out << "distanceLSH: " << dist << endl;
    out << "distanceTrue: " << true_dist << endl;
    out << "tLSH: " << time << " ms" << endl;
    out << "tTrue: " << true_time << " ms" << endl;
    
    // r-near neighbors:
    if (rnn.size()>0){
        out << "R-near neighbours:" << endl;
        out << rnn.at(0)->getId();
        for(int i=1; i<rnn.size(); i++){
            out << ", " << rnn.at(i)->getId();
        }
        out << endl;
    }
    out << endl;
}

void printOutput(ofstream& out, string q_id, string hf, string nn_id, string true_id, double dist, double true_dist ){
    if (!out)
        return;

    out << "Query: " << q_id << endl;
    out << "HashFunction: " << hf << endl;
    out << "Found Nearest neighbour: " << nn_id << endl;
    out << "True Nearest neighbour: " << true_id << endl;
    out << "distanceFound: " << dist << endl;
    out << "distanceTrue: " << true_dist << endl;
    
    out << endl;
}
