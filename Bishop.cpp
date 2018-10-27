// Bishop.cpp
// This file contains the implementation of the class Bishop

// ------------------------- includes --------------------------

#include "Bishop.h"

// ------------------- class implementation --------------------

/**
 * @brief checks whether dest is in Bishop's range of movement, i.e. any number of squares
 * diagonally.
 * @param dest - a square on the board, e.g. "A1"
 * @return true if dest is in Bishop's range of movement, false otherwise
 */
bool Bishop::canReach(const string& dest, bool) const
{
    int fileDiff = abs(dest[FILE_INDEX] - _position[FILE_INDEX]);
    int rankDiff = abs(dest[RANK_INDEX] - _position[RANK_INDEX]);
    return fileDiff == rankDiff;
}

/**
 * @brief generates a path between Bishop's position and dest, excluding position and dest. assumes:
 * Bishop.canReach(dest) = true. allocates memory in freestore.
 * @param dest - a square on the board, e.g. "A1"
 * @return a vector of squares on the board, representing a path between Bishop and dest.
 */
vector<string>* Bishop::getPathTo(const string& dest) const // assume: canReach() = true
{
    return Piece::getPathTo(dest);
}