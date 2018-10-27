// Knight.h

#ifndef CHESS_CPP_KNIGHT_H
#define CHESS_CPP_KNIGHT_H

// ------------------------- includes --------------------------

#include "Piece.h"

// --------------------- const definitions ---------------------

// unicode character for knight
constexpr auto KNIGHT_UNICODE = "\u265E";

// --------------------- class declaration ---------------------

/**
 * This class represents a knight in chess game. extends the class Piece.
 */
class Knight: public Piece
{
public:
    /**
     * @brief a constructor for Knight
     * @param color - color of Knight: WHITE or BLACK
     * @param position - initial position of Knight on the board, e.g. "A1"
     */
    Knight(int color, const string& position): Piece(color, position, true) {}

    /**
     * @brief creates a deep copy of Knight. allocates memory in freestore.
     * @return new clone of Knight
     */
    Knight* clone() override {return new Knight(*this); }

    /**
     * @brief checks whether dest is in Knight's range of movement, i.e. two squares vertically and
     * one square horizontally, or two squares horizontally and one square vertically
     * @param dest - a square on the board, e.g. "A1"
     * @return true if dest is in Knight's range of movement, false otherwise
     */
    bool canReach(const string& dest, bool) const override;

    /**
     * @brief generates an empty vector, representing a path between Knight's position and dest,
     * excluding position and dest. (empty because Knight skips over squares when it moves).
     * assumes: Knight.canReach(dest) = true. allocates memory in freestore.
     * @param dest - a square on the board, e.g. "A1"
     * @return a empty vector of squares on the board, representing a path between Knight and dest.
     */
    vector<string>* getPathTo(const string&) const override {return new vector<string>; }

    /**
     * @brief returns the unicode character which prints Knight
     * @return the unicode character for the chess knight
     */
    string print() const override {return KNIGHT_UNICODE; }

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

#endif //CHESS_CPP_KNIGHT_H