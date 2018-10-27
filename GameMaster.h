// GameMaster.h

#ifndef CHESS_CPP_GAMEMASTER_H
#define CHESS_CPP_GAMEMASTER_H

// ------------------------- includes --------------------------

#include "Board.h"

// --------------------- const definitions ---------------------

// reverse color
constexpr int REVERSE = -1;
// castling queenside indicator
constexpr auto QUEENSIDE = 'Q';
// castling kingside indicator
constexpr auto KINGSIDE = 'K';

// --------------------- class declaration ---------------------

/**
 * This class represents the logical component of a chess game
 */
class GameMaster
{
private:
    Board _board; /** chess Board */

    /**
     * @brief returns the reverse of the given color i.e. WHITE for BLACK and vice versa.
     * @param color - player color: WHITE or BLACK
     * @return the reverse of the given color
     */
    int _reverseColor(int color) const {return color * REVERSE; }

    /**
     * @brief receives path of squares on the board and checks whether they are all empty.
     * @param path - vector of squares on the board, representing a path
     * @return true if all the squares in the path are empty; false otherwise.
     */
    bool _isEmptyPath(vector<string> *path) const;

    /**
     * @brief checks whether the given move is pseudo-legal i.e. dest is in the piece's range and
     * the piece's path to dest is unhindered.
     * @param piece - the moving piece
     * @param dest - a square on the board, e.g. "A1", representing the destination of the piece
     * making the move
     * @return true if the move is pseudo-legal; false otherwise.
     */
    bool _isPseudoPath(Piece *piece, const string &dest) const;

    /**
     * checks whether the given move constitutes a promotion i.e. the piece is src is a pawn and
     * dest is the edge of the board.  assumes: move is pseudo-legal
     * @param src - a square on the board, e.g. "A1", representing the position of the piece making
     * the move
     * @param dest - a square on the board, e.g. "A1", representing the destination of the piece
     * making the move
     * @return
     */
    bool _isPromotion(const string &src, const string &dest) const;

    /**
     * @brief checks whether the given castling move is pseudo-legal i.e. neither the king and rook
     * involved in the move have never moved and the path between them is empty.
     * @param castlingSide  - side to which the castling is executed: 'Q' for queenside, 'K' for
     * kingside
     * @param currentPlayer - color of player performing the castling: WHITE or BLACK
     * @param kingSrc - non-const ref, to which the function assigns the king's position on the
     * board.
     * @param rookSrc - non-const ref, to which the function assigns the rook's position on the
     * board.
     * @return true if the castling move is pseduo-legal; false otherwise.
     */
    bool _isPseudoLegalCastling
            (char castlingSide, int currentPlayer, string &kingSrc, string &rookSrc) const;

    /**
     * @brief gets all moves in the given king's range i.e. one square in every direction.
     * allocates memory in freestore.
     * @param kingsPosition - a square on the board, e.g. "A1", representing the given king's
     * position
     * @return vector of squares on the board representing every move in the given king's range
     */
    vector<string>* _getKingMoves(const string &kingsPosition) const;

public:
    /**
     * @brief checks whether the given player is in check
     * @param color - color of the given player: WHITE or BLACK
     * @return true if the given player is in check; false otherwise
     */
    bool isInCheck(int color);

    /**
     * @brief executes a move in the game. if the move is illegal, it is not executed and the
     * function returns false.
     * @param src - a square on the board, e.g. "A1", representing the position of the piece making
     * the move
     * @param dest - a square on the board, e.g. "A1", representing the destination of the piece
     * making the move
     * @param currentPlayer - color of the player making the move: WHITE or BLACK
     * @param isCurrentInCheck - true if the player moving is in check; false otherwise
     * @return true if the move is legal (and has been executed); false otherwise
     */
    bool move(const string& src, const string& dest, int currentPlayer, bool isCurrentInCheck);

    /**
     * @brief executes a castling move in the game. if the castling is illegal, it is not
     * executed and the function return false.
     * @param castlingSide  - side to which the castling is executed: 'Q' for queenside, 'K' for
     * kingside
     * @param currentPlayer - color of player performing the castling: WHITE or BLACK
     * @param isCurrentInCheck - true if the player moving is in check; false otherwise
     * @return true if the castling move is legal (and has been executed); false otherwise
     */
    bool castling(char castlingSide, int currentPlayer, bool isCurrentInCheck);

    /**
     * @brief check whether the given player is in checkmate
     * @param color - player color: WHITE or BLACK
     * @param isColorInCheck - true if the given player is in check; false otherwise
     * @return true if the given player is in checkmate; false otherwise.
     */
    bool isInCheckmate(int color, bool isColorInCheck);

    /**
     * @brief prints the board.
     */
    void print() {_board.tempPrint(); }
};

#endif //CHESS_CPP_GAMEMASTER_H
