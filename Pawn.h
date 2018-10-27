// Pawn.h

#ifndef CHESS_CPP_PAWN_H
#define CHESS_CPP_PAWN_H

// ------------------------- includes --------------------------

#include "Piece.h"

// --------------------- const definitions ---------------------

// unicode character for pawn
constexpr auto PAWN_UNICODE = "\u265F";

// --------------------- class declaration ---------------------

/**
 * This class represents a pawn in chess game. extends the class Piece.
 */
class Pawn: public Piece
{
public:
    /**
     * @brief a constructor for Pawn
     * @param color - color of Pawn: WHITE or BLACK
     * @param position - initial position of Pawn on the board, e.g. "A1"
     */
    Pawn(int color, const string& position): Piece(color, position, false) {}

    /**
     * @brief creates a deep copy of Pawn. allocates memory in freestore.
     * @return new clone of Pawn
     */
    Pawn* clone() override {return new Pawn(*this); }

    /**
     * @brief checks whether dest is in Pawn's range of movement, i.e. to a square diagonally in
     * front of it, if moving captures an opponent's piece; one square forward (or two on its first
     * move) if it doesn't.
     * @param dest - a square on the board, e.g. "A1"
     * @param isCapture - true if moving to dest captures an opponent's piece; false otherwise
     * @return true if dest is in Pawn's range of movement, false otherwise
     */
    bool canReach(const string& dest, bool isCapture) const override;

    /**
     * @brief generates a path between Pawn's position and dest, excluding position and dest.
     * assumes: Pawn.canReach(dest) = true. allocates memory in freestore.
     * @param dest - a square on the board, e.g. "A1"
     * @return a vector of squares on the board, representing a path between Pawn and dest.
     */
    vector<string>* getPathTo(const string& dest) const override;

    /**
     * @brief returns the unicode character which prints Pawn
     * @return the unicode character for the chess pawn
     */
    string print() const override {return PAWN_UNICODE; }

    /**
     * @brief checks whether this piece is a king
     * return false
     */
    bool isKing() const override {return false; }

    /**
     * @brief checks whether this piece is a pawn
     * return true
     */
    bool isPawn() const override {return true; }
};

#endif //CHESS_CPP_PAWN_H