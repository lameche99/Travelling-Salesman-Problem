#include "algos.h"

int main(int argc, char** argv) {
    Approx algo;
    algo.setInFile(argv[1]);
    algo.setMethod(argv[2]);
    algo.read();
    vector<Pair> adjList[algo.getSize()];
    algo.makeAdjList(adjList);
    algo.primMST(adjList, 0);
    return 0;
}