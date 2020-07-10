#ifndef YAM2_ANALYSIS_SRC_BLSYSTEM_H_
#define YAM2_ANALYSIS_SRC_BLSYSTEM_H_

#include <lhef/lhef.h>
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

#endif  // YAM2_ANALYSIS_SRC_BLSYSTEM_H_
