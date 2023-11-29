#include "ApproxSolver.h"

// Constructor
ApproxSolver::ApproxSolver(string fname, string method, string cutoff, string seed) : TspSolver(fname, method, cutoff, seed) {
    // add something if different from parent class
}

// Prims Algorithm
void ApproxSolver::primMST(int source){
    vector<vector<Pair> > fullTree;
    priority_queue<BigPair, vector<BigPair>, greater<BigPair> > PQ; // Set up priority queue
    int predecessor, cost, curr, size;
    BigPair info;
    Pair vert;

    fullTree = this->getAdjList();
    size = this->getSize();
    vector<vector<Pair> > mst(size, vector<Pair>(size));
    vector <bool> visitedVertex(size, false);
    vert = make_pair(source, source - 1); // node is (current, predecessor)
    PQ.push(make_pair(0, vert)); // Source has weight 0;

    while (!PQ.empty()){
        info = PQ.top(); // Use to get minimum weight
        cost = info.first; // get edge weight
        curr = info.second.first; // get current node
        predecessor = info.second.second; // get predecessor
        PQ.pop(); // Pop before checking for cycles

        if (visitedVertex.at(curr - 1)) // Check for cycle
            continue; // Already accounted for it, move on
        
        visitedVertex.at(curr - 1) = true; // Else, mark the vertex so that we won't have to visit it again
        if (curr != source)
            mst[predecessor][curr - 1] = make_pair(cost, curr);
        
        Pair edge;
        BigPair node;
        vector<Pair> nodes = fullTree[curr - 1];
        for (int i = 0; i < nodes.size(); i++) {
            edge = nodes[i];
            if (!visitedVertex.at(edge.second - 1)) {
                // PQ new node is (edge weight, (next vertex, current vertex))
                node = make_pair(edge.first, make_pair(edge.second, curr - 1));
                PQ.push(node);
            }
        }
    }
    this->mst = mst;
}

// Helper to check if node is alread in tour
bool ApproxSolver::isVisited(int source) {
    for (int i = 0; i < this->tour.size(); i++) {
        if (source == this->tour[i]) {
            return true;
        }
    }
    return false;
}

// Depth first search for optimal tour
void ApproxSolver::dfs(int source) {
    vector<Pair> nodes;
    this->tour.push_back(source); // add starting node to the tour
    nodes = this->mst[source - 1]; // get adjacent nodes in MST
    for (int j = 0; j < nodes.size(); j++) {
        if (nodes[j].first != 0 && !isVisited(nodes[j].second)) {
            dfs(nodes[j].second);
        }
    }
}

// TSP Wrapper
void ApproxSolver::solve() {
    int source = 1, dims = this->getSize();
    primMST(source);
    dfs(source);
    this->tour.push_back(source);
    this->setTour(this->tour);
}