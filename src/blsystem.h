#ifndef YAM2_ANALYSIS_SRC_BLSYSTEM_H_
#define YAM2_ANALYSIS_SRC_BLSYSTEM_H_

#include <lhef/lhef.h>
#include <array>
#include <optional>
#include <vector>
#include "yam2.h"

struct BLsystem {
    std::vector<yam2::FourMomentum> bquarks_;
    std::vector<yam2::FourMomentum> leptons_;
    yam2::TransverseMomentum ptmiss_;

    BLsystem() = delete;
    BLsystem(const std::vector<yam2::FourMomentum> &bs,
             const std::vector<yam2::FourMomentum> &ls,
             const yam2::TransverseMomentum &ptmiss)
        : bquarks_(bs), leptons_(ls), ptmiss_(ptmiss) {}
};

std::optional<BLsystem> selectP(const lhef::Event &ev);

std::optional<yam2::InputKinematics> mkInputForBL(
    const std::optional<BLsystem> &ps, double minv);

inline std::optional<std::array<double, 2>> wMassReco(
    const BLsystem &blsystem, const yam2::M2Solution &sol) {
    const auto leptons = blsystem.leptons_;
    if (leptons.size() != 2) { return {}; }

    const auto w1 = leptons.front() + sol.k1();
    const auto w2 = leptons.back() + sol.k2();
    const std::array<double, 2> mw{w1.m(), w2.m()};
    return mw;
}

#endif  // YAM2_ANALYSIS_SRC_BLSYSTEM_H_
