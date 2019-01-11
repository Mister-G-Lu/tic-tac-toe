#ifndef BOARDXO_HPP
#define BOARDXO_HPP

#include <iostream>
#include <string>

// A board struct for the game tic-tac-toe
struct BoardXO
{
    int8_t state[9]; //where player markers are on the board (player can be -1 or 1; 0 for unoccupied)
    uint8_t moves[9];  //sequence of moves that led to current game state (i.e., which marker position players selected)
    int8_t turn[9]; //which player made the corresponding move (either -1, 1, etc., or, -1, 1, etc.)
    uint8_t numMoves; //total number of moves that have been made in the game to this point

    /* default constructor
       @return a blank board (all positions unoccupied; i.e., 0 and numMoves = 0)*/
    BoardXO()
    {
        for (int i=0; i<9; i++)
        {
            state[i] = 0;
        }
        numMoves = 0;
    }

    /* return marker for requested position
       @return the marker at the given position (-1, 0, 1) throw std::range_error is subscript is out of bounds*/
    const int8_t& operator[](std::uint8_t idx) const
    {
        if (idx<0 || idx > 8)
        {
            throw std::range_error("Error: Subscript out of bounds.");
        }
        return state[idx];
    }

    /* output the state of board, for example
    * XOO
    * OXX
    * XXO
    */
    friend std::ostream& operator<<(std::ostream& os, const BoardXO& brd)
    {
        for (int i =0; i<9; i++)
        {
            int x = (int)brd[i];
            if (x == -1)
            {
                os<<"X";
            }
            else if (x == 0)
            {
                os<<" ";
            }
            else if (x == 1)
            {
                os<<"O";
            }
            if ((i+1)%3 == 0)
            {
                os<<"\n";
            }
        }
        return os;
    }
};

#endif
