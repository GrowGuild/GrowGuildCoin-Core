// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

//for Logprintf
// #include <boost/filesystem/fstream.hpp>
#include <iostream>
#include <string>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xf2;
        pchMessageStart[1] = 0xf9;
        pchMessageStart[2] = 0xe5;
        pchMessageStart[3] = 0xeb;
        vAlertPubKey = ParseHex("0x04400b96e2259341b6963feba3e7373ad62bcffff5b446f542155372c95248a9cf3732c2050102bbf0c7760e1bbff6517d663b252d994e7c1c06faf020d83f5cc8");
        nDefaultPort = 55444;
        nRPCPort = 55420;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "YoucansmokemarijuanayoucaneatityoucanwearititsaperfectplantTommyChongh41l$m34g0l4202017";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();

        CTransaction txNew(1, 1505146800, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1505146800;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 1371509;
        hashGenesisBlock = genesis.GetHash();
     
        assert(hashGenesisBlock == uint256("0x00000315daec388b84b69bf536b0ba31bdc86a38f1dd17491af6fec1cde695f6"));
        assert(genesis.hashMerkleRoot == uint256("0x953ca67c6c183c50175c3c9f1734ccf635b0a0e66e6aa50d157b1cf0c11cd26b"));

        vSeeds.push_back(CDNSSeedData("seed1.bittropolis.com",  "seed1.bittropolis.com"));
        vSeeds.push_back(CDNSSeedData("seed2.bittropolis.com",  "seed2.bittropolis.com"));
        vSeeds.push_back(CDNSSeedData("seed3.bittropolis.com",  "seed3.bittropolis.com"));
        vSeeds.push_back(CDNSSeedData("seed4.bittropolis.com",  "seed4.bittropolis.com"));
        vSeeds.push_back(CDNSSeedData("seed5.bittropolis.com",  "seed5.bittropolis.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 38);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 98);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 240);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0xEE)(0x80)(0x28)(0x6A).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0xEE)(0x80)(0x31)(0xE8).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 100;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xe5;
        pchMessageStart[1] = 0xFA;
        pchMessageStart[2] = 0xCF;
        pchMessageStart[3] = 0xFC;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0x0429f6baea4f15db6a152b071d2d7bc5510e673dede708bb7b8b426de78c600f2e3de04f987cc6df7b7a9de7c68ad1b6a1551dc22358d23fb617afcbdb4bb00ec8");
        nDefaultPort = 42001;
        nRPCPort = 42000;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 57829;
        hashGenesisBlock = genesis.GetHash();
       
        assert(hashGenesisBlock == uint256("0x000068ad37bbbb2d31e349925a78249f703b7c626d0ec7f1f99498f9960ecbc7"));
        assert(genesis.hashMerkleRoot == uint256("0x953ca67c6c183c50175c3c9f1734ccf635b0a0e66e6aa50d157b1cf0c11cd26b"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 127);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 255);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x76)(0xC0)(0xFD)(0xFB).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x76)(0xC1)(0x07)(0x7A).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xf7;
        pchMessageStart[1] = 0xb9;
        pchMessageStart[2] = 0x8b;
        pchMessageStart[3] = 0xd8;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        
        nDefaultPort = 18444;
        strDataDir = "regtest";
        genesis.nTime = 1411111111;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 6;
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x2f124be2af1b61cf843491478e6971f9c538099e4f8d5312e7f7964c9ee5b28e"));
        assert(genesis.hashMerkleRoot == uint256("0x953ca67c6c183c50175c3c9f1734ccf635b0a0e66e6aa50d157b1cf0c11cd26b"));
        
        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
