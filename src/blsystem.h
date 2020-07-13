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

inline std::optional<yam2::InputKinematics> mkInputForBL(
    const std::optional<BLsystem> &ps, double minv, double mrel = 0.0) {
    if (!ps) { return {}; }
    const auto pv = ps.value();
    return yam2::mkInput(pv.bquarks_, pv.leptons_, pv.ptmiss_, yam2::Mass{minv},
                         yam2::Mass{mrel});
}

inline std::optional<std::array<double, 2>> wMassReco(
    const BLsystem &blsystem, const yam2::M2Solution &sol) {
    const auto leptons = blsystem.leptons_;
    if (leptons.size() != 2) { return {}; }

    const auto w1 = leptons.front() + sol.k1();
    const auto w2 = leptons.back() + sol.k2();
    return std::array<double, 2>{w1.m(), w2.m()};
}

#endif  // YAM2_ANALYSIS_SRC_BLSYSTEM_H_
