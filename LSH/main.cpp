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
    string inputFile, outputFile, queryFile;
    double r=-1;
    int k = 4, L=5, w=4000;

    // Handling arguments
    int n=0;
    for(int i=1 ; i<argc ; i++){
        if(!strcmp(argv[i],"-d")){
            inputFile = argv[i+1];
            n++;
        }
        if(!strcmp(argv[i],"-q")){
            queryFile = argv[i+1];
            n++;
        }
        if(!strcmp(argv[i],"-o"))
            outputFile = argv[i+1];
        if(!strcmp(argv[i],"-r"))
            r = stod(argv[i+1]);
        if(!strcmp(argv[i],"-k"))
            k = stoi(argv[i+1]);
        if(!strcmp(argv[i],"-L"))
            L = stoi(argv[i+1]);
        if(!strcmp(argv[i],"-w"))
            w = stoi(argv[i+1]);
    }
    if ( n < 2){
        cerr << "Expected the necessary arguments -d [inputFile], -q [queryFile]" << endl;
        return 1;
    }

    // Open file
    ifstream in(inputFile.c_str());
    if (!in){
        cerr << "Cannot open the input file " << inputFile << ".(Specify with -d argument)" << endl;
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
    
    cout << "Starting LSH with w=" << w << ", k=" << k << ", L=" << L ;
    if (r!=-1) cout << ", r=" << r;
    cout << "." << endl;
 
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

    LSH lsh(w, p1.getD(), k, L, r);

    lsh.insert(p1);

    // Read input file line by line
    cout << "Reading input dataset..." << endl;
    while(getline(in,str)){
        istringstream ss(str);
        ss >> token;
        Point p(stoi(token));

        while( ss >> token )
            p.addCoordinate(stod(token));

        // Insert it to the dataset and hash it
        lsh.insert(p);
    }
    cout << "Reading complete." << endl;


    //cout << "G: \n";
    //lsh.printG(0);

    ifstream qin(queryFile.c_str());
    if (!qin){
        cerr << "Cannot open the query file : " << queryFile << ".(Specify with -d argument)" << endl;
        return 1;
    }
    ofstream out(outputFile.c_str());
    if (!out){
        cerr << "Cannot open the output file : " << outputFile << " so the output will not be saved.(Specify with -o argument)" << endl;
    }

    // Read query file line by line
    while(getline(qin,str)){

        // Read Curve info
        istringstream ss(str);
        ss >> token;
        Point p(stoi(token));

        while( ss >> token )
            p.addCoordinate(stod(token));

        lsh.answerQuery(p, out);

        //////////////
        break;
        /////////////
    }

    //uint32_t gp = g.hash(p);
    //cout << "g(p) = " << bitset<32>(gp) << " = " << gp << endl;

    in.close();
    qin.close();
    out.close();
    return 0;
}
