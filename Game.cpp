// Game.cpp
// This file contains the implementation of the class Game

// ------------------------- includes --------------------------

#include "Game.h"

// --------------------- const definitions ---------------------

// castling queenside: input
constexpr auto Q_INPUT = "o-o-o";
// castling kingside: input
constexpr auto K_INPUT = "o-o";
// castling queenside: rook dest
constexpr int Q_ROOK = 3;
// castling kingside: rook dest
constexpr int K_ROOK = -2;
// size of input representing square on the board
constexpr int SQUARE_SIZE = 2;
// number of squares in legal user input representing a regular move
constexpr int SQUARE_NUM = 2;

// check! message
constexpr auto CHECK_MESSAGE = "\33[37;41mCheck!\33[0m";
// request move message
constexpr auto REQUEST_MOVE = ": Please enter your move:";
// request white player name message
constexpr auto REQUEST_WHITE_PLAYER = "Enter white player name:";
// request black player name message
constexpr auto REQUEST_BLACK_PLAYER = "Enter black player name:";
// illegal move message
constexpr auto ILLEGAL_MESSAGE = "\33[37;41millegal move\33[0m";
// won! message
constexpr auto WON_MESSAGE = " won!";


// ------------------- class implementation --------------------

/**
 * @brief receives input from the user and parses it. input either represents a regular move on
 * the board, i.e. "A1B1", or a castling move: "o-o-o" or "o-o". assumes: legal format.
 * @param src - non-const ref, to which the function assigns: a square on the board, e.g.
 * "A1", representing the position of the piece making the move. assignment is only in case
 * of regular move.
 * @param dest - non-const ref, to which the function assigns: a square on the board, e.g.
 * "A1", representing the destination of the piece. assignment is only in case of regular move.
 * making the move
 * @param isCastling - non-const ref, to which the function assigns: true if the given move
 * is a castling move; false otherwise.
 * @param castlingSide - non-const ref, to which the function assigns: side to which the
 * castling is executed: 'Q' for queenside, 'K' for kingside. assignment is only in case of
 * castling move.
 */
void Game::_scanMove(string &src, string &dest, bool &isCastling, char &castlingSide) const
{
    string move;
    std::cin >> move;
    if ((move == Q_INPUT) || (move == K_INPUT))
    {
        isCastling = true;
        castlingSide = (move == Q_INPUT ? QUEENSIDE: KINGSIDE);
    }
    else
    {
        src = move.substr (0, SQUARE_SIZE);
        dest = move.substr (SQUARE_SIZE, SQUARE_SIZE * SQUARE_NUM);
        isCastling = false;
    }
}

/**
 * @brief runs the current player's next move.
 * @param isCurrentInCheck - true if the player moving is in check; false otherwise
 * @return true if the move is legal (and has been executed); false otherwise.
 */
int Game::_runTurn(bool isCurrentInCheck)
{
    _gameMaster.print();
    if (isCurrentInCheck)
    {
        std::cout << CHECK_MESSAGE << std::endl;
    }
    std::cout << (_currentPlayer == WHITE ? _whitePlayerName: _blackPlayerName) << REQUEST_MOVE
              << std::endl;
    string src, dest;
    bool isCastling;
    char castlingSide;
    _scanMove(src, dest, isCastling, castlingSide);
    if (isCastling)
    {
        return _gameMaster.castling(castlingSide, _currentPlayer, isCurrentInCheck);
    }
    return _gameMaster.move(src, dest, _currentPlayer, isCurrentInCheck);
}

/**
 * @brief runs a chess game.
 */
void Game::run()
{

    std::cout << REQUEST_WHITE_PLAYER << std::endl;
    std::getline(std::cin, _whitePlayerName);
    std::cout << REQUEST_BLACK_PLAYER << std::endl;
    std::getline(std::cin, _blackPlayerName);

    _currentPlayer = WHITE;
    bool isCurrentInCheck = false;

    while(!_gameMaster.isInCheckmate(_currentPlayer, isCurrentInCheck))
    {
        while(!_runTurn(isCurrentInCheck))
        {
            std::cout << ILLEGAL_MESSAGE << std::endl;
        }
        _currentPlayer *= REVERSE; //switch player
        isCurrentInCheck = _gameMaster.isInCheck(_currentPlayer);
    }
    _gameMaster.print();
    std::cout << (_currentPlayer == WHITE ? _blackPlayerName: _whitePlayerName) << WON_MESSAGE
              << std::endl;
}


