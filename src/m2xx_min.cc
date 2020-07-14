#include "blsystem.h"

#include "yam2.h"

#include <lhef/lhef.h>

#include <fstream>
#include <iomanip>
#include <iostream>

#ifdef DEBUG
#include <chrono>
using namespace std::chrono;
#endif

using std::cout;

const double MNU = 0.0;
const double TOL = 1.0e-3;

void writeNullOutput(std::ofstream &outfile) {
    outfile << std::setw(12) << std::setprecision(7) << -1.0 << '\t' << -1
            << '\n';
}

int main(int argc, char *argv[]) {
#ifdef DEBUG
    if (argc != 4)
#else
    if (argc != 3)
#endif
    {
        std::cerr << "Usage: m2xx_min.exe input output\n"
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

#ifdef DEBUG
    std::ofstream ftime;
    ftime.open((argv[3]), std::ofstream::out | std::ofstream::app);
    auto start = high_resolution_clock::now();
#endif

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

        auto m2sol = yam2::m2XX(input.value(), TOL);
        if (!m2sol) {
            writeNullOutput(outfile);
            continue;
        }
        // cout << m2sol.value() << '\n';
        outfile << std::setw(12) << std::setprecision(7) << m2sol.value().m2()
                << '\t' << m2sol.value().neval_objf() << '\n';
    }
#ifdef DEBUG
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    ftime << duration.count() * 1.0e-6 << '\n';
#endif

    cout << "-- " << num_eve << " events processed.\n";
    infile.close();
}
