#include "blsystem.h"

#include "yam2.h"

#include <lhef/lhef.h>

#include <fstream>
#include <iomanip>
#include <iostream>

using std::cout;

const double MNU = 0.0;
const double TOL = 1.0e-2;

void writeNullOutput(std::ofstream &outfile) {
    outfile << std::setw(12) << std::setprecision(7) << -1.0 << '\t' << -1
            << '\n';
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: m2xc_sqp.exe input output\n"
                  << "  - input: Input file in "
                  << "Les Houches Event File format\n"
                  << "  - output: output file.\n";
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "-- Cannot open input file \"" << argv[1] << "\".\n";
        return 1;
    } else {
        cout << "-- Processing \"" << argv[1] << "\" ...\n";
    }

    std::ofstream outfile(argv[2]);
    outfile << "# M2, number of evals\n";

    auto ev = lhef::parseEvent(&infile);
    int num_eve = 0;
    for (; !ev.empty(); ev = lhef::parseEvent(&infile), ++num_eve) {
        // for (; num_eve < 10; ev = lhef::parseEvent(&infile), ++num_eve) {
        const auto input = mkInputForBL(selectP(ev), MNU);
        if (!input) {
            writeNullOutput(outfile);
            continue;
        }

        // cout << input.value() << '\n';

        auto m2sol = yam2::m2XCSQP(input.value(), TOL);
        if (!m2sol) {
            writeNullOutput(outfile);
            continue;
        }
        // cout << m2sol.value() << '\n';
        outfile << std::setw(12) << std::setprecision(7) << m2sol.value().m2()
                << '\t' << m2sol.value().neval_objf() << '\n';
    }

    cout << "-- " << num_eve << " events processed.\n";
    infile.close();
}
