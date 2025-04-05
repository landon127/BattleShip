/*************************************
* AUTHOR       : Landon Espinoza
 * Project      : Battleship
 * CLASS        : CS002
 * SECTION      : MW 7:05am to 9:00a
 * DUE DATE     : April 26, 2023
 ************************************/
#include "header.h"

using namespace std;

/**********************************************************
 *
 * BattleShip
 *_________________________________________________________
 * This program will implement a simulation of how
 *  a game of Battleship is played. It will pass through all
 * the functions necessary to implement the game
 * It will ask the user for whohc game mode and will decide
 *  there. It will ask the user in entering their placement
 * for the ships and will ask if it will be horizontal or
 *  vertical. Then it will ask for a shot and if playing
 *  it will do it accordingly. Then it will play the game
 *  displaying the boards until one wins the game.
 *_________________________________________________________
 * INPUT:
 *   gametype: which game will be played
 *
 * OUTPUT:
 *  The program outputs the game and how it will be played
 *   according to the functions inputted
 ***********************************************************/

int main()
{
    // decalre variables of type PlayerBoard
    PlayerBoard board1, board2;
    cout << "Please enter (P) if you want to play Player1 vs Player2 or enter (C) to play Player vs Computer? ";
    Gametype();
    // open file if pvp
    OpenFile();
    // initializing fleet in func
    initFleet(board1);
    initFleet(board2);
    // displaying boards
    displayBoards(board1.board, board2.board);
    // setting up boards
    boardSetup(board1, board2);
    //playing the game
    Game(board1, board2);
    // close file if pvp
    CloseFile();
}



// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.