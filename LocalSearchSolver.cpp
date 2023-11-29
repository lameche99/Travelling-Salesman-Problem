#include "LocalSearchSolver.h"

// Constructor
LsSolver::LsSolver(string fname, string method, string cutoff, string seed) : TspSolver(fname, method, cutoff, seed) {
    // add something if different from parent class
}

void LsSolver::solve() {
    pair<vector<int>,int> bestTour = runLocalSearch(getAdjList());

    int dims = this->getSize();

    // set the tour and quality as the last one 
    setTour(bestTour.first);
}

pair<vector<int>,int> LsSolver::runLocalSearch(vector<vector<Pair>> adjList){
    // declare constants of simulated annealing algorithm
    double k = 20;
    double T = 100;
    int nsteps = 1500000;
    int M = 5;  // lower temperature every M steps
    double coolingFactor = 0.9999;  // ratio by which we reduce temperature

    // declare tour and cost of tour variables that will be updated iteratively
    vector<int> tour;
    int costTour;
    int seed = getSeed();
    std::mt19937 engine(seed);  // will pass Random Number Generator (RNG) engine to functions that use randomness

    tour = select_random_tour(engine);  // get random tour
    for (int t = 0; t < nsteps; t++){
        costTour = computeTourLength(adjList , tour);
        vector<int> newTour = swap_random_pair(tour, engine);
        int costNewTour = computeTourLength(adjList, newTour);

        // accept new tour if it has less cost, else accept it with a given probability defined by the constants
        if (costNewTour < costTour){
            tour = newTour;
        } else {
            double deltaE = costNewTour - costTour;  // always >0
            deltaE = deltaE / costTour * 100; // normalize deltaE so it is unitless (in percent of regular tour)
            double prob = exp(-deltaE/(k*T));
            uniform_real_distribution<> uniform(0.0, 1.0);
            double r = uniform(engine);
            if (r < prob)
                tour = newTour;
        }
        if (tour == newTour)
            costTour = costNewTour;  // update cost it tour was updated
        // cout<<"iteration "<<t<<" cost: "<<costTour<<endl;  // print current cost

        // decrease Temperature parameter so we go "uphill" in solution space less often and converge faster
        if (t % M == 0)
            T = T * coolingFactor;
    }

    // cout<<endl<<"-----Printing Local Search cost and tour (seed "<<seed<<")-----"<<endl;
    // cout<<"Cost: "<<costTour<<endl;
    // cout<<"Tour: ";
    // for (int v : tour)
    //     cout<<v<<" ";
    // cout<<endl;
    pair<vector<int>,int> tourCostPair = make_pair(tour, costTour);
    return tourCostPair;
}

vector<int> LsSolver::select_random_tour(std::mt19937 engine){
    int size = getSize();
    vector<int> path;
    for (int v=1; v < size+1; v++)
        path.push_back(v);

    // randomly shuffle the vector
    shuffle(path.begin(), path.end(), engine);
    path.push_back(path[0]);  // connect end to beginning to complete the tour
    return path;
}

vector<int> LsSolver::swap_random_pair(vector<int> tour, std::mt19937 engine){
    int seed = getSeed();
    tour.pop_back();  // ignore last node (same as first) to select 2 random indices
    uniform_int_distribution<int> distribution(0, tour.size()-1);
    int idx1 = distribution(engine);
    int idx2 = distribution(engine);
    while (idx2 == idx1)
        idx2 = distribution(engine);

    iter_swap(tour.begin() + idx1, tour.begin() + idx2);  // swap 2 indices in vector
    tour.push_back(tour[0]);
    return tour;
}