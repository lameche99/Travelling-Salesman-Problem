#ifndef ls
#define ls
#include "AbstractSolver.h"

typedef pair<int, Pair> BigPair;

class LsSolver : public TspSolver {
    public:
        // Constructors
        LsSolver(string fname, string method, string cutoff, string seed);

        // main function
        void solve() override;
};

#endif