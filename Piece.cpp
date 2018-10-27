// Piece.cpp
// This file contains the implementation of the class Piece

// ------------------------- includes --------------------------

#include "Piece.h"

// ------------------- class implementation --------------------

/**
 * @brief change Piece's position on the board
 * @param position - a square on the board, e.g. "A1", representing Piece's new position on the
 * board
 */
void Piece::setPosition(const string& position)
{
    _position = position;
    _hasMoved = true;
}

/**
 * @brief generates a path between Piece's position and dest, excluding position and dest; if Piece
 * can skip over other pieces, returns empty path. assumes: Piece.canReach(dest) = true. allocates
 * memory in freestore.
 * @param dest - a square on the board, e.g. "A1"
 * @return a vector of squares on the board, representing a path between Piece and dest.
 */
vector<string>* Piece::getPathTo(const string& dest) const
// default implementation shared by Queen, Bishop and Rook
{
    auto* newPath = new vector<string>;

    char positionFile = _position[FILE_INDEX];
    char destFile = dest[FILE_INDEX];
    char positionRank = _position[RANK_INDEX];
    char destRank = dest[RANK_INDEX];

    int fileDirection = (positionFile < destFile) - (destFile < positionFile); //sgn function
    int rankDirection = (positionRank < destRank) - (destRank < positionRank);
    positionFile += fileDirection;
    positionRank += rankDirection;

    while ((positionFile != destFile) || (positionRank != destRank))
    {
        string squareFile = string(1, positionFile);
        string squareRank = string(1, positionRank);
        newPath->push_back(squareFile + squareRank);
        positionFile += fileDirection;
        positionRank += rankDirection;
    }
    return newPath;
}