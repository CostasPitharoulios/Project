#include <bits/stdc++.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include "../Point.hpp"

using namespace std;

int main(int argc,char *argv[]){
    string inputFile, outputFile;

    // Handling arguments TODO safety checks
    if(argc>1){
        int i;
        for(i=1 ; i<argc ; i++){
            if(!strcmp(argv[i],"-i"))
                inputFile = argv[i+1];
            if(!strcmp(argv[i],"-o"))
                outputFile = argv[i+1];
        }
    }

    // Open file
    ifstream in(inputFile.c_str());
    if(!in){
        cerr << "Cannot open the input file : " << inputFile << endl;
        return 1;
    }

    cout << inputFile << endl;
    Point p[2];

    // Diavazw 2 grammes gia testing 
    string str,token;
    for (int i=0; i<2; i++){
        getline(in,str);
        istringstream ss(str);
        size_t sz;
        while( ss >> token )
            p[i].addCoordinate(stod(token));
    }


    
    return 0;
}
