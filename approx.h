#ifndef approx
#define approx
#include "util.h"

typedef pair<int, Pair> BigPair;

class Approx : public Util {
    private:
        vector<vector<Pair> > mst;
        vector<int> tour;
        void primMST(int src);
        bool isVisited(int src);
        void dfs(int src);
        double tourLength();
    public:
        // Constructors
        Approx(string fname, string method, string seed);
        ~Approx();
        // main function
        void tspSolver();
};

#endif