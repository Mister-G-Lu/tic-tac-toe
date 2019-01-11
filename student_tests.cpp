#define CATCH_CONFIG_MAIN

#include <cstdlib>
#include <ctime>
#include "catch.hpp"
#include <memory>
#include "XO.hpp"

TEST_CASE("Make move")
{
    INFO("Testing makeMove");
    XO blank;
    REQUIRE(blank.makeMove(1, 0));
    REQUIRE(blank.makeMove(-1, 1));
    REQUIRE(blank.makeMove(1, 2));
}
TEST_CASE("Errors")
{
    INFO("Testing errors");
    int8_t won[] = {1, -1, 1, -1, 1};
    const int8_t* wonp = won;
    uint8_t wrongpos[] = {0, 1, 10, 2, 8};
    const uint8_t* wrong = wrongpos;
    uint8_t correctpos[] = {0, 1, 4, 2, 8};
    const uint8_t* correct = correctpos;
    int8_t cheating[] = {1,1,1,1,1};
    uint8_t samepos[] = {0, 1, 1, 2, 8};
    const uint8_t* same = samepos;
    // test wrong position.
    REQUIRE_THROWS_AS(XO(wonp, wrong, 5), std::logic_error);
    // test cheating players.
    REQUIRE_THROWS_AS(XO(cheating, correct, 5), std::logic_error);
    // test same position
    REQUIRE_THROWS_AS(XO(wonp, same, 5), std::logic_error);
    // test not enough moves
    REQUIRE_THROWS_AS(XO(wonp, correct, -1), std::logic_error);

}
TEST_CASE("Constructors")
{
    INFO("Testing constructors");
    XO blank;
    for (int i=0; i<9; i++)
    {
        REQUIRE(blank.getBoard().state[i] == 0);
    }
    REQUIRE(!blank.gameOver());
    blank.show();
    REQUIRE((int)blank.getBoard().numMoves == 0);
// syntax: const int8_t* play, const uint8_t* pos, const uint8_t& n
    int8_t play[] = {1, -1, 1, -1};
    const int8_t* p = play;
    uint8_t pos []= {0, 1, 2, 3};
    const uint8_t* position = pos;
    XO basic(p, position, 4);
    REQUIRE(basic.getBoard().state[0]== 1);
    REQUIRE(basic.getBoard().state[1]== -1);
    REQUIRE(basic.getBoard().state[2]== 1);
    REQUIRE(basic.getBoard().state[3]== -1);
    REQUIRE(!blank.gameOver());
    REQUIRE(blank.winner()==0);
    basic.show();
    REQUIRE((int)basic.getBoard().numMoves == 4);

    std::cout<<"Passed all Basic tests."<<std::endl;
    int8_t won[] = {1, -1, 1, -1, 1};
    const int8_t* wonp = won;
    uint8_t wonpos[] = {0, 1, 4, 2, 8};
    const uint8_t* winningpos = wonpos;
    XO wongame(wonp, winningpos, 5);
    REQUIRE(wongame.gameOver());
    REQUIRE(wongame.winner() == 1);
    wongame.show();
    REQUIRE((int)wongame.getBoard().numMoves == 5);

    int8_t drawn[] = {1, -1, 1, -1, 1, -1, 1, -1, 1};
    const int8_t* drawnplay = drawn;
    uint8_t drawnpos[] = {0, 2, 1, 3, 5, 4, 6, 8, 7};
    const uint8_t* drawnposition = drawnpos;
    XO drawngame(drawnplay, drawnposition, 9);
    drawngame.show();
    REQUIRE((int)drawngame.getBoard().numMoves == 9);
    REQUIRE(drawngame.gameOver());
    REQUIRE(drawngame.winner() == 0);
}
//X = -1
//O = 1
TEST_CASE( "Player X immediate win" )
{
    REQUIRE ( 1== 1);

    INFO( "Player X immediate win" );
    XO g;
    g.makeMove(-1,2);
    g.makeMove(1,0);
    g.makeMove(-1,3);
    g.makeMove(1,7);
    g.makeMove(-1,6);
    g.makeMove(1,8);

    std::cout<<"Before X's immediate win"<<std::endl;
    g.show();

    while(!g.gameOver())
        g.makeOptimalMove();


    std::cout<<"After X's immediate win"<<std::endl;
    g.show();

    REQUIRE(g.winner() == -1);
    REQUIRE(g.getBoard().numMoves == 7);
}
TEST_CASE( "Optimal block w/certain loss for O" )
{
    INFO( "Optimal block w/certain loss for O" );
    XO g;
    g.makeMove(-1,1);
    g.makeMove(1,6);
    g.makeMove(-1,5);
    g.makeMove(1,7);
    g.makeMove(-1,8);

    g.makeOptimalMove();

    std::cout<<"Displaying loss for O"<<std::endl;
    g.show();

    REQUIRE(g.winner() == 0);
    REQUIRE(g.getBoard().numMoves == 6);
}

TEST_CASE( "Player X eventual win" )
{
    INFO( "Player X eventual win" );
    XO g;
    g.makeMove(-1,1);
    g.makeMove(1,6);
    g.makeMove(-1,5);
    g.makeMove(1,7);
    g.makeMove(-1,8);

    std::cout<<"Eventual win for X, original state (O's turn):"<<std::endl;
    g.show();
    while(!g.gameOver())
    {
        g.makeOptimalMove();
        std::cout<<"Making optimal move"<<std::endl;
        g.show();
    }

    std::cout<<"Displaying player x eventual win"<<std::endl;

    g.show();

    REQUIRE(g.winner() == -1);
    REQUIRE(g.getBoard().numMoves == 9);
}

TEST_CASE( "Optimal block w/certain loss for X" )
{
    INFO( "Optimal block w/certain loss for X" );
    XO g;
    g.makeMove(1,1);
    g.makeMove(-1,6);
    g.makeMove(1,5);
    g.makeMove(-1,7);
    g.makeMove(1,8);
    g.makeOptimalMove();

    std::cout<<"Displaying certain loss for X"<<std::endl;
    g.show();

    REQUIRE(g.winner() == 0);
    REQUIRE(g.getBoard().numMoves == 6);
}

TEST_CASE( "Player O eventual win" )
{
    INFO( "Player O eventual win" );
    XO g;
    g.makeMove(1,1);
    g.makeMove(-1,6);
    g.makeMove(1,5);
    g.makeMove(-1,7);
    g.makeMove(1,8);

    while(!g.gameOver())
        g.makeOptimalMove();

    std::cout<<"Displaying O Eventual Win"<<std::endl;
    g.show();

    REQUIRE(g.winner() == 1);
    REQUIRE(g.getBoard().numMoves == 9);

}
