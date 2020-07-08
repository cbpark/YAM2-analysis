#ifndef YAM2_ANALYSIS_SRC_BLSYSTEM_H_
#define YAM2_ANALYSIS_SRC_BLSYSTEM_H_

#include "momentum.h"

#include <lhef/lhef.h>

#include <optional>
#include <vector>

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

#endif  // YAM2_ANALYSIS_SRC_BLSYSTEM_H_
