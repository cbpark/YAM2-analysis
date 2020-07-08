#include "blsystem.h"

#include "input.h"

#include <lhef/lhef.h>

#include <optional>
#include <vector>

using std::vector;
using yam2::FourMomentum;
using yam2::TransverseMomentum;

FourMomentum getFourMomentum(const lhef::Particle &p) {
    return {p.energy(), p.px(), p.py(), p.pz()};
}

auto getMomentaOf(const lhef::ParticleID &pid, const lhef::Particles &ps) {
    const auto particles = lhef::selectByID(pid, ps);
    vector<FourMomentum> mos;
    for (const auto &p : particles) { mos.push_back(getFourMomentum(p)); }
    return mos;
}

auto mkMET(vector<FourMomentum> &ps) {
    const auto psum = yam2::sum(ps);
    return psum.transverseVector();
}

std::optional<BLsystem> selectP(const lhef::Event &ev) {
    const auto toplines = lhef::particleLinesOf(lhef::Top, ev);
    if (toplines.size() != 2) { return {}; }

    vector<lhef::Particles> topchild;
    for (const auto &top : toplines) {
        topchild.push_back(lhef::finalDaughters(top, ev));
    }

    vector<FourMomentum> bquarks, leptons, neus;
    for (const auto &c : topchild) {
        const auto bs = getMomentaOf(lhef::Bottom, c);
        bquarks.insert(bquarks.end(), bs.cbegin(), bs.cend());

        const auto ls = getMomentaOf(lhef::LeptonIso, c);
        leptons.insert(leptons.end(), ls.cbegin(), ls.cend());

        const auto ns = getMomentaOf(lhef::Neutrino, c);
        neus.insert(neus.end(), ns.cbegin(), ns.cend());
    }

    if (bquarks.size() != 2 || leptons.size() != 2) { return {}; }

    const auto ptmiss = mkMET(neus);

    return {{bquarks, leptons, ptmiss}};
}

std::optional<yam2::InputKinematics> mkInputForBL(
    const std::optional<BLsystem> &ps, double minv) {
    if (!ps) { return {}; }
    const auto pv = ps.value();
    return yam2::mkInput(pv.bquarks_, pv.leptons_, pv.ptmiss_, minv);
}
