// Piece.h

#ifndef CHESS_CPP_PIECE_H
#define CHESS_CPP_PIECE_H

// ------------------------- includes --------------------------

#include <tuple>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

// --------------------- const definitions ---------------------

// white set
constexpr int WHITE = 1;
// black set
constexpr int BLACK = -1;
// file's index in a position on the board, e.g. "A1"
constexpr int FILE_INDEX = 0;
// rank's index in a position on the board, e.g. "A1"
constexpr int RANK_INDEX = 1;

// --------------------- class declaration ---------------------

/**
 * This class represents an abstract piece in a chess game.
 */
class Piece
{
protected:
    bool _hasMoved; /** true if Piece has been moved before; false otherwise */
    const int _color; /** color of Piece: WHITE or BLACK */
    string _position; /** position of Piece on the board, e.g. "A1" */
    const bool _skips; /** can Piece skip over other pieces when moving */
public:

    /**
     * @brief a constructor for Piece
     * @param color - color of Piece: WHITE or BLACK
     * @param position - initial position of Piece on the board, e.g. "A1"
     * @param skips - can Piece skip over other pieces when moving
     */
    Piece(int color, const string& position, bool skips):
            _hasMoved(false), _color(color), _position(position), _skips(skips) {}

    /**
     * @brief a destructor for Piece
     */
    virtual ~Piece() = default;

    /**
     * @brief creates a deep copy of Piece. allocates memory in freestore.
     * @return new clone of Piece
     */
    virtual Piece* clone() = 0;

    /**
     * @brief checks whether dest is in Piece's range of movement. e.g. if Piece is a rook and dest
     * is diagonal to it, return false
     * @param dest - a square on the board, e.g. "A1"
     * @param isCapture - true if moving to dest captures an opponent's piece; false otherwise
     * @return true if dest is in Piece's range of movement, false otherwise
     */
    virtual bool canReach(const string& dest, bool isCapture) const = 0;

    /**
     * @brief generates a path between Piece's position and dest, excluding position and dest; if
     * Piece can skip over other pieces, returns empty path. assumes: Piece.canReach(dest) = true.
     * allocates memory in freestore.
     * @param dest - a square on the board, e.g. "A1"
     * @return a vector of squares on the board, representing a path between Piece and dest.
     */
    virtual vector<string>* getPathTo(const string& dest) const = 0;

    /**
     * @brief returns the unicode character which prints Piece
     * @return the unicode character matching Piece's type
     */
    virtual string print() const = 0;

    /**
     * @brief checks whether Piece has been moved before
     * @return true if Piece has been moved already; false otherwise
     */
    bool hasMoved() const {return _hasMoved; }

    /**
     * @brief returns color of Piece
     * @return color of Piece: WHITE or BLACK
     */
    int getColor() const {return _color; }

    /**
     * @brief returns position of Piece on the board
     * @return position of Piece on the board, e.g. "A1"
     */
    const string& getPosition() const {return _position; }

    /**
     * @brief checks whether Piece can skip over other pieces when moving
     * @return true if Piece can skip over other pieces; false otherwise
     */
    bool skips() const {return _skips; }

    /**
     * @brief change Piece's position on the board
     * @param position - a square on the board, e.g. "A1", representing Piece's new position on the
     * board
     */
    void setPosition(const string& position); // also updates _hasMoved

    /**
     * @brief checks whether Piece is a king
     * return true if Piece is a king; false otherwise
     */
    virtual bool isKing() const = 0;

    /**
     * @brief checks whether Piece is a pawn
     * return true if Piece is a pawn; false otherwise
     */
    virtual bool isPawn() const = 0;
};

#endif //CHESS_CPP_PIECE_H