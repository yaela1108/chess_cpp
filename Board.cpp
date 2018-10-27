// Piece.cpp
// This file contains the implementation of the class Piece

// ------------------------- includes --------------------------

#include "Board.h"

// --------------------- const definitions ---------------------

// _print command
constexpr auto PRINT_COMMAND = "\33[";
// end _print command
constexpr auto END_PRINT = "0m";
// _print white text command
constexpr auto PRINT_WHITE = "37;";
// _print black text command
constexpr auto PRINT_BLACK = "30;";
// _print default text command
constexpr auto PRINT_DEFATULT = "0;";
// _print green background command
constexpr auto PRINT_GREEN = "42m";
// _print blue background command
constexpr auto PRINT_BLUE = "46m";
// number of different colors for squares
constexpr int SQUARE_COLOR_NUM = 2;
// _print space
constexpr auto SPACE = " ";

// ------------------- class implementation --------------------

/**
 * @brief returns the piece that's in square <position> in the matrix
 * @param position - a square in the matrix, e.g. "A1", representing the position from which a piece
 * is retrieved.
 * @return the retrieved piece; nullptr if the given square in the matrix is empty.
 */
Piece* Board::_getPiece(const string &position) const
{
    return _board[position[FILE_INDEX] - MIN_FILE][position[RANK_INDEX] - MIN_RANK];
}

/**
 * @brief places a piece in the given position in the matrix
 * @param piece - the piece to be placed
 * @param position - a square in the matrix, e.g. "A1", representing the piece's new position.
 */
void Board::_setPiece(Piece *piece, const string &position)
{
    _board[position[FILE_INDEX] - MIN_FILE][position[RANK_INDEX] - MIN_RANK] = piece;
}

/**
 * @brief places a piece in the given position in the matrix, and updates that piece's position.
 * @param piece - the piece to be moved. assumes: piece isn't nullptr.
 * @param position - a square in the matrix, e.g. "A1", representing the piece's new position.
 */
void Board::_movePiece(Piece *piece, const string &position)
{
    _setPiece(piece, position);
    piece->setPosition(position);
}

/**
 * @brief remove the piece placed in the given position from the matrix and from its respective set.
 * frees memory in freestore.
 * @param position - a square in the matrix, e.g. "A1", representing the position from which a piece
 * is to be removed.
 */
void Board::_removePiece(const string &position)
{
    Piece* piece = _getPiece(position);
    if (piece != nullptr)
    {
        vector<Piece*>& pieces = _getPieces(piece->getColor());
        pieces.erase(std::remove(pieces.begin(), pieces.end(), piece), pieces.end());
        delete piece;
        _setPiece(nullptr, position);
    }
}

/**
 * @brief returns the set of pieces in the given color
 * @param color - color of set: WHITE or BLACK
 * @return the set of pieces in the given color.
 */
vector<Piece*>& Board::_getPieces(int color)
{
    return (color == WHITE ? _whitePieces: _blackPieces);
}

/**
 * @brief returns the king in the given color
 * @param color - color of king: WHITE or BLACK
 * @return the king in the given color
 */
Piece* Board::_getKing(int color) const
{
    return (color == WHITE ? _whiteKing: _blackKing);
}

/**
 * @brief generates all pieces in the white / black set with their initial positions. allocates
 * memory in freestore.
 * @param color - color of set: WHITE or BLACK
 */
void Board::_createPieces(int color)
{
    vector<Piece*>& pieces = _getPieces(color);
    char rankPosition = (color == WHITE ? MIN_RANK: MAX_RANK), filePosition = MIN_FILE;
    string rankString = string(1, rankPosition), fileString;

    pieces.push_back((Piece *) (new Rook(color, string(1, filePosition++) + rankString)));
    pieces.push_back((Piece *) (new Knight(color, string(1, filePosition++) + rankString)));
    pieces.push_back((Piece *) (new Bishop(color, string(1, filePosition++) + rankString)));
    pieces.push_back((Piece *) (new Queen(color, string(1, filePosition++) + rankString)));
    pieces.push_back((Piece *) (new King(color, string(1, filePosition++) + rankString)));
    pieces.push_back((Piece *) (new Bishop(color, string(1, filePosition++) + rankString)));
    pieces.push_back((Piece *) (new Knight(color, string(1, filePosition++) + rankString)));
    pieces.push_back((Piece *) (new Rook(color, string(1, filePosition) + rankString)));

    rankString = string(1, rankPosition + color);
    for (filePosition = MIN_FILE; filePosition <= MAX_FILE; filePosition++)
    {
        fileString = string(1, filePosition);
        pieces.push_back((Piece *) (new Pawn(color, fileString + rankString)));
    }
}

/**
 * @brief places all pieces in the matrix according to their positions and updates the white / black
 * kings' pointers. assumes: sets of white / black pieces are already updated.
 * @param color - color of set: WHITE or BLACK
 */
void Board::_setUpPieces(int color)
{
    vector<Piece*>& pieces = _getPieces(color);
    for (auto piece: pieces)
    {
        _setPiece(piece, piece->getPosition());
        if (piece->isKing())
        {
            color == WHITE ? (_whiteKing = piece): (_blackKing = piece);
        }
    }
}

/**
 * @brief a constructor for Board.
 * @param isTemp - true if Board is a tempBoard of a different Board; false otherwise.
 */
Board::Board(bool isTemp)
{
    _createPieces(WHITE);
    _createPieces(BLACK);
    _setUpPieces(WHITE);
    _setUpPieces(BLACK);
    isTemp ? (_tempBoard = nullptr) : (_tempBoard = new Board(true));
}

/**
 * @brief a destructor for Board.
 */
Board::~Board()
{
    delete _tempBoard;
    for (auto piece: _whitePieces)
    {
        delete piece;
    }
    for (auto piece: _blackPieces)
    {
        delete piece;
    }
}

/**
 * @brief a copy constructor for Board. assumes: only used to create tempBoards.
 * @param other - other Board, whose contents are deep-copied and assigned to this Board
 */
Board::Board(const Board& other) // assume: only used to construct temp board
{
    for (auto piece: other._whitePieces)
    {
        _whitePieces.push_back(piece->clone());
    }
    for (auto piece: other._blackPieces)
    {
        _blackPieces.push_back(piece->clone());
    }
    _setUpPieces(WHITE);
    _setUpPieces(BLACK);
    _tempBoard = nullptr;
}

/**
 * @brief assignment operator for Board.
 * @param other - other Board, whose contents are deep-copied and assigned to this Board
 * @return this Board
 */
Board& Board::operator=(const Board& other)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            _board[i][j] = nullptr;
        }
    }
    for (auto piece: _whitePieces)
    {
        delete piece;
    }
    _whitePieces.clear();
    for (auto piece: _blackPieces)
    {
        delete piece;
    }
    _blackPieces.clear();

    for (auto piece: other._whitePieces)
    {
        _whitePieces.push_back(piece->clone());
    }
    for (auto piece: other._blackPieces)
    {
        _blackPieces.push_back(piece->clone());
    }
    _setUpPieces(WHITE);
    _setUpPieces(BLACK);
    return *this;
}

/**
 * @brief makes a move on Board. assumes: move is legal
 * @param src - a square on the board, e.g. "A1", representing the position of the piece making
 * the move
 * @param dest - a square on the board, e.g. "A1", representing the destination of the piece
 * making the move
 */
void Board::tempMove(const string& src, const string& dest)
{
    Piece* destPiece = _tempBoard->_getPiece(dest);
    if (destPiece != nullptr)
    {
        _tempBoard->_removePiece(dest);
    }
    Piece* srcPiece = _tempBoard->_getPiece(src);
    _tempBoard->_setPiece(nullptr, src);
    _tempBoard->_movePiece(srcPiece, dest);
}

/**
 * @brief promotes the given piece to queen. assumes: promotion is legal and piece is not
 * nullptr.
 * @param piece - the piece to promote.
 */
void Board::tempPromote(Piece* piece) // assume: not nullptr
{
    string position = piece->getPosition();
    int color = piece->getColor();
    vector<Piece*>& pieces = _tempBoard->_getPieces(color);

    _tempBoard->_removePiece(position);
    auto queen = new Queen(color, position);
    pieces.push_back((Piece*)queen);
    _tempBoard->_movePiece(queen, position);
}

/**
 * @brief saves Board up to latest move
 */
void Board::saveMoves()
{
    *this = *_tempBoard;
}

/**
 * @brief undoes all moves made on Board since last save.
 */
void Board::undoMoves()
{
    *_tempBoard = *this;
}

/**
 * @brief print the square located at the given position in the matrix
 * @param position - a square in the matrix, e.g. "A1", which is to be printed.
 */
void Board::_printSquare(const string &position) const
{
    Piece* piece = _getPiece(position);
    int fileIndex = position[FILE_INDEX] - MIN_FILE;
    int rankIndex = position[RANK_INDEX] - MIN_RANK;

    string squareColor = ((fileIndex + rankIndex) % SQUARE_COLOR_NUM == 0) ?
                         PRINT_GREEN : PRINT_BLUE;
    string textColor = (piece != nullptr ?
                        (piece->getColor() == WHITE ? PRINT_WHITE : PRINT_BLACK): PRINT_DEFATULT);
    string text = (piece != nullptr ? piece->print() : SPACE);
    string toPrint = PRINT_COMMAND + textColor + squareColor + text + PRINT_COMMAND + END_PRINT;
    std::cout << toPrint;
}

/**
 * @brief prints the matrix
 */
void Board::_print() const
{
    std::cout << SPACE << SPACE;
    char filePosition, rankPosition;
    for (filePosition = MIN_FILE; filePosition <= MAX_FILE; filePosition++)
    {
        std::cout << filePosition;
    }
    std::cout << std::endl << std::endl;

    string position;
    for (rankPosition = MAX_RANK; rankPosition >= MIN_RANK; rankPosition--)
    {
        std::cout << rankPosition << SPACE;
        for (filePosition = MIN_FILE; filePosition <= MAX_FILE; filePosition++)
        {
            position = string(1, filePosition) + string(1, rankPosition);
            _printSquare(position);
        }
        std::cout << SPACE << rankPosition << std::endl;
    }

    std::cout << std::endl << SPACE << SPACE;
    for (filePosition = MIN_FILE; filePosition <= MAX_FILE; filePosition++)
    {
        std::cout << filePosition;
    }
    std::cout << std::endl << std::endl;
}

/**
 * @brief checks if the given position is a square on the Board.
 * @param position -  a string in the format <char><int>
 * @return true if position is a square on the board, false otherwise
 */
bool Board::isInBoard(const string& position)
{
    return (position[RANK_INDEX] >= MIN_RANK) && (position[RANK_INDEX] <= MAX_RANK) &&
           (position[FILE_INDEX] >= MIN_FILE) && (position[FILE_INDEX] <= MAX_FILE);
}

/**
 * @brief returns the piece that's in square <position> on the Board. the piece lives until next
 * call to saveMoves() or undoMoves()
 * @param position - a square on the board, e.g. "A1", representing the position from which a
 * piece is retrieved.
 */
Piece* Board::getTempPiece(const string& position) const
{
    return _tempBoard->_getPiece(position);
}

/**
 * @brief returns the set of pieces in the given color
 * @param color - color of set: WHITE or BLACK
 */
vector<Piece*>& Board::getTempPieces(int color)
{
    return _tempBoard->_getPieces(color);
}

/**
 * @brief returns the king in the given color. the king lives until next call to saveMoves() or
 * undoMoves()
  * @param color - color of king: WHITE or BLACK
 * @return the king in the given color
 */
Piece* Board::getTempKing(int color) const
{
    return _tempBoard->_getKing(color);
}

/**
 * @brief prints the (updated) Board
 */
void Board::tempPrint() const
{
    _tempBoard->_print();
}