// Bishop.h

#ifndef CHESS_CPP_BISHOP_H
#define CHESS_CPP_BISHOP_H

// ------------------------- includes --------------------------

#include "Piece.h"

// --------------------- const definitions ---------------------

// unicode character for bishop
constexpr auto BISHOP_UNICODE = "\u265D";

// --------------------- class declaration ---------------------

/**
 * This class represents a bishop in chess game. extends the class Piece.
 */
class Bishop: public Piece
{
public:
    /**
     * @brief a constructor for Bishop
     * @param color - color of Bishop: WHITE or BLACK
     * @param position - initial position of Bishop on the board, e.g. "A1"
     */
    Bishop(int color, const string& position): Piece(color, position, false) {}

    /**
     * @brief creates a deep copy of Bishop. allocates memory in freestore.
     * @return new clone of Bishop
     */
    Bishop* clone() override {return new Bishop(*this); }

    /**
     * @brief checks whether dest is in Bishop's range of movement, i.e. any number of squares
     * diagonally.
     * @param dest - a square on the board, e.g. "A1"
     * @return true if dest is in Bishop's range of movement, false otherwise
     */
    bool canReach(const string& dest, bool) const override;

    /**
     * @brief generates a path between Bishop's position and dest, excluding position and dest.
     * assumes: Bishop.canReach(dest) = true. allocates memory in freestore.
     * @param dest - a square on the board, e.g. "A1"
     * @return a vector of squares on the board, representing a path between Bishop and dest.
     */
    vector<string>* getPathTo(const string& dest) const override;

    /**
     * @brief returns the unicode character which prints Bishop
     * @return the unicode character for the chess bishop
     */
    string print() const override {return BISHOP_UNICODE; }

    /**
     * @brief checks whether this piece is a king
     * return false
     */
    bool isKing() const override {return false; }

    /**
     * @brief checks whether this piece is a pawn
     * return false
     */
    bool isPawn() const override {return false; }
};

#endif //CHESS_CPP_BISHOP_H