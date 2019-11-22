#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "../include/Point.hpp"
#include "../include/Clustering.hpp"
#include "../include/Curve.hpp"

using namespace std;

int main(int argc,char *argv[]){
    string inputFile, outputFile, confFile;

    // Handling arguments
    if ( argc != 7 && argc != 8 ){
        cerr << "Wrong number of arguments" << endl;
        return 1;
    }
    for(int i=1 ; i<argc ; i++){
        if(!strcmp(argv[i],"-i"))
            inputFile = argv[i+1];
        if(!strcmp(argv[i],"-o"))
            outputFile = argv[i+1];
        if(!strcmp(argv[i],"-c"))
            confFile = argv[i+1];
    }

    // Read configuration file
    int n_clusters =-1, n_grids=2, L=3, k=4;
    ifstream cin(confFile.c_str());
    if (!cin){
        cerr << "Cannot open the configuration file " << confFile << endl;
        return 1;
    }
    string str,token,val;
    while(getline(cin,str)){
        istringstream ss(str);
        ss >> token;
        ss >> val;

        if(!token.compare("number_of_clusters:")){
            n_clusters = stoi(val);
        }else if(!token.compare("number_of_grids:")){
            n_grids = stoi(val);
        }else if(!token.compare("number_of_vector_hash_tables:")){
            L = stoi(val);
        }else if(!token.compare("number_of_vector_hash_functions:")){
            k = stoi(val);
        }else{
            cout << "Unknown argument in config file : " << token << endl;
        }
    }
    if(n_clusters == -1){
        cout << "Error: number_of_clusters argument is neccessary in the config file" << endl;
        return 1;
    }

    // Open input file
    ifstream in(inputFile.c_str());
    if (!in){
        cerr << "Cannot open the input file " << inputFile << endl;
        return 1;
    }

    // Read the first line
    //Point p1;
    bool curvesFlag = false;
    if(getline(in,str)){
        if(!str.compare("vectors")){
            cout << "Its all about vectors" << endl;
        }
        else if(!str.compare("curves")){
            cout << "Its all about Curves" << endl;
            curvesFlag = true;
        }
        else{
            cerr << "Expected \"curves\" or \"vectors\" as the first line of the input file " << inputFile << endl;
            return 1;
        }
    }else{
        cerr << "Input file " << inputFile << " is empty." << endl;
        return 1;
    }

       
    if(!curvesFlag){ 
        // KMeans for vectors
        vector<void*> dataset;
        
        // Read input file line by line
        cout << "Reading input dataset..." << endl;
        while(getline(in,str)){
            istringstream ss(str);
            ss >> token;

            //Read item id
            int id;
            sscanf(token.c_str(),"item%d",&id);

            Point p(id);

            //Read coordinates
            while( ss >> token )
                p.addCoordinate(stod(token));

            // Save it to the dataset list
            dataset.push_back((void*)new Point(p));
        }
        cout << "Reading complete." << endl;

        // Make a Clustering instance
        Clustering vc(false,dataset,n_clusters,"random");

        vc.KMeans();
    }
    else{ 
        // KMeans for curves
        vector<void*> dataset;

        // Read input file line by line
        cout << "Reading input dataset..." << endl;
        while (getline(in,str)){
            stringstream linestream(str);
           
            // The first token is the id 
            getline(linestream, token, '\t');
            Curve c;
            c.setId(token);
            //cout << ":::Id= " << token << "\n";
            
            // The second token is the number of coordinates
            getline(linestream, token, '\t');
            //cout << ":::Num of cords: " << token << endl;
            int numberOfCords = stoi(token);
            c.setNumberOfCoordinates(numberOfCords);
             
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
                c.PushToVector(aPoint);
            }
            //c.printCoordinates(); 

            // Save curve to the dataset list
            dataset.push_back((void*)new Curve(c));
        }

        cout << "Reading complete." << endl;

        // Make a Clustering instance
        Clustering cc(true,dataset,n_clusters,"random");

        cc.KMeans();
    }
    cout << "Process complete. The output is written on file " << outputFile << endl;

    in.close();
    return 0;
}
