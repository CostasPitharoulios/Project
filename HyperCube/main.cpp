#include <bitset>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include "../Point.hpp"
#include "../dist.hpp"
#include "HC.hpp"

using namespace std;

int main(int argc,char *argv[]){
    string inputFile, outputFile, queryFile;
    double r=-1;

    // Handling arguments
    if (argc == 5 || argc == 7){
        int i;
        for(i=1 ; i<argc ; i++){
            if(!strcmp(argv[i],"-d"))
                inputFile = argv[i+1];
            if(!strcmp(argv[i],"-q"))
                queryFile = argv[i+1];
            if(!strcmp(argv[i],"-o"))
                outputFile = argv[i+1];
            if(!strcmp(argv[i],"-r"))
                r = stod(argv[i+1]);
        }
    }
    else{
        cerr << "Wrong number of arguments" << endl;
        return 1;
    }

    // Open file
    ifstream in(inputFile.c_str());
    if (!in){
        cerr << "Cannot open the input file : " << inputFile << endl;
        return 1;
    }
    if (r < 0 && r!=-1){
        cerr << "r must be positive." << endl;
        return 1;
    }

    // Read the first point
    string str,token;
    Point p1;
    if(getline(in,str)){
        istringstream ss(str);
        ss >> token;
        p1.setId(stoi(token));
        while( ss >> token )
            p1.addCoordinate(stod(token));
    }else{
        cerr << "Input file " << inputFile << " is empty." << endl;
        return 1;
    }
 
    /*Point p1(1);
    p1.addCoordinate(0);
    p1.addCoordinate(50);
    p1.addCoordinate(22);
    p1.addCoordinate(0);

    Point p2(2);
    p2.addCoordinate(19);
    p2.addCoordinate(3);
    p2.addCoordinate(41);
    p2.addCoordinate(5);
    */

    srand(time(NULL));
    int k = 4, dd=8, w=4, hd=2;
    HC hc(w, p1.getD(), k, dd, hd);

    hc.insert(p1);

    // Read input file
    cout << "Reading input dataset..." << endl;
    while(getline(in,str)){
        istringstream ss(str);
        ss >> token;
        Point p(stoi(token));

        while( ss >> token )
            p.addCoordinate(stod(token));

        // Insert it to the dataset and hash it
        hc.insert(p);
    }
    cout << "Reading complete." << endl;

    ifstream qin(queryFile.c_str());
    if (!qin){
        cerr << "Cannot open the query file : " << queryFile << endl;
        return 1;
    }

    // Read query file
    while(getline(qin,str)){
        istringstream ss(str);
        ss >> token;
        Point p(stoi(token));

        while( ss >> token )
            p.addCoordinate(stod(token));

        // Find nearest neighbour(s)
        if ( r==-1){ // if r is not given as argument
            // Find its A-NN
            double dist;
            Point *nn = hc.nearestNeighbour(p,"manh",dist);

            if (nn!=nullptr)
                cout << "NN of " << p.getId() << " is " << nn->getId() << " with distance " << dist << endl;
            else
                cout << "NN of " << p.getId() << " is was not found " << endl;
        }else{
            vector<double> dist;
            vector<Point *> rnn = hc.nearestNeighbours(p,"manh",r,dist);

            if ( rnn.size()==0 ){
                cout << "NN of " << p.getId() << " in radius " << r << " is was not found " << endl;
            }else{
                cout << "NN of " << p.getId() << " in radius " << r << " are: " << endl;
                for (int i=0; i<rnn.size(); i++){
                    cout << "- " << rnn.at(i)->getId() << " with distance " << dist.at(i) << endl;
                }
            }
        }
        //////////////
        break;
        /////////////
    }

    //uint32_t gp = g.hash(p);
    //cout << "g(p) = " << bitset<32>(gp) << " = " << gp << endl;

    in.close();
    return 0;
}
