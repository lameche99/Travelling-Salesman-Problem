#include "algos.h"

int main(int argc, char** argv) {
    Approx algo;
    algo.setInFile(argv[1]);
    algo.setMethod(argv[2]);
    algo.read();
    algo.makeAdjList();
    
    // cout << "Distance: " << adjList[5][5].first << endl;
    // cout << "Adj Node: " << adjList[5][5].second << endl;

    algo.primMST(1);
    return 0;
}