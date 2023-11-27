#include "algos.h"

void Approx::primMST(int source){
    vector<vector<Pair> > adjList = this->getAdjList();
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
        if (visitedVertex.at(source - 1)) // Check for cycle
        continue; // Already accounted for it, move on
        visitedVertex.at(source - 1) = true; // Else, mark the vertex so that we won't have to visit it again
        cout << "Mark vertex " << info.second << " and add weight " << info.first << endl;
        minCost += info.first; // Add to minCos
        vector<Pair> nodes = adjList[source - 1];
        Pair adj;
        long long int dist;
        int vertex;
        for (int i = 0; i < nodes.size(); i++) {
            adj = nodes[i];
            dist = adj.first, vertex = adj.second;
            if (!visitedVertex.at(vertex - 1)) {
                PQ.push(adj);
            }
        }
    }
    cout << "Minimum cost to connect all vertices : " << minCost << endl;
} // PrimsAlgorithm
