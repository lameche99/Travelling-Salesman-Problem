#include "AbstractSolver.h"

// eucledian distance
int TspSolver::euclid(int x1, int x2, int y1, int y2) {
    double x = x1 - x2;
    double y = y1 - y2;
    double dist = sqrt(pow(x, 2) + pow(y, 2));
    return int(dist + 0.5);
}

// read input data
void TspSolver::read() {
    ifstream input;
    input.open(this->getInFile()); // open .tsp file
    vector<int> ids, xaxis, yaxis; // vectors to store IDs, X coords and Y coords
    vector<string> info; // vector to store general info about city
    string line;
    while (getline(input, line))
    {
        if (isalpha(line[0])) { // if first character is alphabetic it's city info
            size_t div = line.find(' '); // find first space char
            info.push_back(line.substr(div + 1)); // add content after space char
        } else {
            stringstream linestream(line);
            string idx, x, y;
            if (linestream >> idx >> x >> y) {
                ids.push_back(stoi(idx)); // convert ID to int
                xaxis.push_back(stoi(x)); // convert X coord to int
                yaxis.push_back(stoi(y)); // convert Y coord to int
            }
        }
    }
    // store private variables
    this->city = info[0]; // store city name
    this->size = stoi(info[2]); // store dimensions
    this->ids = ids; // store IDs
    this->xaxis = xaxis; // store X coords
    this->yaxis = yaxis; // store Y coords
}

// Create Adjacency Matrix
void TspSolver::makeAdjList() {
    // declare adjMatrix as vector of vector of pairs :(weight, vertex)
    // adjList[u_id - 1][v_id - 1] = (weight, v_id) -> weight for (u_id, v_id) edge
    vector<vector<Pair> > adjList(this->size, vector<Pair> (this->size));
    int u, v;
    long long int x1, x2, y1, y2;
    for (int i = 0; i < this->size; i++)
    {
        u = this->ids[i]; // u is the location ID -> u = i + 1
        x1 = this->xaxis[i], y1 = this->yaxis[i]; // x,y for node u
        int dist;
        for (int j = 0; j < this->size; j++)
        {
            x2 = this->xaxis[j], y2 = this->yaxis[j]; // x,y for node v
            v = this->ids[j]; // v is the location ID -> v = j + 1
            if (u == v) {
                adjList[i][j] = make_pair(0, u); // for same node add edge of 0
            } else {
                dist = euclid(x1, x2, y1, y2); // calculate eucledian distance between u and v
                Pair way1 = make_pair(dist, v); // create edge Pair (dist, v)
                Pair way2 = make_pair(dist, u); // create edge Pair (dist, u) because graph is undirected
                adjList[i][j] = way1; // add u edge
                adjList[j][i] = way2; // add v edge
            }
        }
    }
    this->adjList = adjList; // store adjMatrix as private variable
}

// Print Adj Matrix
void TspSolver::displayAdjList(vector<vector<Pair> > adjList) {
    int parent;
    for (int i = 0; i < this->size; i++) {
        Pair edge;
        parent = i + 1;
        cout << "Node " << parent << ":";
        for (int j = 0; j < this->size; j ++) {
            edge = adjList[i][j];
            cout << " - (" << edge.second << ", " << edge.first << ")";
        }
        cout << endl;
    }
}

// Write Solution File
void TspSolver::writeSol() {
    try {
        ofstream outfile(this->outFile); // open file
        if (!outfile.is_open()) {
            throw runtime_error("Could not open file.");
        }
        outfile << fixed << this->quality << setprecision(7) << endl; // First line is tour quality
        for (int i = 0; i < this->tour.size(); i++) {
            outfile << this->tour[i]; // add location from tour
            if (i != this->tour.size() - 1) {outfile << ",";} // add comma except to last element
        }
        outfile.close();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl; // Log the error
    }
}

// constructor
TspSolver::TspSolver(string inFile, string method, string cutoff, string seed) {
    this->setInFile(inFile);
    this->setMethod(method);
    this->setCutoff(cutoff);
    this->setSeed(seed);
    this->read();
    this->makeAdjList();
    this->setOutFile();
}

// set a tour as the solution of the solver
void TspSolver::setTour(vector<int> tour) {
    this->tour = tour;

    // compute quality of the tour
    this->quality = computeTourLength(getAdjList(), getTour());

    // check whether tour is complete
    int dims = this->getSize();
    string isTourFull = (this->tour.size() - 1) == dims ? "Yes" : "No";
    this->full = isTourFull;
}

inline int TspSolver::computeTourLength(const vector<vector<Pair> >& adjList, const vector<int>& tour) {
    int cost = 0;
    size_t tourSize = tour.size();

    for (size_t i = 0; i < tourSize - 1; ++i) {
        int u = tour[i];
        int v = tour[i + 1];
        cost += adjList[u - 1][v - 1].first;
    }

    return cost;
}