// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (     0, uint256("0x91ec5f25ee9a0ffa1af7d4da4db9a552228dd2dc77cdb15b738be4e1f55f30ee"))
		(  4506, uint256("0x71d4d0454e12191a77078d42f09bef60e8687a9fe3890cbb42d77151f8d55683"))
		(  5607, uint256("0x1a2ca64c0dee6bdbbe3f1d9ec44c262b20a4a395851a6dff50d9eedf0ed7d0d4"))
		( 14707, uint256("0x7ff1c13ceea15676c8dfda9dd4bf5e7adc7c36be8df455c8944051f9bddf5989"))
		( 15260, uint256("0x52988b844cd4d548e3bed745420c9ba90db2be01c98f08bb6511fcbae217f74e"))
		( 15589, uint256("0xe4c056e91d0ae4bfe6c95a6f48ec52dfdcf1bb3208e4e76574032d91bba676c2"))
		( 55545, uint256("0x3a3df3801fb583944cd1df14a01f4c41646bb38ad133211d4a855751654aafa7"))
		( 91063, uint256("0x029de26d43f0c35a781f4a0f505bea7768b767b3be71081075c5b01ae1f3314f"))
		( 92883, uint256("0x9eb06971435ec72ecca7bb2c84f3d768e1d7228d310ed92224b88a1bd5472b8b"))
		( 148997, uint256("0xb5f37d9a5c5045a5214460d99d6d7f2154687c5534217725465c5eda78acdabe"))
		( 246132, uint256("0x3fe39b954546d59a455493dccee4f9ed8fa0d94d9e64f98aeed28d293e074d25"))
		( 483425, uint256("0x9e73c7276ad00bbb2653ff7d78d247e2ba3360451deb4bc959ed93edf4438c14"))
		( 731930, uint256("0xa2117305047df0c85930f3851911c3e601b62594639e6585a7f88de99dedeb3a"))
		( 786440, uint256("0x9a37e1245975be76680f5a1da9da26ad3a9d5b78f4b5544328b74a769b9c7643"))
        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1418671473, // * UNIX timestamp of last checkpoint block
        963726,    // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        8000.0     // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet = 
        boost::assign::map_list_of
        (   0, uint256("91ec5f25ee9a0ffa1af7d4da4db9a552228dd2dc77cdb15b738be4e1f55f30ee"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1369685559,
        0,
        300
    };

    const CCheckpointData &Checkpoints() {
        if (fTestNet)
            return dataTestnet;
        else
            return data;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
