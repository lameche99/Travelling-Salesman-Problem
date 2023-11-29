#include "AbstractSolver.cpp"
#include "ApproxSolver.cpp"
#include "BruteForceSolver.cpp"
#include "LocalSearchSolver.cpp"

// main file that runs either of the implemented algorithms
// to solve the traveling salesman problem (TSP)
//
// Inputs:
//  argc: count number of arguments
//  argv: contains the parameters of the run
//      argv[1]: filename to the dataset eg: data/Atlanta.tsp
//      argv[2]: method that we want to use to solve the tsp
//      argv[3]: cutoff time in seconds
//      argv[4]: random seed
// Output: /
// each method creates a file under the name 
// "argv[1]_argv[2]_argv[3]_argv[4].sol"

int main(int argc, char** argv) {

    // create the pointer to a solver
    TspSolver* solver = nullptr;

    // create selected solver
    if (strcmp(argv[2], "BF") == 0) { 
        solver = new BfSolver(argv[1], argv[2], argv[3], argv[4]);
    } else if (strcmp(argv[2], "Approx") == 0) {
        solver = new ApproxSolver(argv[1], argv[2], argv[3], argv[4]);
    } else if (strcmp(argv[2], "LS") == 0) {
        solver = new LsSolver(argv[1], argv[2], argv[3], argv[4]);
    } else {
        std::cout << "\033[1;33m"; // set text color to orange
        std::cout << "a correct algorithm name was not provided\n";
        std::cout << "please select \"BF\", \"Approx\", or \"LS\"\n";
        std::cout << "example of input : ";
        std::cout << "./data/Atlanta.tsp Approx 100 0\n";
        std::cout << "\033[0m";  // reset text color to default
        return 1;
    }

    // initialization for execution time measurement
    time_t start, end;
    double execTime;

    // solve the problem
    time(&start); // start clock
    ios_base::sync_with_stdio(false);
    solver->solve();
    time(&end); // end clock
    execTime = double(end - start);

    // write solution and print results
    solver->writeSol();
    std::cout << "Quality: " << fixed << solver->getQuality() << setprecision(7) << endl;
    std::cout << "Execution Time: " << fixed << execTime << setprecision(5) << endl; 
    std::cout << "Full Tour? " << solver->getVerdict() << endl;

    return 0;
}