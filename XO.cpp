#include <iostream>
#include "XO.hpp"
#include <assert.h>
/* default constructor
     @return blank game state*/
XO::XO() {}
/* create game where moves have already been played
   @return game created that reflects moves specified by user;
throws a std::logic_error and board remains blank if moves/players are invalid .

For example, a game could be initialized using XO({-1,1,-1,1,-1,1}, {2,0,3,7,6,8}, 6)*/
XO::XO(const int8_t* play, const uint8_t* pos, const uint8_t& n)
{
    if ((int)n<0 || (int)n>9)
    {
        throw std::logic_error("Error: Move amount was invalid in given board.");
    }
    if ((int)*pos <0 || (int)*pos >8)
    {
        throw std::logic_error("Error: Tried to make move at invalid position in given board.");
    }
    if ((int)*play!=-1 && (int)*play!=1)
    {
        throw std::logic_error("Error: Invalid player given in given board.");
    }
    if(!makeMoves(play,pos,n))
    {
        throw std::logic_error("Error: could not create board for logical reasons");
    }
}

//display the board.
void XO::show()
{
    std::cout<<b;
}
//place player marker play (-1 or 1) at position pos; increment number of moves counter (b.numMoves)

bool XO::makeMove(const int8_t& play, const uint8_t& pos, BoardXO& brd)
{
    if ((int)play != -1 && (int)play != 1)
    {
        std::cout<<"Play was invalid"<<std::endl;
        return false;
    }
    if ((int)pos<0 || (int)pos>8)
    {
        std::cout<<"Pos was invalid"<<std::endl;
        return false;
    }
    if((int)brd[(int)pos]!=0)
    {
        std::cout<<"Pos was occupied"<<std::endl;
        return false;
    }
    if((int)brd.numMoves > 0 && brd.turn[(int)brd.numMoves - 1] == play)
    {
        std::cout<<"Tried to play two turns in a row"<<std::endl;
        return false;
    }

    // std::cout<<"Play was "<<(int)play<<" and pos was "<< (int)pos<<std::endl;
    // add the play to the board state
    brd.state[(int)pos] = play;
// add to sequence of moves.
    brd.moves[(int)brd.numMoves] = pos;
// add to which player made the move.
    brd.turn[(int)brd.numMoves] = play;
    // std::cout<<"Nummoves was "<< (int)brd.numMoves<<std::endl;
    brd.numMoves = brd.numMoves + 1;
    // std::cout<<"Nummoves became "<< (int)brd.numMoves<<std::endl;
    return true;
}

bool XO::makeMove(const int8_t& play, const uint8_t& pos)
{
    return makeMove(play, pos, b);
}
/* place multiple markers on the board
   @return game created that reflects moves specified by user; returns false and board is unmodified if moves/players are invalid */
bool XO::makeMoves(const int8_t* play, const uint8_t* pos, const uint8_t& n)
{
    if ((int)n< 0 || (int)n > 9)
    {
        std::cout<<"At move " << (int)n << " Tried to make more moves that would breach legal amount"<<std::endl;
        return false;
    }
    /*
    if (sizeof(play)/sizeof(int)!= (int)n || sizeof(pos)/sizeof(int)!= (int)n)
    {
        std::cout<<"Array didn't match n"<<std::endl;
        return false;
    }*/
    for (int i=0; i<(int)n; i++)
    {
        if(!makeMove(*(play+i), *(pos+i)))
        {
            return false;
        }
    }
    return true;
}

// pre-condition: board has one marker set (i.e., one player has placed a marker); post condition: game state updated to reflect optimal move for active player
/*
q is double-ended queue
push the current state (board) of the game to q
while q is not empty
   c = pop the game state from the front of q
     if the game c is not over
     push every possible move (board) for the next player to back of q
     else
     calculate the score of the initial move that led to win/lose/draw
*/
bool XO::makeOptimalMove()
{
    if(gameOver())
    {
        return false;
    }
    Deque<BoardXO> q;
    q.pushBack(b);
    int scores[9] = {-10,-10,-10,-10,-10,-10,-10,-10,-10};
    for (int i=0 ; i<9; i++)
    {
        if((int)b[i]==0)
        {
            scores[i]= 1;
        }
    }
    //write a for loop to make the empty position scores = `1
    while (!q.isEmpty())
    {
        BoardXO c = q.front();
        q.popFront();

        int nextPlay = 0;
        if((int)c.turn[(int)c.numMoves - 1] == 1)
        {
            // std::cout<<"Last player was O"<<std::endl;
            nextPlay = -1;
        }
        else
        {
            // std::cout<<"Last player was X"<<std::endl;
            nextPlay = 1;
        }
        // std::cout<<"Displaying c:"<<std::endl;
        // std::cout<<c;
        if (!gameOver(c))
        {
// std::cout<<"Game wasn't over and q wasn't empty"<<std::endl;
            for (int i=0 ; i<9; i++)
            {
                BoardXO temp = c;
                if ((int)c.state[i] == 0)
                {
                    // std::cout<<"Making nextplay with play "<<(int)nextPlay<<" at "<< i<<std::endl;
                    assert(makeMove((int8_t)nextPlay, (uint8_t)i, temp));
                    q.pushBack(temp);
                }
            }
        }
        else
        {
            // std::cout<<"Game ended!" <<std::endl;
            // the initial move pos (since game wasn't over, b.numMoves will not go out of bounds)
            int initmove = (int)c.moves[(int)b.numMoves];
            //determine the person who played [this line is accurate]
            int8_t whichPlay = c.turn[(int)b.numMoves];
            // std::cout<<"Calculating score for "<<(int)whichPlay<<" with init move "<<initmove<<std::endl;
            if (winner(c) == whichPlay)
            {
                // std::cout<<(int)whichPlay << " wins using pos "<<initmove<<std::endl;
                // if player wins: score = 10 – total number of moves
                int newscore = 10 - c.numMoves;
// if current score is > 0 and new score is greater than this score
                if(scores[initmove]> 0 && newscore > scores[initmove])
                {
                    scores[initmove] = newscore;
                }
            }
            else if ((int)winner(c) == 0)
            {
                // std::cout<<(int)whichPlay <<" draws with move "<< initmove<<std::endl;
// if 0 is less than the current score then set the score to 0
                if (scores[initmove]>0)
                {
                    scores[initmove] = 0;
                }
            }
            else
            {
                //  std::cout<<(int)whichPlay <<" lost with move "<< initmove<<std::endl;
                // if opponent wins: score = total number of moves – 10
                int newscore = c.numMoves - 10;
//if new score is less than the current score of the initial move then set the score to the new score
                if(newscore<scores[initmove])
                {
                    scores[initmove] = newscore;
                }
            }
        }
    }
    //determine last person to actually play (since one marker is guaranteed, this will never go out of bounds)
    int nextPlay = ((int)b.turn[(int)b.numMoves-1] == 1) ? -1 : 1;
    int maxscore = -11;
    // look for highest score (pick first if tied)
    int index = 0;
    for (int i=0; i<9; i++)
    {
        //ensure location is not occupied
        if(scores[i] > maxscore && (int)b.state[i] == 0)
        {
            maxscore = scores[i];
            index = i;
        }
    }
    // std::cout<<"Making move for "<<nextPlay<<" at position "<<index<<std::endl;
    makeMove((int8_t)nextPlay, (uint8_t)index);
    return true;
}

BoardXO XO::getBoard()
{
    return b;   //return current board (this is mainly for testing/grading)
}

bool XO::gameOver(const BoardXO& brd)
{
    if (brd.numMoves == 9)
    {
        return true;
    }
    if (brd[0]!= 0)
    {
        if (brd[0] == brd[1] && brd[1] == brd[2])
            return true;

        if( brd[0] == brd[3] && brd[3] == brd[6])
            return true;

        if( brd[0] == brd[4] && brd[4] == brd[8])
            return true;
    }
    if (brd[3]!= 0 && brd[3] == brd[4] && brd[4] == brd[5])
    {
        return true;
    }
    if (brd[6]!= 0 && brd[6] == brd[7] && brd[7] == brd[8])
    {
        return true;
    }
    if (brd[2]!= 0)
    {
        if (brd[2] == brd[4] && brd[4] == brd[6])
            return true;
        if(brd[2]== brd[5] && brd[5]==brd[8])
            return true;
    }
    if (brd[1]!=0 && brd[1]== brd[4] && brd[4]==brd[7])
    {
        return true;
    }
    return false;
} //1 draw or game won, 0 available moves
int8_t XO::winner(const BoardXO& brd)
{

    if (brd[0]!= 0)
    {
        if (brd[0] == brd[1] && brd[1] == brd[2])
            return brd[0];

        if( brd[0] == brd[3] && brd[3] == brd[6])
            return brd[0];

        if( brd[0] == brd[4] && brd[4] == brd[8])
            return brd[0];
    }
    if (brd[3]!= 0 && brd[3] == brd[4] && brd[4] == brd[5])
    {
        return brd[3];
    }
    if (brd[6]!= 0 && brd[6] == brd[7] && brd[7] == brd[8])
    {
        return brd[6];
    }
    if (brd[2]!= 0)
    {
        if (brd[2] == brd[4] && brd[4] == brd[6])
            return brd[2];
        if(brd[2]== brd[5] && brd[5]==brd[8])
            return brd[2];
    }
    if (brd[1]!=0 && brd[1]== brd[4] && brd[4]==brd[7])
    {
        return brd[1];
    }
    return 0;
} //-1 for player -1 or 1 for player 1 or 0 for no winner (draw)

// draw or game won, 0 available moves
bool XO::gameOver()
{
    return gameOver(b);
}

// check each possible win condition and return -1, 0, 1, for winner.
int8_t XO::winner()
{
    return winner(b);
}
