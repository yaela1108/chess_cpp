// Piece.h

#ifndef CHESS_CPP_BOARD_H
#define CHESS_CPP_BOARD_H

// ------------------------- includes --------------------------

#include <algorithm> // std::remove
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Pawn.h"
#include "King.h"

// --------------------- const definitions ---------------------

// max rank in board
constexpr char MAX_RANK = '8';
// min rank in board
constexpr char MIN_RANK = '1';
// max file in board
constexpr char MAX_FILE = 'H';
// min file in board
constexpr char MIN_FILE = 'A';
// number of ranks / files in board
constexpr int BOARD_SIZE = 8;

// --------------------- class declaration ---------------------

/**
 * This class represents a chess board.
 */
class Board
{
private:
    /** matrix representing the actual chess board */
    Piece* _board[BOARD_SIZE][BOARD_SIZE] = {nullptr};
    /** set of white pieces on the board */
    vector<Piece*> _whitePieces;
    /** set of black pieces on the board*/
    vector<Piece*> _blackPieces;
    /** the white king */
    Piece* _whiteKing;
    /** the black king */
    Piece* _blackKing;
    /**
     * a Board representing a modified (updated) version of this Board. Moves are made on
     * tempBoard, while this Board represents the last saved version of tempBoard.
     */
    Board* _tempBoard;  // tempBoard does not point to another Board

    /**
     * @brief generates all pieces in the white / black set with their initial positions. allocates
     * memory in freestore.
     * @param color - color of set: WHITE or BLACK
     */
    void _createPieces(int color);

    /**
     * @brief places all pieces in the matrix according to their positions and updates the white /
     * black kings' pointers. assumes: sets of white / black pieces are already updated.
     * @param color - color of set: WHITE or BLACK
     */
    void _setUpPieces(int color);

    /**
     * @brief places a piece in the given position in the matrix
     * @param piece - the piece to be placed
     * @param position - a square in the matrix, e.g. "A1", representing the piece's new position.
     */
    void _setPiece(Piece *piece, const string &position);

    /**
     * @brief places a piece in the given position in the matrix, and updates that piece's position.
     * @param piece - the piece to be moved. assumes: piece isn't nullptr.
     * @param position - a square in the matrix, e.g. "A1", representing the piece's new position.
     */
    void _movePiece(Piece *piece, const string &position);

    /**
     * @brief remove the piece placed in the given position from the matrix and from its respective
     * set. frees memory in freestore.
     * @param position - a square in the matrix, e.g. "A1", representing the position from which a
     * piece is to be removed.
     */
    void _removePiece(const string &position);

    /**
     * @brief returns the piece that's in square <position> in the matrix
     * @param position - a square in the matrix, e.g. "A1", representing the position from which a
     * piece is retrieved.
     * @return the retrieved piece; nullptr if the given square in the matrix is empty.
     */
    Piece* _getPiece(const string &position) const;

    /**
     * @brief returns the set of pieces in the given color
     * @param color - color of set: WHITE or BLACK
     * @return the set of pieces in the given color.
     */
    vector<Piece*>& _getPieces(int color);

    /**
     * @brief returns the king in the given color
      * @param color - color of king: WHITE or BLACK
     * @return the king in the given color
     */
    Piece* _getKing(int color) const;

    /**
     * @brief print the square located at the given position in the matrix
     * @param position - a square in the matrix, e.g. "A1", which is to be printed.
     */
    void _printSquare(const string &position) const;

    /**
     * @brief prints the matrix
     */
    void _print() const;

public:

    /**
     * @brief a constructor for Board.
     * @param isTemp - true if Board is a tempBoard of a different Board; false otherwise.
     */
    explicit Board(bool isTemp = false);

    /**
     * @brief a destructor for Board.
     */
    ~Board();

    /**
     * @brief assignment operator for Board.
     * @param other - other Board, whose contents are deep-copied and assigned to this Board
     * @return this Board
     */
    Board& operator=(const Board& other); // (excluding _tempBoard)

    /**
     * @brief a copy constructor for Board. assumes: only used to create tempBoards.
     * @param other - other Board, whose contents are deep-copied and assigned to this Board
     */
    Board(const Board& other); // (excluding _tempBoard)

    /**
     * @brief makes a move on Board. assumes: move is legal
     * @param src - a square on the board, e.g. "A1", representing the position of the piece making
     * the move
     * @param dest - a square on the board, e.g. "A1", representing the destination of the piece
     * making the move
     */
    void tempMove(const string& src, const string& dest);

    /**
     * @brief saves Board up to latest move
     */
    void saveMoves();

    /**
     * @brief undoes all moves made on Board since last save.
     */
    void undoMoves();

    /**
     * @brief promotes the given piece to queen. assumes: promotion is legal and piece is not
     * nullptr.
     * @param piece - the piece to promote.
     */
    void tempPromote(Piece* piece);

    /**
     * @brief returns the piece that's in square <position> on the Board. the piece lives until next
     * call to saveMoves() or undoMoves()
     * @param position - a square on the board, e.g. "A1", representing the position from which a
     * piece is retrieved.
     */
    Piece* getTempPiece(const string& position) const;

    /**
     * @brief returns the set of pieces in the given color
     * @param color - color of set: WHITE or BLACK
     */
    vector<Piece*>& getTempPieces(int color);

    /**
     * @brief returns the king in the given color. the king lives until next call to saveMoves() or
     * undoMoves()
      * @param color - color of king: WHITE or BLACK
     * @return the king in the given color
     */
    Piece* getTempKing(int color) const;

    /**
     * @brief checks if the given position is a square on the Board.
     * @param position -  a string in the format <char><int>
     * @return true if position is a square on the board, false otherwise
     */
    static bool isInBoard(const string& position);

    /**
     * @brief prints the (updated) Board
     */
    void tempPrint() const;
};


#endif //CHESS_CPP_BOARD_H