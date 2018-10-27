// King.cpp
// This file contains the implementation of the class King

// ------------------------- includes --------------------------

#include "King.h"

// --------------------- const definitions ---------------------

// max difference between ranks or files in a legal king's move
constexpr int KING_RANGE = 1;

// ------------------- class implementation --------------------

/**
 * @brief checks whether dest is in King's range of movement, i.e. one square in any direction.
 * @param dest - a square on the board, e.g. "A1"
 * @return true if dest is in King's range of movement, false otherwise
 */
bool King::canReach(const string& dest, bool) const
{
    int fileDiff = abs(dest[FILE_INDEX] - _position[FILE_INDEX]);
    int rankDiff = abs(dest[RANK_INDEX] - _position[RANK_INDEX]);
    return (fileDiff <= KING_RANGE) && (rankDiff <= KING_RANGE);
}