#include "blsystem.h"

#include <lhef/lhef.h>

#include <fstream>
#include <iostream>

using std::cout;
using std::vector;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: yam2analysis.exe input\n"
                  << "    - input: Input file in "
                  << "Les Houches Event File format\n";
        return 1;
    }

    std::ifstream filename(argv[1]);
    if (!filename) {
        std::cerr << "-- Cannot open input file \"" << argv[1] << "\".\n";
        return 1;
    } else {
        cout << "-- Processing \"" << argv[1] << "\" ...\n";
    }

    auto lhe = lhef::parseEvent(&filename);
    int num_eve = 0;
    // for (; !lhe.empty(); lhe = lhef::parseEvent(&filename)) {
    for (; num_eve < 3; lhe = lhef::parseEvent(&filename)) {
        ++num_eve;

        selectP(lhe);
    }

    cout << "-- " << num_eve << " events proceses.\n";
    filename.close();
}
