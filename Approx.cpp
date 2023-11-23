#include "algos.h"

void Approx::primMST(vector<Pair> adjList[], int source){
    int size = this->getSize();
    vector <bool> visitedVertex(size, false);
    priority_queue<Pair, vector<Pair>, greater<Pair> > PQ; // Set up priority queue
    Pair info;
    int minCost = 0;
    PQ.push(make_pair(0, source)); // Source has weight 0;
    while (!PQ.empty()){
        info = PQ.top(); // Use to get minimum weight
        source = info.second; // get the vertex
        PQ.pop(); // Pop before checking for cycles
        if (visitedVertex.at(source)) // Check for cycle
        continue; // Already accounted for it, move on
        visitedVertex.at(source) = true; // Else, mark the vertex so that we won't have to visit it again
        cout << "Mark vertex " << info.second << " and add weight " << info.first << endl;
        minCost += info.first; // Add to minCos
        for (vector<Pair>::iterator it = adjList[source].begin(); it != adjList[source].end(); it++) // Visit all children
        if (!visitedVertex.at(it->second)) // If vertex hasn't been visited already
            PQ.push(make_pair(it->first, it->second)); // Push vertex and weight onto Priority Queue
    } // While Priority Queue is not empty
    cout << "Minimum cost to connect all vertices : " << minCost << endl;
} // PrimsAlgorithm