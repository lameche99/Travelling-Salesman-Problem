#include "BruteForceSolver.h"

// Constructor
BfSolver::BfSolver(string fname, string method, string cutoff, string seed) : TspSolver(fname, method, cutoff, seed) {
    // add something if different from parent class
}


void BfSolver::solve() {
    pair<int, vector<int> > sol;
    int dims = this->getSize();
    if (dims <= 10) {
        sol = bruteForceTSP_10(this->getAdjList(), dims, this->getCutoff(), this->getSeed());
        setTour(sol.second);
    } else {
        sol = bruteForceTSP_11(this->getAdjList(), dims, this->getCutoff(), this->getSeed());
        setTour(sol.second);
    }
}

// Function to solve the TSP with a Brute Force algorithm for small graphs (|V| <= 10)
// Parameters:
// - adjMat: Adjacency matrix representing the graph.
// - numNodes: Number of nodes in the graph.
// - time_constraint: Time limit for the algorithm.
// - seed: Seed for random number generation.
pair<int, vector<int> > BfSolver::bruteForceTSP_10(const vector<vector<Pair> >& adjMat, int numNodes, double time_constraint, unsigned seed) {
    // Generate all permutations
    vector<vector<int> > allPermutations = generatePermutations(numNodes);

    // Shuffle the permutations with a specified seed
    shufflePermutations(allPermutations, seed);

    // Set an upper bound for the time in place (exit condition)
    time_point<high_resolution_clock> start = high_resolution_clock::now();
    time_point<high_resolution_clock> end = high_resolution_clock::now();
    double duration = duration_cast<seconds>(end - start).count();

    // Store the minimum weight Hamiltonian Cycle and its vertices
    int min_path = INT_MAX;
    vector<int> min_path_nodes(numNodes);

    // Counter to keep track of processed permutations
    int permutationCounter = 0;
   
    do {
        // Store the current weight Hamiltonian Cycle
        int current_path = 0;

        // Calculate the total weight of the current Hamiltonian Cycle
        for (int j=0; j<numNodes-1; j++) {
            int from = allPermutations[permutationCounter][j];
            int to = allPermutations[permutationCounter][j + 1];
            current_path += adjMat[from - 1][to - 1].first;
        }

        // Add the weight of the last edge to complete the cycle
        current_path += adjMat[allPermutations[permutationCounter][numNodes - 1] - 1][allPermutations[permutationCounter][0] - 1].first;
        min_path_nodes.push_back(adjMat[allPermutations[permutationCounter][numNodes - 1] - 1][allPermutations[permutationCounter][0] - 1].second);

        // Update the minimum path if the current path is smaller
        if (current_path < min_path) {
            min_path = current_path;
            min_path_nodes = allPermutations[permutationCounter];
        }
        
        // Increment the counter
        permutationCounter++;

        // Update the end time
        end = high_resolution_clock::now();

        // Calculate the elapsed time
        duration = duration_cast<seconds>(end - start).count();

        if (DEBUG) {
        // Print debugging information
        cout << "Current Path: " << current_path << " | Elapsed Time: " << duration << " seconds" << endl;
        }

        // Uncomment the following line if you want to add a delay
        // this_thread::sleep_for(milliseconds(100));

    } while (duration < time_constraint && permutationCounter < allPermutations.size());

    if (DEBUG) {
    cout << "Loop finished after: " << duration << " seconds" << endl;
    } 

    return make_pair(min_path, min_path_nodes);
}


// Function to generate all permutations of N nodes
vector<vector<int> > BfSolver::generatePermutations(int numNodes) {
    // Create a vector with nodes [0, 1, ..., numNodes-1]
    vector<int> nodes(numNodes);
    for (int i=0; i<numNodes; i++) {
        nodes[i] = i + 1;
    }

    // Initialize a vector to store all permutations
    vector<vector<int> > permutations;

    // Generate permutations and store them in the vector
    do {
        permutations.push_back(nodes);
    } while (next_permutation(nodes.begin(), nodes.end()));

    return permutations;
}


// Function to shuffle a vector of vectors with a specified seed
void BfSolver::shufflePermutations(vector<vector<int> >& permutations, unsigned seed) {
    // Shuffle the generated permutations to increase randomness
    mt19937 g(seed);
    shuffle(permutations.begin(), permutations.end(), g);
}



// Parameters:
// - adjMat: Adjacency matrix representing the graph.
// - numNodes: Number of nodes in the graph.
// - time_constraint: Time limit for the algorithm.
// - seed: Seed for random number generation.
// Function to solve the TSP with a Brute Force algorithm for large graphs (|V| > 10)
pair<int, vector<int> > BfSolver::bruteForceTSP_11(const vector<vector<Pair> >& adjMat, int numNodes, double time_constraint, unsigned seed) {
    // Generate an initial permutation
    vector<int> permutation;
    for (int i=0; i<numNodes; i++)
        permutation.push_back(i + 1);

    // Use the provided seed for randomness
    mt19937 g(seed);

    // Set an upper bound for the time in place (exit condition)
    time_point<high_resolution_clock> start = high_resolution_clock::now();
    time_point<high_resolution_clock> end = high_resolution_clock::now();
    double duration = duration_cast<seconds>(end - start).count();

    // Store the minimum weight Hamiltonian Cycle and its vertices
    int min_path = INT_MAX;
    vector<int> min_path_nodes(numNodes);

    // Counter to keep track of processed permutations
    int permutationCounter = 0;
    double permutationUpperBound = tgamma(numNodes + 1);

    do {
        // Randomize the order of vertices using the provided seed
        shuffle(permutation.begin(), permutation.end(), g);

        if (DEBUG) {
            // Print the elements of the current permutation
            cout << "Current Permutation: ";
            for (int i=0; i<permutation.size(); i++) {
                cout << permutation[i] << " ";
            }
            cout << endl;
        }

        // Store the current weight Hamiltonian Cycle
        int current_path = 0;

        // Calculate the total weight of the current Hamiltonian Cycle
        for (int j=0; j<numNodes-1; j++) {
            int from = permutation[j];
            int to = permutation[j + 1];
            current_path += adjMat[from - 1][to - 1].first;
        }

        // Add the weight of the last edge to complete the cycle
        current_path += adjMat[permutation[numNodes - 1] - 1][permutation[0] - 1].first;
        permutation.push_back(adjMat[permutation[numNodes - 1] - 1][permutation[0] - 1].second);

        // Update the minimum path if the current path is smaller
        if (current_path < min_path) {
            min_path = current_path;
            min_path_nodes = permutation;
        }

        // Increment the counter
        permutationCounter++;

        // Update the end time
        end = high_resolution_clock::now();

        // Calculate the elapsed time
        duration = duration_cast<seconds>(end - start).count();

        if (DEBUG) {
            cout << "Current Path: " << current_path << " | Elapsed Time: " << duration << " seconds" << endl;
        }

        // Add a delay to avoid a tight loop (uncomment if needed)
        // this_thread::sleep_for(milliseconds(100));

    } while (duration < time_constraint && permutationCounter < permutationUpperBound && next_permutation(permutation.begin(), permutation.end()));

    if (DEBUG) {
        cout << "Loop finished after: " << duration << " seconds" << endl;
    }

    return make_pair(min_path, min_path_nodes);
}
