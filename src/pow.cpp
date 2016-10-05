// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "pow.h"

#include "arith_uint256.h"
#include "chain.h"
#include "primitives/block.h"
#include "uint256.h"
#include "util.h"

#include <math.h>

unsigned int KimotoGravityWell(const CBlockIndex* pindexLast, const CBlockHeader *pblock, uint64_t TargetBlocksSpacingSeconds, uint64_t PastBlocksMin, uint64_t PastBlocksMax, const Consensus::Params& params)
{
	/* current difficulty formula, megacoin - kimoto gravity well */
	const CBlockIndex *BlockLastSolved = pindexLast;
	const CBlockIndex *BlockReading = pindexLast;
	unsigned int nProofOfWorkLimit = UintToArith256(params.powLimit).GetCompact();

	uint64_t PastBlocksMass = 0;
	int64_t PastRateActualSeconds = 0;
	int64_t PastRateTargetSeconds = 0;
	double PastRateAdjustmentRatio = double(1);
	arith_uint256 PastDifficultyAverage;
	arith_uint256 PastDifficultyAveragePrev;
	double EventHorizonDeviation;
	double EventHorizonDeviationFast;
	double EventHorizonDeviationSlow;

	if (BlockLastSolved == NULL || BlockLastSolved->nHeight == 0 || (uint64_t)BlockLastSolved->nHeight < PastBlocksMin) {
		return nProofOfWorkLimit;
	}
	int64_t LatestBlockTime = BlockLastSolved->GetBlockTime();
	for (unsigned int i = 1; BlockReading && BlockReading->nHeight > 0; i++) {
		if (PastBlocksMax > 0 && i > PastBlocksMax) { break; }
		PastBlocksMass++;

        PastDifficultyAverage.SetCompact(BlockReading->nBits);

		if (i > 1) {
        PastDifficultyAverage = ((PastDifficultyAverage - PastDifficultyAveragePrev) / i) + PastDifficultyAveragePrev;  }
		PastDifficultyAveragePrev = PastDifficultyAverage;

		if (LatestBlockTime < BlockReading->GetBlockTime()) {
			if (BlockReading->nHeight > 100000) LatestBlockTime = BlockReading->GetBlockTime();
		}

		PastRateActualSeconds = LatestBlockTime - BlockReading->GetBlockTime();

		if (BlockReading->nHeight > 100000) {
			if (PastRateActualSeconds < 1) { PastRateActualSeconds = 1; }
		} else {
			if (PastRateActualSeconds < 0) { PastRateActualSeconds = 0; }
		}

		PastRateTargetSeconds = TargetBlocksSpacingSeconds * PastBlocksMass;
		PastRateAdjustmentRatio = double(1);

		if (PastRateActualSeconds != 0 && PastRateTargetSeconds != 0) {
			PastRateAdjustmentRatio = double(PastRateTargetSeconds) / double(PastRateActualSeconds);
		}
		EventHorizonDeviation = 1 + (0.7084 * pow((double(PastBlocksMass)/double(28.2)), -1.228));
		EventHorizonDeviationFast = EventHorizonDeviation;
		EventHorizonDeviationSlow = 1 / EventHorizonDeviation;

		if (PastBlocksMass >= PastBlocksMin) {
			if ((PastRateAdjustmentRatio <= EventHorizonDeviationSlow) || (PastRateAdjustmentRatio >= EventHorizonDeviationFast)) {
				assert(BlockReading);
				break;
			}
		}
		if (BlockReading->pprev == NULL) {
			assert(BlockReading);
			break;
		}
		BlockReading = BlockReading->pprev;
	}

    const arith_uint256 bnPowLimit = UintToArith256(params.powLimit);
	arith_uint256 bnNew(PastDifficultyAverage);
	if (PastRateActualSeconds != 0 && PastRateTargetSeconds != 0) {
		bnNew *= PastRateActualSeconds;
		bnNew /= PastRateTargetSeconds;
	}
	if (bnNew > bnPowLimit) { bnNew = bnPowLimit; }

	return bnNew.GetCompact();
}

unsigned int GetNextWorkRequired_OLD(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params)
{
    unsigned int nProofOfWorkLimit = UintToArith256(params.powLimit).GetCompact();

    // Genesis block
    if (pindexLast == NULL)
        return nProofOfWorkLimit;

    // Only change once per difficulty adjustment interval
    if ((pindexLast->nHeight+1) % params.DifficultyAdjustmentInterval() != 0)   {        
        return pindexLast->nBits;
    }

    // GameCredits: This fixes an issue where a 51% attack can change difficulty at will.
    // Go back the full period unless it's the first retarget after genesis. Code courtesy of Art Forz
    int blockstogoback = params.DifficultyAdjustmentInterval() - 1;
    if ((pindexLast->nHeight+1) != params.DifficultyAdjustmentInterval())
        blockstogoback = params.DifficultyAdjustmentInterval();

    // Go back by what we want to be 14 days worth of blocks
    const CBlockIndex* pindexFirst = pindexLast;
    for (int i = 0; pindexFirst && i < blockstogoback; i++)
        pindexFirst = pindexFirst->pprev;
    assert(pindexFirst);

    // Limit adjustment step
    int64_t nActualTimespan = pindexLast->GetBlockTime() - pindexFirst->GetBlockTime();

    if (nActualTimespan < params.nPowTargetTimespan/4)
        nActualTimespan = params.nPowTargetTimespan/4;
    if (nActualTimespan > params.nPowTargetTimespan*4)
        nActualTimespan = params.nPowTargetTimespan*4;

    // Retarget
    const arith_uint256 bnPowLimit = UintToArith256(params.powLimit);
    arith_uint256 bnNew;
    arith_uint256 bnOld;
    bnNew.SetCompact(pindexLast->nBits);
    bnOld = bnNew;
    bnNew *= nActualTimespan;
    bnNew /= params.nPowTargetTimespan;

    if (bnNew > bnPowLimit)
        bnNew = bnPowLimit;

    /// debug print
    LogPrintf("GetNextWorkRequired RETARGET\n");
    LogPrintf("Before: %08x  %s\n", pindexLast->nBits, bnOld.ToString());
    LogPrintf("After:  %08x  %s\n", bnNew.GetCompact(), bnNew.ToString());

    return bnNew.GetCompact();
}

unsigned int GetNextWorkRequired_V3(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params)
{
    unsigned int nProofOfWorkLimit = UintToArith256(params.powLimit).GetCompact();

    // Genesis block
    if (pindexLast == NULL)
        return nProofOfWorkLimit;

    const CBlockIndex* pindexFirst = pindexLast->pprev;
    int64_t nActualSpacing = pindexLast->GetBlockTime() - pindexFirst->GetBlockTime();

    // limit the adjustment
    if (nActualSpacing < params.nPowTargetSpacingnew/16)
        nActualSpacing = params.nPowTargetSpacingnew/16;
    if (nActualSpacing > params.nPowTargetSpacingnew*16)
        nActualSpacing = params.nPowTargetSpacingnew*16;

    // Retarget
    const arith_uint256 bnPowLimit = UintToArith256(params.powLimit);
    arith_uint256 bnNew;
    bnNew.SetCompact(pindexLast->nBits);
    bnNew *= ((params.DifficultyAdjustmentIntervalnew() - 1) * params.nPowTargetSpacingnew + 2 * nActualSpacing);
    bnNew /= ((params.DifficultyAdjustmentIntervalnew() + 1) * params.nPowTargetSpacingnew);

    if (bnNew > bnPowLimit)
        bnNew = bnPowLimit;

    return bnNew.GetCompact();
}

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params)
{
	unsigned int nHeight = pindexLast->nHeight + 1;

	// Settings for GameCredits KGW
    unsigned int TimeDaySeconds = 60 * 60 * 24;
    int64_t PastSecondsMin = TimeDaySeconds * 0.01;
    int64_t PastSecondsMax = TimeDaySeconds * 0.14;
    int64_t BlocksTargetSpacing = 0;

	if(nHeight < 15332) {
		// KGW v1
       return GetNextWorkRequired_OLD(pindexLast, pblock, params);
	} 
	else if(nHeight < 1036320) {
		    // Former 30 Second Block Target, KGW 2 Prefork
            BlocksTargetSpacing = 30;
			uint64_t PastBlocksMin = PastSecondsMin / BlocksTargetSpacing;
	        uint64_t PastBlocksMax = PastSecondsMax / BlocksTargetSpacing;
	        return KimotoGravityWell(pindexLast, pblock, BlocksTargetSpacing, PastBlocksMin, PastBlocksMax, params);
	} 
	else if(nHeight < 1096772) {
		    // New 90 Second Block Target, KGW 2 Postfork
		    BlocksTargetSpacing = 90;
		    uint64_t PastBlocksMin = PastSecondsMin / BlocksTargetSpacing;
	        uint64_t PastBlocksMax = PastSecondsMax / BlocksTargetSpacing;
	        return KimotoGravityWell(pindexLast, pblock, BlocksTargetSpacing, PastBlocksMin, PastBlocksMax, params);
	}
	else {
			return GetNextWorkRequired_V3(pindexLast, pblock, params);
	} 
}

bool CheckProofOfWork(uint256 hash, unsigned int nBits, const Consensus::Params& params)
{
    bool fNegative;
    bool fOverflow;
    arith_uint256 bnTarget;

    bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

    // Check range
    if (fNegative || bnTarget == 0 || fOverflow || bnTarget > UintToArith256(params.powLimit))
        return error("CheckProofOfWork(): nBits below minimum work");

    // Check proof of work matches claimed amount
    if (UintToArith256(hash) > bnTarget)
        return error("CheckProofOfWork(): hash doesn't match nBits");

    return true;
}

arith_uint256 GetBlockProof(const CBlockIndex& block)
{
    arith_uint256 bnTarget;
    bool fNegative;
    bool fOverflow;
    bnTarget.SetCompact(block.nBits, &fNegative, &fOverflow);
    if (fNegative || fOverflow || bnTarget == 0)
        return 0;
    // We need to compute 2**256 / (bnTarget+1), but we can't represent 2**256
    // as it's too large for a arith_uint256. However, as 2**256 is at least as large
    // as bnTarget+1, it is equal to ((2**256 - bnTarget - 1) / (bnTarget+1)) + 1,
    // or ~bnTarget / (nTarget+1) + 1.
    return (~bnTarget / (bnTarget + 1)) + 1;
}

int64_t GetBlockProofEquivalentTime(const CBlockIndex& to, const CBlockIndex& from, const CBlockIndex& tip, const Consensus::Params& params)
{
    arith_uint256 r;
    int sign = 1;
    if (to.nChainWork > from.nChainWork) {
        r = to.nChainWork - from.nChainWork;
    } else {
        r = from.nChainWork - to.nChainWork;
        sign = -1;
    }
    r = r * arith_uint256(params.nPowTargetSpacing) / GetBlockProof(tip);
    if (r.bits() > 63) {
        return sign * std::numeric_limits<int64_t>::max();
    }
    return sign * r.GetLow64();
}
