// GameMaster.cpp
// This file contains the implementation of the class GameMaster

// ------------------------- includes --------------------------

#include "GameMaster.h"

// --------------------- const definitions ---------------------

// max difference between ranks or files in a legal king's move
constexpr int KING_RANGE = 1;
// castling queenside: direction
constexpr int Q_DIRECTION = -1;
// castling kingside: direction
constexpr int K_DIRECTION = 1;
// castling queenside: rook dest
constexpr int Q_ROOK = 3;
// castling kingside: rook dest
constexpr int K_ROOK = -2;


// ------------------- class implementation --------------------

/**
 * @brief receives path of squares on the board and checks whether they are all empty.
 * @param path - vector of squares on the board, representing a path
 * @return true if all the squares in the path are empty; false otherwise.
 */
bool GameMaster::_isEmptyPath(vector<string> *path) const
{
    for (const auto& position: *path)
    {
        if (_board.getTempPiece(position) != nullptr)
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief checks whether the given move is pseudo-legal i.e. dest is in the piece's range and the
 * piece's path to dest is unhindered.
 * @param piece - the moving piece
 * @param dest - a square on the board, e.g. "A1", representing the destination of the piece
 * making the move
 * @return true if the move is pseudo-legal; false otherwise.
 */
bool GameMaster::_isPseudoPath(Piece *piece, const string &dest) const
{
    if (!_board.isInBoard(dest))
    {
        return false;
    }
    Piece* destPiece = _board.getTempPiece(dest);
    bool isCapture = true;
    if (destPiece == nullptr)
    {
        isCapture = false;
    }
    else if (destPiece->getColor() == piece->getColor())
    {
        return false;
    }
    if (!piece->canReach(dest, isCapture))
    {
        return false;
    }
    vector<string>* path = piece->getPathTo(dest);
    bool result = _isEmptyPath(path);
    delete path;
    return result;
}

/**
 * @brief checks whether the given player is in check
 * @param color - color of the given player: WHITE or BLACK
 * @return true if the given player is in check; false otherwise
 */
bool GameMaster::isInCheck(int color)
{
    Piece* king = _board.getTempKing(color);
    const string& kingPosition = king->getPosition();
    vector<Piece*>& enemyPieces = _board.getTempPieces(_reverseColor(color));
    for (const auto piece: enemyPieces)
    {
        if (_isPseudoPath(piece, kingPosition))
        {
            return true;
        }
    }
    return false;
}

/**
 * checks whether the given move constitutes a promotion i.e. the piece is src is a pawn and dest
 * is the edge of the board. assumes: move is pseudo-legal
 * @param src - a square on the board, e.g. "A1", representing the position of the piece making
 * the move
 * @param dest - a square on the board, e.g. "A1", representing the destination of the piece
 * making the move
 * @return
 */
bool GameMaster::_isPromotion(const string &src, const string &dest) const
{
    Piece* srcPiece = _board.getTempPiece(src);
    char endOfBoard = (srcPiece->getColor() == WHITE ? MAX_RANK: MIN_RANK);
    return srcPiece->isPawn() && (dest[RANK_INDEX] == endOfBoard);
}

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
bool GameMaster::move
        (const string& src, const string& dest, int currentPlayer, bool isCurrentInCheck)
{
    if (!_board.isInBoard(src))
    {
        return false;
    }
    Piece *srcPiece = _board.getTempPiece(src);
    if ((srcPiece == nullptr) || (srcPiece->getColor() != currentPlayer))
    {
        return false;
    }
    if (isCurrentInCheck && !srcPiece->isKing())
    {
        return false;
    }
    if (!_isPseudoPath(srcPiece, dest))
    {
        return false;
    }
    bool promotion = _isPromotion(src, dest);
    _board.tempMove(src, dest);
    if (isInCheck(srcPiece->getColor()))
    {
        _board.undoMoves();
        return false;
    }
    if (promotion)
    {
        _board.tempPromote(srcPiece);
    }
    _board.saveMoves();
    return true;
}

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
bool GameMaster::_isPseudoLegalCastling
        (char castlingSide, int currentPlayer, string &kingSrc, string &rookSrc) const
{
    Piece* king = _board.getTempKing(currentPlayer);
    if (king->hasMoved())
    {
        return false;
    }
    kingSrc = king->getPosition();

    char rookSrcFile = (castlingSide == QUEENSIDE ? MIN_FILE: MAX_FILE);
    rookSrc = string(1, rookSrcFile) + string(1, kingSrc[RANK_INDEX]);

    Piece* rook = _board.getTempPiece(rookSrc);
    if ((rook == nullptr) || (rook->hasMoved()))
    {
        return false;
    }

    vector<string>* rookToKingPath = rook->getPathTo(kingSrc);
    bool result = _isEmptyPath(rookToKingPath);
    delete rookToKingPath;
    return result;
}

/**
 * @brief executes a castling move in the game. if the castling is illegal, it is not
 * executed and the function return false.
 * @param castlingSide  - side to which the castling is executed: 'Q' for queenside, 'K' for
 * kingside
 * @param currentPlayer - color of player performing the castling: WHITE or BLACK
 * @param isCurrentInCheck - true if the player moving is in check; false otherwise
 * @return true if the castling move is legal (and has been executed); false otherwise
 */
bool GameMaster::castling(char castlingSide, int currentPlayer, bool isCurrentInCheck)
{
    string kingSrc, rookSrc;
    if (!_isPseudoLegalCastling(castlingSide, currentPlayer, kingSrc, rookSrc))
    {
        return false;
    }

    int direction = (castlingSide == QUEENSIDE ? Q_DIRECTION: K_DIRECTION);
    auto kingMidFile = char(kingSrc[FILE_INDEX] + direction);
    auto kingDestFile = char(kingMidFile + direction);
    const string& kingMid = string(1, kingMidFile) + string(1, kingSrc[RANK_INDEX]);
    const string& kingDest = string(1, kingDestFile) + string(1, kingSrc[RANK_INDEX]);

    bool result = isCurrentInCheck;
    _board.tempMove(kingSrc, kingMid);
    result = result || isInCheck(currentPlayer);
    _board.tempMove(kingMid, kingDest);
    result = result || isInCheck(currentPlayer);
    if (result)
    {
        _board.undoMoves();
        return false;
    }

    auto rookDestFile = char(rookSrc[FILE_INDEX] + (castlingSide == QUEENSIDE ? Q_ROOK: K_ROOK));
    const string& rookDest = string(1, rookDestFile) + string(1, kingSrc[RANK_INDEX]);
    _board.tempMove(rookSrc, rookDest);
    _board.saveMoves();
    return true;
}

/**
 * @brief gets all moves in the given king's range i.e. one square in every direction.
 * allocates memory in freestore.
 * @param kingsPosition - a square on the board, e.g. "A1", representing the given king's
 * position
 * @return vector of squares on the board representing every move in the given king's range
 */
vector<string>* GameMaster::_getKingMoves(const string &kingsPosition) const
{
    char positionFile = kingsPosition[FILE_INDEX];
    char positionRank = kingsPosition[RANK_INDEX];
    string newPosition;

    auto* newMoves = new vector<string>;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            newPosition = string(1, char(positionFile + i)) + string(1, char(positionRank + j));
            newMoves->push_back(newPosition);
        }
    }
    return newMoves;
}

/**
 * @brief check whether the given player is in checkmate
 * @param color - player color: WHITE or BLACK
 * @param isColorInCheck - true if the given player is in check; false otherwise
 * @return true if the given player is in checkmate; false otherwise.
 */
bool GameMaster::isInCheckmate(int color, bool isColorInCheck)
{
    if (!isColorInCheck)
    {
        return false;
    }
    Piece* king = _board.getTempKing(color);
    string kingsPosition = king->getPosition();
    vector<string>* kingMoves = _getKingMoves(kingsPosition);
    bool result;
    for (const auto& dest: *kingMoves)
    {
        // board getters must be reset after undoMoves(), saveMoves()
        king = _board.getTempKing(color);
        if (_isPseudoPath(king, dest))
        {
            _board.tempMove(kingsPosition, dest);
            result = isInCheck(color);
            _board.undoMoves();
            if (!result)
            {
                delete kingMoves;
                return false;
            }
        }
    }
    delete kingMoves;
    return true;
}