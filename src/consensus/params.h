// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_PARAMS_H
#define BITCOIN_CONSENSUS_PARAMS_H

#include "uint256.h"

namespace Consensus {
/**
 * Parameters that influence chain consensus.
 */
struct Params {
    uint256 hashGenesisBlock;
    int nSubsidyHalvingInterval;
    /** Proof of work parameters */
    uint256 powLimit;
    bool fPowAllowMinDifficultyBlocks;
    int64_t nPowTargetSpacing;
    int64_t nPowTargetTimespan;
    int64_t nPowTargetSpacingnew;
    int64_t nPowTargetTimespannew;
    int64_t DifficultyAdjustmentInterval() const { return nPowTargetTimespan / nPowTargetSpacing; }
    int64_t DifficultyAdjustmentIntervalnew() const { return nPowTargetTimespannew / nPowTargetSpacingnew; }
};
} // namespace Consensus

#endif // BITCOIN_CONSENSUS_PARAMS_H
