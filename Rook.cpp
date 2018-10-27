// Rook.cpp
// This file contains the implementation of the class Rook

// ------------------------- includes --------------------------

#include "Rook.h"

// --------------------- const definitions ---------------------

// difference between ranks or files in a legal rook's move
constexpr int ROOK_DIFF = 0;

// ------------------- class implementation --------------------

/**
 * @brief checks whether dest is in Rook's range of movement, i.e. any number of squares along a
 * rank or file.
 * @param dest - a square on the board, e.g. "A1"
 * @return true if dest is in Rook's range of movement, false otherwise
 */
bool Rook::canReach(const string& dest, bool) const
{
    int fileDiff = abs(dest[FILE_INDEX] - _position[FILE_INDEX]);
    int rankDiff = abs(dest[RANK_INDEX] - _position[RANK_INDEX]);
    return (fileDiff == ROOK_DIFF) || (rankDiff == ROOK_DIFF);
}

/**
 * @brief generates a path between Rook's position and dest, excluding position and dest. assumes:
 * Rook.canReach(dest) = true. allocates memory in freestore.
 * @param dest - a square on the board, e.g. "A1"
 * @return a vector of squares on the board, representing a path between Rook and dest.
 */
vector<string>* Rook::getPathTo(const string& dest) const // assume: canReach() = true
{
    return Piece::getPathTo(dest);
}