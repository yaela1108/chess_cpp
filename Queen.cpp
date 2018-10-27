// Queen.cpp
// This file contains the implementation of the class Queen

// ------------------------- includes --------------------------

#include "Queen.h"

// --------------------- const definitions ---------------------

// difference between ranks or files in a legal queen's move
constexpr int QUEEN_DIFF = 0;

// ------------------- class implementation --------------------

/**
 * @brief checks whether dest is in Queen's range of movement, i.e. any number of squares along a
 * rank, file, or diagonal.
 * @param dest - a square on the board, e.g. "A1"
 * @return true if dest is in Queen's range of movement, false otherwise
 */
bool Queen::canReach(const string& dest, bool) const
{
    int fileDiff = abs(dest[FILE_INDEX] - _position[FILE_INDEX]);
    int rankDiff = abs(dest[RANK_INDEX] - _position[RANK_INDEX]);
    return (fileDiff == QUEEN_DIFF) || (rankDiff == QUEEN_DIFF) || (fileDiff == rankDiff);
}

/**
 * @brief generates a path between Queen's position and dest, excluding position and dest. assumes:
 * Queen.canReach(dest) = true. allocates memory in freestore.
 * @param dest - a square on the board, e.g. "A1"
 * @return a vector of squares on the board, representing a path between Queen and dest.
 */
vector<string>* Queen::getPathTo(const string& dest) const // assume: canReach() = true
{
    return Piece::getPathTo(dest);
}