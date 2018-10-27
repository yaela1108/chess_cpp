// Game.h

#ifndef CHESS_CPP_GAME_H
#define CHESS_CPP_GAME_H

// ------------------------- includes --------------------------

#include "GameMaster.h"

// --------------------- class declaration ---------------------

/**
 * This class represents a chess game.
 */
class Game
{
private:
    GameMaster _gameMaster; /** logical components of a chess game*/
    std::string _whitePlayerName; /** white player's name */
    std::string _blackPlayerName; /** black player's name */
    int _currentPlayer; /** color of current player: WHITE or BLACK */

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
    void _scanMove(string &src, string &dest, bool &isCastling, char &castlingSide) const;

    /**
     * @brief runs the current player's next move.
     * @param isCurrentInCheck - true if the player moving is in check; false otherwise
     * @return true if the move is legal (and has been executed); false otherwise.
     */
    int _runTurn(bool isCurrentInCheck);


public:
    /**
     * @brief runs a chess game.
     */
    void run();
};


#endif //CHESS_CPP_GAME_H
