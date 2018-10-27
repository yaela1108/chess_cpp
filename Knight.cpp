// Knight.cpp
// This file contains the implementation of the class Knight

// ------------------------- includes --------------------------

#include "Knight.h"

// --------------------- const definitions ---------------------

// min difference between ranks or files in a legal knight's move
constexpr int KNIGHT_DIFF1 = 1;
// max difference between ranks or files in a legal knight's move
constexpr int KNIGHT_DIFF2 = 2;

// ------------------- class implementation --------------------

/**
 * @brief checks whether dest is in Knight's range of movement, i.e. two squares vertically and one
 * square horizontally, or two squares horizontally and one square vertically
 * @param dest - a square on the board, e.g. "A1"
 * @return true if dest is in Knight's range of movement, false otherwise
 */
bool Knight::canReach(const string& dest, bool) const
{
    int fileDiff = abs(dest[FILE_INDEX] - _position[FILE_INDEX]);
    int rankDiff = abs(dest[RANK_INDEX] - _position[RANK_INDEX]);
    return ((fileDiff == KNIGHT_DIFF1) && (rankDiff == KNIGHT_DIFF2)) ||
           ((fileDiff == KNIGHT_DIFF2) && (rankDiff == KNIGHT_DIFF1));
}