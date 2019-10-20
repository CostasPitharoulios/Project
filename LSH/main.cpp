#include <bitset>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "../Point.hpp"
#include "../dist.hpp"
#include "LSH.hpp"

using namespace std;

int main(int argc,char *argv[]){
    string inputFile, outputFile;
    int r;

    // Handling arguments
    if (argc == 5 || argc == 7){
        int i;
        for(i=1 ; i<argc ; i++){
            if(!strcmp(argv[i],"-d"))
                inputFile = argv[i+1];
            if(!strcmp(argv[i],"-o"))
                outputFile = argv[i+1];
            if(!strcmp(argv[i],"-r"))
                r = stoi(argv[i+1]);
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
    if (r < 0){
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

    int k = 4, L=5;
    LSH lsh(4*r, p1.getD(), k, L);

    lsh.insert(p1);

    // Read input file
    /*while(getline(in,str)){
        istringstream ss(str);
        Point p;

        ss >> token;
        p.setId(stoi(token));

        while( ss >> token )
            p.addCoordinate(stod(token));

        // Insert it to the dataset and hash it
        lsh.insert(p);
    }
    */

    //lsh.printG(1);

    //uint32_t gp = g.hash(p);
    //cout << "g(p) = " << bitset<32>(gp) << " = " << gp << endl;

    in.close();
    return 0;
}
