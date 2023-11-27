#ifndef algos
#define algos

#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <functional>
using namespace std;
typedef pair<long long int, long long int> Pair;

class Algorithm {
    private:
        string inFile, outFile;
        int size, cutoff, seed;
        string city, method;
        vector<int> ids, xaxis, yaxis;
        vector<vector<Pair> > adjList;
        int euclid(int x1, int x2, int y1, int y2);
    public:
        string getInFile() {return this->inFile;}
        string getOutFile() {return this->outFile;}
        string getCity() {return this->city;}
        string getMethod() {return this->method;}
        int getCutoff() {return this->cutoff;}
        int getSeed() {return this->seed;}
        int getSize() {return this->size;}
        vector<int> getIds() {return this->ids;}
        vector<int> getXs() {return this->xaxis;}
        vector<int> getYs() {return this->yaxis;}
        vector<vector<Pair> > getAdjList() {return this->adjList;}
        void setInFile(char* fname) {this->inFile = fname;}
        void setOutFile() {
            this->outFile = getCity() + '_' + getMethod() + '_' + to_string(getCutoff()) + '_' + to_string(getSeed()) + ".sol";
        }
        void setCity(string cityname) {this->city = cityname;}
        void setMethod(string meth) {this->method = meth;}
        void setCutoff(string cutoff) {this->cutoff = stoi(cutoff);}
        void setSeed(string seed) {this->seed = stoi(seed);}
        void setSize(int size) {this->size = size;}
        void read();
        void makeAdjList();
        void displayAdjList();
};

class Approx : public Algorithm {
    public:
        void primMST(int src);
};

class BF : public Algorithm {

};

class LS : public Algorithm {


};

#endif