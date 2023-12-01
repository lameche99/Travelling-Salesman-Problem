#ifndef approx
#define approx
#include "AbstractSolver.h"

typedef pair<int, Pair> BigPair;

class ApproxSolver : public TspSolver {
    private:
        vector<vector<Pair> > mst;
        vector<int> tour;
        void primMST(int src);
        bool isVisited(int src);
        void dfs(int src);
        double tourLength();
    public:
        // Constructors
        ApproxSolver(string fname, string method, string cutoff, string seed);
        
        // main function
        void solve() override;
};

#endif