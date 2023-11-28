#include "util.h"

int main(int argc, char** argv) {
    Approx algo(argv[1], argv[2], argv[3]);
    
    algo.tspSolver();
    vector<int> fullTour = algo.getTour();
    cout << "Full Tour" << endl;
    for (int i = 0; i < fullTour.size(); i++) {
        cout << fullTour[i] << " ";
    }
    cout << endl;
    cout << "Quality: " << algo.getQuality() << endl;
    // algo.displayAdjList(fullTree);
    // algo.primMST(1);
    // vector<vector<Pair> > mst = algo.getMST();
    // algo.displayAdjList(mst);
    // algo.setInFile(argv[1]);
    // algo.setMethod(argv[2]);
    // algo.read();
    // algo.makeAdjList();
    
    // cout << "Distance: " << adjList[5][5].first << endl;
    // cout << "Adj Node: " << adjList[5][5].second << endl;

    // algo.primMST(1);
    return 0;
}