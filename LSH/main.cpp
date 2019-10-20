#include <bitset>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "../Point.hpp"
#include "../dist.hpp"
#include "H.hpp"
#include "G.hpp"

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

    // Read only one GIA TESTINGS
    /*string str,token;
    getline(in,str);
    istringstream ss(str);
    size_t sz;
    Point p;
    ss >> token;
    p.setId(stoi(token));
    while( ss >> token )
        p.addCoordinate(stod(token));

    */

    Point p;
    p.addCoordinate(0);
    p.addCoordinate(55);
    p.addCoordinate(10);
    p.addCoordinate(0);

    cout << "Arxiko: ";
    p.printCoordinates();

    int k = 4;
    G g(4*r, p.getD(), k);

    uint32_t gp = g.hash(p);
    cout << "g(p) = " << bitset<32>(gp) << " = " << gp << endl;

    in.close();
    return 0;
}
