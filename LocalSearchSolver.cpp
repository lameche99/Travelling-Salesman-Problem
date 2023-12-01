#include "LocalSearchSolver.h"
#include <iostream>
#include <chrono> 

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
    using namespace std;
    using namespace chrono;

    double probSize = getSize();
    // declare constants of simulated annealing algorithm
    double T;
    if (probSize < 60) {
        T = 0.2;
    } else {
        T = 1; // higher temperature for larger problems
    }
    int nsteps = 3000000;
    int M = 5;  // lower temperature every M steps
    double coolingFactor = 0.9999;  // ratio by which we reduce temperature
    int maxCountNoChange = max(1000. * (probSize-10 + 1), 1000.); // if algo does not accept new points for a certain amount of steps, then stop
    int nNewTours = 3;
    double swapPairProb = 0.90; // probability to swap pair over changing node

    // int nsteps = 3000000;
    // double T = max(0.1, 0.016 * (probSize-50) + 0.2); // increase T with problem size
    // int M = 5;  // lower temperature every M steps
    // double coolingFactor = min(1.25e-5*(probSize-50) + 0.99995, 0.99999);  // ratio by which we reduce temperature
    // int maxCountNoChange = max(1000. * (probSize-10 + 1), 1000.); // if algo does not accept new points for a certain amount of steps, then stop
    // int nNewTours = 3;
    // double swapPairProb = 0.9; // probability to swap pair over changing node


    // higher number of maxCountNoChange for higher dimension problems
    int countNoChange = 0;

    // declare tour and cost of tour variables that will be updated iteratively
    vector<int> tour;
    int costTour;

    vector<int> bestTour;
    int costBestTour;
    

    int seed = getSeed();
    std::mt19937 engine(seed);  // will pass Random Number Generator (RNG) engine to functions that use randomness

    tour = select_random_tour(engine);  // get random tour
    costTour = computeTourLength(adjList , tour);

    auto start = high_resolution_clock::now(); // initialize chronometer
    int t = 0;
    double execTime;
    while ( (t<nsteps) && (execTime<getCutoff()) && (countNoChange < maxCountNoChange)){

        uniform_real_distribution<> uniform(0.0, 1.0);
        double r = uniform(engine);
        vector<int> newTour;
        if (r<swapPairProb) {
            newTour = swap_random_pair(tour, engine);
        } else{
            newTour = move_random_node(tour, engine);
        }
        
        // add extra swaps at the beginning
        for(int otherswaps = 0; otherswaps <= (nNewTours-t*2./maxCountNoChange); otherswaps++) {
                uniform_real_distribution<> uniform(0.0, 1.0);
                double r = uniform(engine);
            if (r<swapPairProb) {
                 newTour = swap_random_pair(tour, engine);
            } else{
                newTour = move_random_node(tour, engine);
            }
        }   

        int costNewTour = computeTourLength(adjList, newTour);

        // accept new tour if it has less cost, else accept it with a given probability defined by the constants
        double deltaE = costNewTour - costTour;  // always >0
        
        if (deltaE < 0){
            tour = newTour;
            costTour = costNewTour;
            bestTour = tour;
            costBestTour = costTour;
            countNoChange = 0;
        } else { // deltaE >= 0
            deltaE = deltaE / costTour; // normalize deltaE so it is unitless (in percent of regular tour)
            double prob = exp(-deltaE/(T));
            uniform_real_distribution<> uniform(0.0, 1.0);
            double r = uniform(engine);
            if (r < prob) {
                tour = newTour;
                costTour = costNewTour;
                
                if (costNewTour == costTour) {
                    countNoChange++;
                }else {
                    countNoChange = 0;
                }

            } else {
                countNoChange++;
            }
        }
        //if (tour == newTour)
        //    costTour = costNewTour;  // update cost it tour was updated
        //cout<<"iteration "<<t<<" cost: "<<costTour<<endl;  // print current cost
        

        // decrease Temperature parameter so we go "uphill" in solution space less often and converge faster
        if (t % M == 0) {
            T = T * coolingFactor;
        }
        t++;
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        execTime = duration.count() / 1e6;
    }

    // cout<<endl<<"-----Printing Local Search cost and tour (seed "<<seed<<")-----"<<endl;
    // cout<<"Cost: "<<costTour<<endl;
    // cout<<"Tour: ";
    // for (int v : tour)
    //     cout<<v<<" ";
    // cout<<endl;
    pair<vector<int>,int> tourCostPair = make_pair(bestTour, costBestTour);
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

vector<int> LsSolver::move_random_node(vector<int> tour, std::mt19937 engine){
    int seed = getSeed();
    tour.pop_back();  // ignore last node (same as first) to select 2 random indices
    uniform_int_distribution<int> distribution(0, tour.size()-1);
    int idx1 = distribution(engine);
    int idx2 = distribution(engine);
    while (idx2 == idx1)
        idx2 = distribution(engine);

    // Extract the node at idx1
    int nodeToMove = tour[idx1];

    // Erase the node at idx1
    tour.erase(tour.begin() + idx1);

    // Insert the node at idx2
    tour.insert(tour.begin() + idx2, nodeToMove);

    tour.push_back(tour[0]);
    return tour;
}