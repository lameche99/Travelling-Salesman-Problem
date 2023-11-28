#include "util.h"
#include "approx.h"

int main(int argc, char** argv) {
    time_t start, end;
    double execTime;
    Approx algo(argv[1], argv[2], argv[3]);
    time(&start); // start clock
    ios_base::sync_with_stdio(false);
    algo.tspSolver();
    time(&end); // end clock
    execTime = double(end - start);
    algo.writeSol();
    cout << "Quality: " << fixed << algo.getQuality() << setprecision(7) << endl;
    cout << "Execution Time: " << fixed << execTime << setprecision(5) << endl; 
    cout << "Full Tour? " << algo.getVerdict() << endl;
    return 0;
}