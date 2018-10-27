// King.h

#ifndef CHESS_CPP_KING_H
#define CHESS_CPP_KING_H

// ------------------------- includes --------------------------

#include "Piece.h"

// --------------------- const definitions ---------------------

// unicode character for king
constexpr auto KING_UNICODE = "\u265A";

// --------------------- class declaration ---------------------

/**
 * This class represents a king in chess game. extends the class Piece.
 */
class King: public Piece
{
public:
    /**
     * @brief a constructor for King
     * @param color - color of King: WHITE or BLACK
     * @param position - initial position of King on the board, e.g. "A1"
     */
    King(int color, const string& position): Piece(color, position, true) {}

    /**
     * @brief creates a deep copy of King. allocates memory in freestore.
     * @return new clone of King
     */
    King* clone() override {return new King(*this); }

    /**
     * @brief checks whether dest is in King's range of movement, i.e. one square in any direction.
     * @param dest - a square on the board, e.g. "A1"
     * @return true if dest is in King's range of movement, false otherwise
     */
    bool canReach(const string& dest, bool) const override;

    /**
     * @brief generates an empty vector, representing a path between King's position and dest,
     * excluding position and dest. assumes: King.canReach(dest) = true. allocates memory in
     * freestore.
     * @param dest - a square on the board, e.g. "A1"
     * @return a empty vector of squares on the board, representing a path between King and dest.
     */
    vector<string>* getPathTo(const string&) const override {return new vector<string>; }

    /**
     * @brief returns the unicode character which prints King
     * @return the unicode character for the chess king
     */
    string print() const override {return KING_UNICODE; }

    /**
     * @brief checks whether this piece is a king
     * return true
     */
    bool isKing() const override {return true; }

    /**
     * @brief checks whether this piece is a pawn
     * return false
     */
    bool isPawn() const override {return false; }
};

#endif //CHESS_CPP_KING_H