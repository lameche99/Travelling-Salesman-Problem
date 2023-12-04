#ifndef util
#define util

#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <functional>
#include <iomanip>
#include <cstring>
using namespace std;
typedef pair<double, double> Pair;

// Virtual class that encompasses many useful functions common to all solvers
class TspSolver {
    private:
        string inFile, outFile, city, method, full;
        int size, cutoff, seed;
        double quality;
        vector<int> ids, xaxis, yaxis, tour;
        vector<vector<Pair> > adjList;
        int euclid(int x1, int x2, int y1, int y2);

    protected:
        // setters are private
        // variables are initialized with public init function
        void setInFile(string fname) {this->inFile = fname;}
        void setOutFile() {
            if (this->method == "BF") {
                this->outFile = "./output/" + getCity() + '_' + getMethod() + '_' + to_string(getCutoff()) + ".sol";
            } else if (this->method == "Approx")
            {
                this->outFile = "./output/" + getCity() + '_' + getMethod() + '_' + to_string(getSeed()) + ".sol";
            } else if (this->method == "LS") {
                this->outFile = "./output/" + getCity() + '_' + getMethod() + '_' + to_string(getCutoff()) + '_' + to_string(getSeed()) + ".sol";
            } else {
                cout << "Invalid Method. Try again." << endl;
            }    
        }
        void setCity(string cityname) {this->city = cityname;}
        void setMethod(string meth) {this->method = meth;}
        void setCutoff(string cutoff) {this->cutoff = stoi(cutoff);}
        void setSeed(string seed) {this->seed = stoi(seed);}
        void setSize(int size) {this->size = size;}
        void setQuality(double cost) {this->quality = cost;}
        void setTour(vector<int> tour);

    public:
        // Constructor
        TspSolver(string inFile, string method, string cutoff, string seed);
        TspSolver(){};

        // Getters for private variables
        string getInFile() {return this->inFile;}
        string getOutFile() {return this->outFile;}
        string getCity() {return this->city;}
        string getMethod() {return this->method;}
        string getVerdict() {return this->full;}
        int getCutoff() {return this->cutoff;}
        int getSeed() {return this->seed;}
        int getSize() {return this->size;}
        double getQuality() {return this->quality;}
        vector<int> getIds() {return this->ids;}
        vector<int> getXs() {return this->xaxis;}
        vector<int> getYs() {return this->yaxis;}
        vector<int> getTour() {return this->tour;}
        vector<vector<Pair> > getAdjList() {return this->adjList;}

        // compute the length of a tour
        //int computeTourLength(vector<vector<Pair>> adjList, vector<int> tour);

        inline int computeTourLength(const vector<vector<Pair>>& adjList,const vector<int>& tour);

        // Input Handling
        void read(); // Read file and extract information
        void makeAdjList(); // Create adjacency matrix representation of Graph
        void displayAdjList(vector<vector<Pair> > adjList); // Print Adjacency matrix

        // Write Output
        void writeSol();

        // solve the TSP with initialized variables
        // this is implemented in the children class
        virtual void solve() = 0;
};

#endif