#include "util.h"

// eucledian distance
int Util::euclid(int x1, int x2, int y1, int y2) {
    double x = x1 - x2;
    double y = y1 - y2;
    double dist = sqrt(pow(x, 2) + pow(y, 2));
    return int(dist + 0.5);
}

// read input data
void Util::read() {
    ifstream input;
    input.open(this->getInFile());
    vector<int> ids, xaxis, yaxis;
    vector<string> info;
    string line;
    while (getline(input, line))
    {
        if (isalpha(line[0])) {
            size_t div = line.find(' ');
            info.push_back(line.substr(div + 1));
        } else {
            stringstream linestream(line);
            string idx, x, y;
            if (linestream >> idx >> x >> y) {
                ids.push_back(stoi(idx));
                xaxis.push_back(stoi(x));
                yaxis.push_back(stoi(y));
            }
        }
    }
    this->city = info[0];
    this->size = info.size() == 6 ? stoi(info[2]) : stoi(info[3]);
    this->ids = ids;
    this->xaxis = xaxis;
    this->yaxis = yaxis;
}

// Create Adjacency Matrix
void Util::makeAdjList() {
    vector<vector<Pair> > adjList(this->size, vector<Pair> (this->size));
    int u, v;
    long long int x1, x2, y1, y2;
    for (int i = 0; i < this->size; i++)
    {
        u = this->ids[i];
        x1 = this->xaxis[i], y1 = this->yaxis[i];
        int dist;
        for (int j = 0; j < this->size; j++)
        {
            x2 = this->xaxis[j], y2 = this->yaxis[j];
            v = this->ids[j];
            if (u == v) {
                adjList[i][j] = make_pair(0, u);
            } else {
                dist = euclid(x1, x2, y1, y2);
                Pair way1 = make_pair(dist, v);
                Pair way2 = make_pair(dist, u);
                adjList[i][j] = way1;
                adjList[j][i] = way2;
            }
        }
    }
    this->adjList = adjList;
}

// Print Adj Matrix
void Util::displayAdjList(vector<vector<Pair> > adjList) {
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
void Util::writeSol() {
    try {
        ofstream outfile(this->outFile); // open file
        if (!outfile.is_open()) {
            throw runtime_error("Could not open file.");
        }
        outfile << fixed << this->quality << setprecision(7) << endl; // First line is tour quality
        for (int i = 0; i < this->tour.size(); i++) {
            outfile << this->tour[i];
            if (i != this->tour.size() - 1) {outfile << ",";} // add comma except to last element
        }
        outfile.close();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl; // Log the error
    }
}