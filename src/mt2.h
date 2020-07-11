#ifndef YAM2_ANALYSIS_SRC_MT2_H_
#define YAM2_ANALYSIS_SRC_MT2_H_

#include "lester_mt2_bisect.h"

#include "yam2.h"

double getMT2(const yam2::InputKinematics& inp) {
    const auto p1 = inp.p1();
    const auto p2 = inp.p2();
    const auto ptmiss = inp.ptmiss();
    const double minv = inp.minv().value;

    asymm_mt2_lester_bisect::disableCopyrightMessage();
    const double mt2 = asymm_mt2_lester_bisect::get_mT2(
        p1.m(), p1.px(), p1.py(), p2.m(), p2.px(), p2.py(), ptmiss.px(),
        ptmiss.py(), minv, minv);
    return mt2 * inp.scale();
}

#endif  // YAM2_ANALYSIS_SRC_MT2_H_
