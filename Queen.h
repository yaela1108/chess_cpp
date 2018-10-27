// Queen.h

#ifndef CHESS_CPP_QUEEN_H
#define CHESS_CPP_QUEEN_H

// ------------------------- includes --------------------------

#include "Piece.h"

// --------------------- const definitions ---------------------

// unicode character for queen
constexpr auto QUEEN_UNICODE = "\u265B";

// --------------------- class declaration ---------------------

/**
 * This class represents a queen in chess game. extends the class Piece.
 */
class Queen: public Piece
{
public:
    /**
     * @brief a constructor for Queen
     * @param color - color of Queen: WHITE or BLACK
     * @param position - initial position of Queen on the board, e.g. "A1"
     */
    Queen(int color, const string& position): Piece(color, position, false) {}

    /**
     * @brief creates a deep copy of Queen. allocates memory in freestore.
     * @return new clone of Queen
     */
    Queen* clone() override {return new Queen(*this); }

    /**
     * @brief checks whether dest is in Queen's range of movement, i.e. any number of squares along
     * a rank, file, or diagonal.
     * @param dest - a square on the board, e.g. "A1"
     * @return true if dest is in Queen's range of movement, false otherwise
     */
    bool canReach(const string& dest, bool) const override;

    /**
     * @brief generates a path between Queen's position and dest, excluding position and dest.
     * assumes: Queen.canReach(dest) = true. allocates memory in freestore.
     * @param dest - a square on the board, e.g. "A1"
     * @return a vector of squares on the board, representing a path between Queen and dest.
     */
    vector<string>* getPathTo(const string& dest) const override;

    /**
     * @brief returns the unicode character which prints Queen
     * @return the unicode character for the chess queen
     */
    string print() const override {return QUEEN_UNICODE; }

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

#endif //CHESS_CPP_QUEEN_H