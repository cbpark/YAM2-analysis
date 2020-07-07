#include <fstream>
#include <iostream>
#include "lhef/lhef.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: test_parse input\n"
                  << "    - input: Input file in "
                  << "Les Houches Event File format\n";
        return 1;
    }

    std::ifstream filename(argv[1]);
    if (!filename) {
        std::cerr << "-- Cannot open input file \"" << argv[1] << "\".\n";
        return 1;
    } else {
        std::cout << "-- Reading \"" << argv[1] << "\" ...\n";
    }

    lhef::Event lhe = lhef::parseEvent(&filename);
    int num_eve = 0;
    // for (; !lhe.empty(); lhe = lhef::parseEvent(&filename)) {
    for (; num_eve < 3; lhe = lhef::parseEvent(&filename)) {
        ++num_eve;
        auto toplines = lhef::particleLinesOf(lhef::Top, lhe);
        for (const auto& top : toplines) {
            auto daughters_of_top = lhef::finalDaughters(top, lhe);
            std::cout << "---- Daughters of one top quark:\n"
                      << lhef::show(daughters_of_top) << '\n';
        }
    }

    std::cout << "-- " << num_eve << " events parsed.\n";
    filename.close();
}
