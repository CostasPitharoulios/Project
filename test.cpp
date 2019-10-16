#include <iostream>
#include <string>
#include <cstring>
#include "Point.hpp"

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

    string str;
    for (int i=0; i<2; i++){
        getline(in,str);
        
    }
    
    return 0;
}
