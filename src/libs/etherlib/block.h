#pragma once
/*-------------------------------------------------------------------------------------------
 * QuickBlocks - Decentralized, useful, and detailed data from Ethereum blockchains
 * Copyright (c) 2018 Great Hill Corporation (http://quickblocks.io)
 *
 * This program is free software: you may redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version. This program is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details. You should have received a copy of the GNU General
 * Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *-------------------------------------------------------------------------------------------*/
/*
 * This file was generated with makeClass. Edit only those parts of the code inside
 * of 'EXISTING_CODE' tags.
 */
#include <map>
#include "etherlib.h"
#include "transaction.h"

namespace qblocks {

// EXISTING_CODE
typedef bool (*ADDRESSFUNC)(blknum_t bn, blknum_t tx, blknum_t tc, const SFAddress& addr, void *data);
typedef bool (*TRANSFUNC)(const CTransaction *trans, void *data);
// EXISTING_CODE

//--------------------------------------------------------------------------
class CBlock : public CBaseNode {
public:
    SFGas gasLimit;
    SFGas gasUsed;
    SFHash hash;
    blknum_t blockNumber;
    SFHash parentHash;
    SFAddress miner;
    uint64_t difficulty;
    double price;
    bool finalized;
    timestamp_t timestamp;
    CTransactionArray transactions;

public:
    CBlock(void);
    CBlock(const CBlock& bl);
    virtual ~CBlock(void);
    CBlock& operator=(const CBlock& bl);

    DECLARE_NODE(CBlock);

    const CBaseNode *getObjectAt(const string_q& fieldName, size_t index) const override;

    // EXISTING_CODE
    bool forEveryAddress      (ADDRESSFUNC func, TRANSFUNC filt, void *data);
    bool forEveryUniqueAddress(ADDRESSFUNC func, TRANSFUNC filt, void *data);
    bool operator==(const CBlock& bl) const;
    bool operator!=(const CBlock& bl) const { return !operator==(bl); }
    // EXISTING_CODE
    friend bool operator<(const CBlock& v1, const CBlock& v2);
    friend ostream& operator<<(ostream& os, const CBlock& item);

protected:
    void clear(void);
    void initialize(void);
    void duplicate(const CBlock& bl);
    bool readBackLevel(SFArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CBlock::CBlock(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CBlock::CBlock(const CBlock& bl) {
    // EXISTING_CODE
    // EXISTING_CODE
    duplicate(bl);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CBlock::~CBlock(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CBlock::clear(void) {
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CBlock::initialize(void) {
    CBaseNode::initialize();

    gasLimit = 0;
    gasUsed = 0;
    hash = "";
    blockNumber = 0;
    parentHash = "";
    miner = "";
    difficulty = 0;
    price = 0.0;
    finalized = 0;
    timestamp = 0;
    transactions.clear();

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CBlock::duplicate(const CBlock& bl) {
    clear();
    CBaseNode::duplicate(bl);

    gasLimit = bl.gasLimit;
    gasUsed = bl.gasUsed;
    hash = bl.hash;
    blockNumber = bl.blockNumber;
    parentHash = bl.parentHash;
    miner = bl.miner;
    difficulty = bl.difficulty;
    price = bl.price;
    finalized = bl.finalized;
    timestamp = bl.timestamp;
    transactions = bl.transactions;

    // EXISTING_CODE
    // EXISTING_CODE
    finishParse();
}

//--------------------------------------------------------------------------
inline CBlock& CBlock::operator=(const CBlock& bl) {
    duplicate(bl);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//-------------------------------------------------------------------------
inline bool operator<(const CBlock& v1, const CBlock& v2) {
    // EXISTING_CODE
    // EXISTING_CODE
    // No default sort defined in class definition, assume already sorted
    return true;
}

//---------------------------------------------------------------------------
typedef SFArrayBase<CBlock> CBlockArray;
extern SFArchive& operator>>(SFArchive& archive, CBlockArray& array);
extern SFArchive& operator<<(SFArchive& archive, const CBlockArray& array);

//---------------------------------------------------------------------------
extern SFArchive& operator<<(SFArchive& archive, const CBlock& blo);
extern SFArchive& operator>>(SFArchive& archive, CBlock& blo);

//---------------------------------------------------------------------------
// EXISTING_CODE
inline blknum_t bnFromPath(const string_q& path) {
    string_q p = substitute(path, ".bin", "");
    reverse(p); p = nextTokenClear(p, '/'); reverse(p);
    return toUnsigned(p);
}

//---------------------------------------------------------------------------
inline bool isBlockFinal(timestamp_t ts_block, timestamp_t ts_chain, timestamp_t seconds = (60 * 4)) {
    // Default to four minutes
    // If the distance from the front of the node's current view of the front of the chain
    // is more than the numbers of seconds provided, consider the block final (even if it isn't
    // in a perfectly mathematical sense
    return ((ts_chain - ts_block) > seconds);
}
extern bool isPotentialAddr(SFUintBN test, SFAddress& addrOut);
extern void processPotentialAddrs(blknum_t bn, blknum_t tx, blknum_t tc,
                                    const string_q& potList, ADDRESSFUNC func, void *data);

//---------------------------------------------------------------------------
class CAddressItem {
public:
    blknum_t blockNum;
    blknum_t transIndex;
    blknum_t traceId;
    SFAddress addr;
    CAddressItem(void)
        : blockNum(0), transIndex(0), traceId(0), addr("") { }
    CAddressItem(const CAddressItem& item)
        : blockNum(item.blockNum), transIndex(item.transIndex), traceId(item.traceId), addr(item.addr) { }
    CAddressItem& operator=(const CAddressItem& item) {
        blockNum = item.blockNum;
        transIndex = item.transIndex;
        traceId = item.traceId;
        addr = item.addr;
        return *this;
    }
    CAddressItem(blknum_t bn, blknum_t tx, blknum_t tc, const SFAddress& a)
        : blockNum(bn), transIndex(tx), traceId(tc), addr(a) { }
    friend bool operator<(const CAddressItem& v1, const CAddressItem& v2) {
        return v1.addr < v2.addr;
    }
    friend ostream& operator<<(ostream& os, const CAddressItem& item);
};
typedef map<CAddressItem, uint64_t> CAddressItemMap;
// EXISTING_CODE
}  // namespace qblocks

