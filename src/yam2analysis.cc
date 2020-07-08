#include "blsystem.h"

#include <lhef/lhef.h>

#include <fstream>
#include <iostream>

using std::cout;
using std::vector;

const double MNU = 0.0;

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
    // for (; !lhe.empty(); lhe = lhef::parseEvent(&filename), ++num_eve) {
    for (; num_eve < 3; lhe = lhef::parseEvent(&filename), ++num_eve) {
        const auto input = mkInputForBL(selectP(lhe), MNU);
        if (!input) { continue; }

        cout << input.value() << '\n';
    }

    cout << "-- " << num_eve << " events proceses.\n";
    filename.close();
}
