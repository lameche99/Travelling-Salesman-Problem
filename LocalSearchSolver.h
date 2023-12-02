#ifndef ls
#define ls
#include "AbstractSolver.h"
#include <iostream>
#include <random>

typedef pair<int, Pair> BigPair;

class LsSolver : public TspSolver {
    public:
        // Constructors
        LsSolver(string fname, string method, string cutoff, string seed);

        // main function
        void solve() override;

        // local search
        pair<vector<int>,int> runLocalSearch(vector<vector<Pair> > adjList);

        vector<int> select_random_tour(std::mt19937 engine);

        vector<int> swap_random_pair(vector<int> tour, std::mt19937 engine);
        vector<int> move_random_node(vector<int> tour, std::mt19937 engine);

        int get_cost_tour(vector<vector<Pair> > adjList, vector<int> tour);

};

#endif