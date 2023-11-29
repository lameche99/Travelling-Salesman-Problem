#ifndef bf
#define bf
#include "AbstractSolver.h"

typedef pair<int, Pair> BigPair;

class BfSolver : public TspSolver {
    public:
        // Constructors
        BfSolver(string fname, string method, string cutoff, string seed);

        // main function
        void solve() override;
};

#endif