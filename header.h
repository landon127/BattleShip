#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>      
#include <stdlib.h> 
#include <time.h> 

using namespace std;

//global constants
const int sizeCARRIER = 5;
const int sizeBATTLESHIP = 4;
const int sizeCRUISER = 3;
const int sizeSUBMARINE = 3;
const int sizeDESTROYER = 2;
const int FLEETSIZE = 5;


struct Point {
  int row;
  int col;
};

struct Ship {
  string name;
  int size;
  int hitcount;
  vector<Point> shipIndices;
};

struct PlayerBoard {
  string name;
  char board[10][10];
  Ship ships[FLEETSIZE];
};

/********************************************************************
* getComputerInputForSettingBoard
*   This function gets computer input for setting the board. It checks 
*   to make sure that all inputs are valid and not out of bound or 
*   in a space already occupied. It passes these coordinates by reference
*   and returns nothing. 
********************************************************************/
void getComputerInputForSettingBoard(PlayerBoard& b, int& row, int& col, char orientation, int size);
/********************************************************************
* initialize
*   This function asks the user if they'd like to play player vs player 
*   or player vs computer. 
********************************************************************/
void initialize();
/********************************************************************
* OpenFile
*   This function opens the file that has input for player 1 and 2 
********************************************************************/
void OpenFile();
/********************************************************************
* CloseFile
*   This function opens the file that has input for player 1 and 2 
********************************************************************/
void CloseFile();
/********************************************************************
* boardSetup
*   This function receives two PlayerBoards, one representing player
*   board (left hand side; ship board) and another representing
*   enemy board (right hand side; hit board) and prompts user
*   to place ships on player board. Displays boards at each step of
*   the process.
*   - returns nothing this function will setup the boards
********************************************************************/
void boardSetup(PlayerBoard &b1, PlayerBoard &b2);
/********************************************************************
* placeShip
*   This function receives a PlayerBoard representing player
*   board (left hand side; ship board) and an int representing the
*   index of the ship within the board. It gets valid information
*   from the player for where to place the ship, then places the ship.
*   - returns nothing this function will place ships
********************************************************************/
void placeShip(PlayerBoard &p, int, bool computerTurn);
/********************************************************************
* displayBoards
*   This function receives two 2D arrays, one representing player
*   board and another representing enemy board, then displays the
*   contents of these arrays
*   - returns nothing this function will display contents of
*   arrays
********************************************************************/
void displayBoards(char board1[][10], char board2[][10]);
/********************************************************************
* initFleet
*   This function takes in two PlayerBoards and initializes the boards 
*   with ' ' and all the ships in the fleet with appropriate 
*   information
*   - returns nothing this function will initialize boards
********************************************************************/
void initFleet(PlayerBoard &p);
/********************************************************************
* getValidInfo
*   This function receives two ints that represent the starting
*   coordiantes of the ship, a char that is the ship's orientation,
*   a PlayerBoard containing the ships, and the index of the ship
*   within the fleet. The function gets valid starting coordinates
*   for the ship from the user.
*   - returns nothing this function obtains valid ship placement
*   information
********************************************************************/
void getValidInfo(int &rows, int &col, char &orientation, PlayerBoard &p,
                  int index, bool computerTurn);
/********************************************************************
* spaceOccupied
*   This function receives a PlayerBoard that is the board where a
*   a ship is to be placed, two ints that represent the starting
*   coordiantes of the ship, a char that is the ship's orientation,
*   and an int that is the size of the ship.
*   - returns true if any space ship wants to occupy is already
*   occupied, false otherwise
********************************************************************/
bool spaceOccupied(PlayerBoard p, int rows, int col, char orientation,
                   int size);
/********************************************************************
* playGame
*   This function receives two PlayerBoard variables that are the two boards. 
*   It goes turn by turn and calls validating info function as well as hitorNot  
*   function to see if there were hits. It acts like a main, but it's inside a  
*   function. It tells if the fleet has sunk or not. 
*   - returns nothing
********************************************************************/
void playGame(PlayerBoard &bo1, PlayerBoard &bo2);
/********************************************************************
* inputIsValid
*   This function receives two ints that represent the starting
*   coordiantes of the ship, a char that is the ship's orientation,
*   a PlayerBoard containing the ships, and the index of the ship
*   within the fleet. The function gets valid starting coordinates
*   for the ship from the user.
*   - returns true if ship placement info is valid, false otherwise
********************************************************************/
bool inputIsValid(PlayerBoard &p, int row, int col);
/********************************************************************
* Play
*   This function dives deeper in and lets us know the hitcount and if 
* its a hit or miss. It shows which ships have sunk and it maintains a counter
* for hitcounts and for the fleet.  
********************************************************************/
bool Play (PlayerBoard &p,int row, int col, int &counter);
/********************************************************************
* getComputerShots
*   This function gets the intelligent computer shots. It shoots randomly 
*   until it gets a hit and after that it aims around the selected area. 
*   Once a ship has sunk, it shoots randomly again. It returns nothing.
********************************************************************/
void getComputerShotsSmart(PlayerBoard& b, int& row, int& col);