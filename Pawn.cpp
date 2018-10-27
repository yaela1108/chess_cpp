// Pawn.cpp
// This file contains the implementation of the class Pawn

// ------------------------- includes --------------------------

#include "Pawn.h"

// --------------------- const definitions ---------------------

// difference between files in a legal pawn's move, if not capturing
constexpr int PAWN_DIFF0 = 0;
// difference between files (and ranks, if capturing) in a legal pawn's move
constexpr int PAWN_DIFF1 = 1;
// difference between ranks in a legal pawn's skip, if not capturing 
constexpr int PAWN_DIFF2 = 2;

// ------------------- class implementation --------------------

/**
 * @brief checks whether dest is in Pawn's range of movement, i.e. to a square diagonally in front
 * of it, if moving captures an opponent's piece; one square forward (or two on its first move) if
 * it doesn't.
 * @param dest - a square on the board, e.g. "A1"
 * @param isCapture - true if moving to dest captures an opponent's piece; false otherwise
 * @return true if dest is in Pawn's range of movement, false otherwise
 */
bool Pawn::canReach(const string& dest, bool isCapture) const
{
    int fileDiff = abs(dest[FILE_INDEX] - _position[FILE_INDEX]);
    int rankDiff = _color * (dest[RANK_INDEX] - _position[RANK_INDEX]);
    if (isCapture)
    {
        return (fileDiff == PAWN_DIFF1) && (rankDiff == PAWN_DIFF1);
    }
    bool legalPawnSkip = (!_hasMoved) && (rankDiff == PAWN_DIFF2);
    return (fileDiff == PAWN_DIFF0) && ((rankDiff == PAWN_DIFF1) || (legalPawnSkip));
}

/**
 * @brief generates a path between Pawn's position and dest, excluding position and dest. assumes:
 * Pawn.canReach(dest) = true. allocates memory in freestore.
 * @param dest - a square on the board, e.g. "A1"
 * @return a vector of squares on the board, representing a path between Pawn and dest.
 */
vector<string>* Pawn::getPathTo(const string& dest) const
{
    auto* newPath = new vector<string>;
    int rankDiff = abs(dest[RANK_INDEX] - _position[RANK_INDEX]);
    if (rankDiff == PAWN_DIFF2)
    {
        string squareFile = string(1, char(dest[FILE_INDEX]));
        string squareRank = string(1, char(dest[RANK_INDEX] - _color));
        newPath->push_back(squareFile + squareRank);
    }
    return newPath;
}