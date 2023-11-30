#ifndef bf
#define bf
#include "AbstractSolver.h"

typedef pair<int, Pair> BigPair;

class BfSolver : public TspSolver {
    private:
        pair<int, vector<int> > bruteForceTSP_10(const vector<vector<Pair> >& adjMat, int numNodes, double time_constraint, unsigned seed);
        vector<vector<int> > generatePermutations(int numNodes);
        void shufflePermutations(vector<vector<int> >& permutations, unsigned seed);
        pair<int, vector<int> > bruteForceTSP_11(const vector<vector<Pair> >& adjMat, int numNodes, double time_constraint, unsigned seed);
    public:
        // Constructors
        BfSolver(string fname, string method, string cutoff, string seed);
        
        // main function
        void solve() override;
};

#endif