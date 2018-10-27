// Rook.h

#ifndef CHESS_CPP_ROOK_H
#define CHESS_CPP_ROOK_H

// ------------------------- includes --------------------------

#include "Piece.h"

// --------------------- const definitions ---------------------

// unicode character for rook
constexpr auto ROOK_UNICODE = "\u265C";

// --------------------- class declaration ---------------------

/**
 * This class represents a rook in chess game. extends the class Piece.
 */
class Rook: public Piece
{
public:
    /**
     * @brief a constructor for Rook
     * @param color - color of Rook: WHITE or BLACK
     * @param position - initial position of Rook on the board, e.g. "A1"
     */
    Rook(int color, const string& position): Piece(color, position, false) {}

    /**
     * @brief creates a deep copy of Rook. allocates memory in freestore.
     * @return new clone of Rook
     */
    Rook* clone() override {return new Rook(*this); }

    /**
     * @brief checks whether dest is in Rook's range of movement, i.e. any number of squares along a
     * rank or file.
     * @param dest - a square on the board, e.g. "A1"
     * @return true if dest is in Rook's range of movement, false otherwise
     */
    bool canReach(const string& dest, bool) const override;

    /**
     * @brief generates a path between Rook's position and dest, excluding position and dest.
     * assumes: Rook.canReach(dest) = true. allocates memory in freestore.
     * @param dest - a square on the board, e.g. "A1"
     * @return a vector of squares on the board, representing a path between Rook and dest.
     */
    vector<string>* getPathTo(const string& dest) const override;

    /**
     * @brief returns the unicode character which prints Rook
     * @return the unicode character for the chess rook
     */
    string print() const override {return ROOK_UNICODE; }

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

#endif //CHESS_CPP_ROOK_H