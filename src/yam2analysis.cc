#include "momentum.h"

#include "lhef/lhef.h"
#include "lhef/particle.h"
#include "lhef/pid.h"

#include <algorithm>
#include <fstream>
#include <iostream>

using std::cout;

yam2::FourMomentum getFourMomentum(const lhef::Particle& p) {
    return {p.energy(), p.px(), p.py(), p.pz()};
}

int main(int argc, char* argv[]) {
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
        cout << "-- Reading \"" << argv[1] << "\" ...\n";
    }

    lhef::ParticleID is_lepton;
    std::merge(lhef::Electron.cbegin(), lhef::Electron.cend(),
               lhef::Muon.cbegin(), lhef::Muon.cend(),
               std::back_inserter(is_lepton));

    lhef::ParticleID is_neutrino;
    std::merge(lhef::ElecNeutrino.cbegin(), lhef::ElecNeutrino.cend(),
               lhef::MuonNeutrino.cbegin(), lhef::MuonNeutrino.cend(),
               std::back_inserter(is_neutrino));

    auto lhe = lhef::parseEvent(&filename);
    int num_eve = 0;
    // for (; !lhe.empty(); lhe = lhef::parseEvent(&filename)) {
    for (; num_eve < 3; lhe = lhef::parseEvent(&filename)) {
        ++num_eve;

        const auto toplines = lhef::particleLinesOf(lhef::Top, lhe);
        if (toplines.size() != 2) { break; }

        std::vector<lhef::Particles> topchild;
        for (const auto& top : toplines) {
            topchild.push_back(lhef::finalDaughters(top, lhe));
        }
        for (const auto& c : topchild) {
            cout << lhef::show(c) << '\n';
            auto bquark = lhef::selectByID(lhef::Bottom, c);
            cout << "bquark: " << lhef::show(bquark) << '\n';
            auto lepton = lhef::selectByID(is_lepton, c);
            cout << "lepton: " << lhef::show(lepton) << '\n';
            auto neutrino = lhef::selectByID(is_neutrino, c);
            cout << "neutrino: " << lhef::show(neutrino) << '\n';
        }
    }

    cout << "-- " << num_eve << " events parsed.\n";
    filename.close();
}
