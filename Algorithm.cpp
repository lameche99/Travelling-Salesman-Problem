#include "algos.h"

int Algorithm::euclid(int x1, int x2, int y1, int y2) {
    double x = x1 - x2;
    double y = y1 - y2;
    double dist = sqrt(pow(x, 2) + pow(y, 2));
    return int(dist);
}

void Algorithm::read() {
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

void Algorithm::makeAdjList(vector<Pair> adjList[]) {
    for (int i = 0; i < this->size; i++)
    {
        int u = this->ids[i];
        int x1 = this->xaxis[i], y1 = this->yaxis[i];
        int dist;
        for (int j = 0; j < this->size; j++)
        {
            if (i == j) {
                adjList[u].push_back(make_pair(0, u));
            } else {
                int x2 = this->xaxis[j], y2 = this->yaxis[j];
                int v = this->ids[j];
                dist = euclid(x1, x2, y1, y2);
                adjList[u].push_back(make_pair(dist, v));
                adjList[v].push_back(make_pair(dist, u));
            }
        }
    }
}