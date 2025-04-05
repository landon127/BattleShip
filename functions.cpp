//
// Created by landon e on 4/4/25.
//

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
* FUNCTION Gametype
*_________________________________________________________
*   This function takes in the gaem type and whihc will
*    be played
*   - returns nothing
*_________________________________________________________
* PRE-CONDITIONS
*   The following need previously defined values:
*    none
*
* POST-CONDITIONS
*   This function will return  nothing
***********************************************************/
char type;
void Gametype()
{
  cin >> type;
}
/**********************************************************
*
* FUNCTION OpenFile
*_________________________________________________________
*   This function acts accordingly to the game tyep and
*    opens file
*   - returns bool
*_________________________________________________________
* PRE-CONDITIONS
*   The following need previously defined values:
*    none
*
* POST-CONDITIONS
*   This function will return  nothing
***********************************************************/
ifstream myFile;
void OpenFile()
{
  // opens file
    if (type == 'C')
    myFile.open("input.txt");
}


/**********************************************************
*
* FUNCTION initFleet
*_________________________________________________________
*   This function takes in a PlayerBoard PB, and initializes
*   the info accordingly
*   - returns bool
*_________________________________________________________
* PRE-CONDITIONS
*   The following need previously defined values:
*    playerboard PB: (reference) info of playerboard in PB
*
* POST-CONDITIONS
*   This function will return  nothing
***********************************************************/
void initFleet(PlayerBoard& PB)
{
  // initializes fleet and stores info
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      PB.board[i][j] = ' ';

  PB.ships[0] = {"Carrier", 5, 0};
  PB.ships[1] = {"Battleship", 4, 0};
  PB.ships[2] = {"Cruiser", 3, 0};
  PB.ships[3] = {"Submarine", 3, 0};
  PB.ships[4] = {"Destroyer", 2, 0};
}


/**********************************************************
*
* FUNCTION displayBoards
*_________________________________________________________
*   This function takes in a char baord1 and board2
*    and it will set and display the boards of each .
*   - returns nothing
*_________________________________________________________
* PRE-CONDITIONS
*   The following need previously defined values:
*    char board1:  array - info of board 1
*    char board2: array - info of board 2
*
*
* POST-CONDITIONS
*   This function will return  nothing
***********************************************************/
void displayBoards(char board1[][10], char board2[][10])
{

   string horiz_spacer(10, ' ');
   const int rowss = 10;
   //char array[rows][10];
   cout <<  "               Your Board                 " << "          "
        <<  "                  Enemy Board"             << endl;
    cout << "    1   2   3   4   5   6   7   8   9   10" << "          "
         << "    1   2   3   4   5   6   7   8   9   10" << endl;
    cout << "  -----------------------------------------" << "          "
         << "  -----------------------------------------" << endl;
    for(int i=0; i < rowss;i++)
    {
        //print row of board1
        cout << static_cast<char>('A' + i) << " |";

        for (int j=0; j < 10; j++)
        {
            cout << " " << board1[i][j] << " |";

        }
       // print board 2
        cout << "          " << static_cast<char>('A' + i) << " |";
        for (int j=0; j < 10; j++)
        {
        cout << " " << board2[i][j] << " |";
        }
        //finish closing the board
        cout << endl;
        cout << "  -----------------------------------------" << "          "
         << "  -----------------------------------------" << endl;
     }
}

/**********************************************************
*
* FUNCTION BoardSetUp
*_________________________________________________________
*   This function takes in a two PlayerBoards of board1 and baord2
*   and will initialize the boards by placing the ships. It will
*  display the baprds accordingly. After going through the functions
*  it will update the board according to the game
*_________________________________________________________
* PRE-CONDITIONS
*   The following need previously defined values:
*    Playerbaord board1 : (reference) info on board
*    Playerboard board2 : (Reference) info on board 2
*
* POST-CONDITIONS
*   This function will return  nothing
***********************************************************/

void boardSetup(PlayerBoard &board1, PlayerBoard &board2)
{
  // sets up board
  srand((unsigned) time(NULL));
  // if computer is present
  bool CPU = false;

  cout << "Player 1 set your board." << endl;

  for (int i = 0; i < FLEET_SIZE; i++)
    {
      //update board
      placeShip(board1, i, CPU);
        displayBoards(board1.board, board2.board);
    }
  // prints for player 2
  cout << "Player 2 set your board." << endl;
  if (type == 'C')
      CPU = true;
   for (int i = 0; i < FLEET_SIZE; i++)
    {
      placeShip(board2, i, CPU);
      displayBoardsEnemy(board1.board, board2.board);
    }
}


/**********************************************************
*
* FUNCTION placeShip
*_________________________________________________________
*   This function takes in a two PlayerBoards of board1 and baord2
*   and will call the func getValidInfo to complete the placement
*   and validate the info
*_________________________________________________________
* PRE-CONDITIONS
*   The following need previously defined values:
*    Playerbaord board PB: playerboard info of ship
*    Int index: index of ship
*    bool CPU: determine if the computer turn
*
* POST-CONDITIONS
*   This function will return  nothing
***********************************************************/
void placeShip(PlayerBoard &PB, int index, bool CPU)
{
  // set up for place ship
  int rows;
  int col;
  char orientation;
  getValidInfo(rows, col, orientation, PB, index, CPU);
}

/**********************************************************
*
* FUNCTION getValidInfo
*_________________________________________________________
*   This function takes in a PlayerBoard PB, int row,col
*    char orientation int index and bool CPU. It will
* ask for the coordinates of a ship placement and wether or not
*   it is horizontal or vertical. Then according to the gametype
*   it will either get input from the file or generate the computer board
*   After it will check with it's fucntions to determine if the
* input given is valid. It will update the board accodringly and move on
*   returns nothing
*_________________________________________________________
* PRE-CONDITIONS
*   The following need previously defined values:
*    playerboard PB: (reference) holds info of playerboard
*    Int row :(reference) holds row
*        col :(reference) holds col
*        index : index of ship
*    char oreintation: (reference)  if horiz or vert
*    bool CPU: determiens if it is computer or not
*
* POST-CONDITIONS
*   This function will return  nothing
***********************************************************/

void getValidInfo(int &rows, int &col, char &orientation, PlayerBoard &PB,
                  int index,bool CPU)
{
  while (true)
  {
    //variables
      char letter; // letter for input text row
      int number; // number for coordinate col
    // print coordimnates
      cout << "Enter the starting coordinates of your " << PB.ships[index].name
           << ": ";
      if (type == 'P')
      {
        // get from input text
        string line;
        getline (myFile,line);
        //gets letter
        letter = line[0];
        string Str_num; // string number col
        //convert from string to number
        Str_num = line.substr(1);
        number = stoi(Str_num);

        cout << letter << number << endl;
        //update
        rows = letter - 65;
        col = number - 1;
      }
      else
      {
        if(CPU)
        {
          // generates random number for h or v
           int randomNumber;
           randomNumber = rand() % 2;
          // for horizontal
           if (randomNumber != 1)
              orientation = 'h';
           else
             //for vertical
              orientation = 'v';
          // sets up computer board
              CompBoardSetUp(PB, rows, col, orientation, PB.ships[index].size);
        }
          // asks user to input coordinate
            else
            {
              cin >> letter >> number;
              //update
              rows = letter - 65;
              col = number - 1;
            }
      }
    // prints orientation
      cout << "Enter the orientation of your " << PB.ships[index].name
           << " (horizontal(h) or vertical(v)): ";
      if (type == 'P')
      {
        // gets coordinates
        string coordinate1;
        getline (myFile,coordinate1);
        orientation = coordinate1[0];
        cout << orientation << endl;
      }
        //for computer prints orientation
        else
        {
          if(!CPU)
          cin >> orientation;
          else if (CPU)
          cout << orientation << endl;

        }
    // goes to check if it is occupied
      int size;
      size = PB.ships[index].size;
      bool isSpaceOccupied;
      isSpaceOccupied = spaceOccupied(PB, rows, col, orientation, size);
      if(isSpaceOccupied)
      {
        continue;
      }
    // adds to horizontal
      if (orientation == 'h')
        {
          for (int j = 0; j < size; j++)
          {
            if (j == 0)
            {
              PB.board[rows][col] = 's';
              Point coordinate2;
              coordinate2 = {rows, col};
              PB.ships[index].shipIndices.push_back(coordinate2);
            }
            else
            {
              col++;
              PB.board[rows][col] = 's';
              Point coordinate2;
              coordinate2 = {rows, col};
              PB.ships[index].shipIndices.push_back(coordinate2);
            }
          }
        }
        // adds to vertical
      else if (orientation == 'v')
      {
        for (int i = 0; i < size; i++)
          {
            if (i == 0)
            {
             PB.board[rows][col] = 's';
             Point coordinate3;
             coordinate3 = {rows, col};
             PB.ships[index].shipIndices.push_back(coordinate3);
            }
            else
            {
              rows++;
              PB.board[rows][col] = 's';
              Point coordinate4;
              coordinate4 = {rows, col};
              PB.ships[index].shipIndices.push_back(coordinate4);
            }
          }
      }
    break;
  }

}

/**********************************************************
*
* FUNCTION CompBoardSetUp
*_________________________________________________________
*   This function takes in a PlayerBoard PB, int row,col
*    char orientation int size and sets up the board.
*    It comes up with a random coordinate for the computer
*    that will display horiz or vertical and it will be
*     in parameters, seeting it up for the computer
*   - returns bool
*_________________________________________________________
* PRE-CONDITIONS
*   The following need previously defined values:
*    playerboard PB: (reference) holds info of playerboard
*    Int row :(reference) holds row
*        col :(reference) holds col
*        size : size of ship
*    char oreintation: if horiz or vert
*
* POST-CONDITIONS
*   This function will return  nothing
***********************************************************/

void CompBoardSetUp(PlayerBoard& PB, int& row, int& col,
                                     char orientation, int size)
{
   while(true)
   {
     // variables
      int ROW; // row of coordinate
      int COL; //col of cooridnate
     // get coords of 0-10 for row and col
       ROW = rand() % 10;
       COL = rand() % 10;
      if (orientation == 'h')
      {
        if ((COL + size) > 9)
          continue;
      }
      else
      {
        if((ROW + size) > 9)
        continue;
      }
     // checks to see if full
       bool full = false;
       if (orientation == 'h')
       {
          for (int j = COL; j <= COL + size; j++)
          {
            //checks to see if available  for col
            if (PB.board[ROW][j] != ' ')
            {
              full = true;
              break;
            }
          }
       }
       else
       {
         // if full is true
          for (int i = ROW; i <= ROW + size; i++)
          {
            //checks if not available  for row
            if(PB.board[i][COL] != ' ')
            {
              full = true;
              break;
            }
          }
       }
       if (full)
         continue;
       // updating to pass
       char A = static_cast<char>(ROW + 65);
       int NewCOL = COL + 1;
       cout << A << "," << NewCOL<< endl;

       row = ROW;
       col = COL;
       break;

   }
}


/**********************************************************
*
* FUNCTION spaceOccupied
*_________________________________________________________
*   This function takes in a PlayerBoard PB, int row,col
*    char orientation int size and checks if inputs are valid
*    It checks if it is within the paraemter first then,
*    it checks if the space is occupied or not
*   - returns bool
*_________________________________________________________
* PRE-CONDITIONS
*   The following need previously defined values:
*    playerboard PB: holds info of playerboard
*    Int row : holds col
*        col : holds col
*        size : size of ship
*    char oreintation: if horiz or vert
*
* POST-CONDITIONS
*   This function will return  bool
***********************************************************/

bool spaceOccupied(PlayerBoard PB, int rows, int col, char orientation,
                   int size)
{
  //checks and adds for horizontal orientation
  if (orientation == 'h')
  {
    for (int j = 0; j < size; j++)
    {
      if (j == 0)
      {
        // checks if within borders
        if ((rows > 9) || (col > 9))
        {
          // prints error if out of board
          cout << "Error: Ship placement is outside the board." << endl;
          return true;
        }
        else if (PB.board[rows][col] != ' ')
        {
          // prints error if space is occupied by other ships
          cout << "Error: Space already occupied." << endl;
          return true;
        }
        else
          continue;
      }
      else
      {
        // adds to the col number but checks if valid ,in parameters
        col++;
        // checks if within boundaries
        if ((rows > 9) || (col > 9))
        {
          cout << "Error: Ship placement is outside the board." << endl;
          return true;
        }
          // checks if space is occupied
        else if (PB.board[rows][col] != ' ')
        {
          cout << "Error: Space already occupied." << endl;
          return true;
        }
        else
          continue;
      }
    }
    return false;
  }
    // checks and adds for vertical orientation
  else if (orientation == 'v')
  {
    for (int i = 0; i < size; i++)
    {
      if (i == 0)
      {
        // checks if within boundaries
        if ((rows > 9) || (col > 9))
        {
          cout << "Error: Ship placement is outside the board." << endl;
          return true;
        }
          // checks if it is occupied or not
        else if (PB.board[rows][col] != ' ')
        {
          cout << "Error: Space already occupied." << endl;
          return true;
        }
        else
          continue;
      }
      else
      {
        //adds to the row number
        rows++;
        // checks if within boundaries
        if ((rows > 9) || (col > 9))
        {
          cout << "Error: Ship placement is outside the board." << endl;
          return true;
        }
          // checks if it is occupied or not
        else if (PB.board[rows][col] != ' ')
        {
          cout << "Error: Space already occupied." << endl;
          return true;
        }
        else
        {
          continue;
        }
      }
    }
  }
  return false;
}

/**********************************************************
*
* FUNCTION Game
*_________________________________________________________
*   This function takes in a PlayerBoard board1 and board2
*   by reference . It will continue to play the game fire,
*   shoot , get valid or invalid info, and print resutls
*    until one wins
*   - returns nothing
*_________________________________________________________
* PRE-CONDITIONS
*   The following need previously defined values:
*    playerboard board1: (by reference) holds info of board1
*    playerboard board2: (reference) holds info of board2
* POST-CONDITIONS
*   This function will return nothing
***********************************************************/

void Game(PlayerBoard &board1,PlayerBoard &board2)
{
     // delcare variables
    int turn = 1; // num of turn
    char row; //  letter that shows row
    int col;  // column
    int count = 0, count2 = 0; // fleet size count
    while (true)
    {
      // prints fire shot and which turn
      cout << "Player " << turn << ":" << endl;
      cout << "Fire a shot: ";
      // player vs player
    if (type == 'P')
    {
        //getting input from file
        string line;
        // getting info
        getline(myFile, line);
        // get the letter (row)
        row = line[0];
        string Str; // string letter for row
        // convert from string to interger
        Str = line.substr(1);
        col = stoi(Str);

        row = row ;
        col = col;
        // print row and col for board
        cout << row << "," << col   << endl;
      // update
        row = row -65;
        col = col -1 ;

    }
    else
    {
        if (type == 'C' && turn == 2)
        {
          // get input for shot
          // variables
            char let; // letter to print
            int TempROW; // temporary row for (number)
          // call function
            getCompShot(board1, TempROW, col);  // 0 to 9
          // convert to char
            let = static_cast<char>(TempROW + 65);
           // pass variable
            row = TempROW ;
          // print coordinate
            cout << let << "," << col + 1 << endl;  /// +1
          //update
            col = col;

        }
          // asks for coordinates
        else
        {

            cin >> row >> col;
            row = row - 65;
            col = col -1 ;
        }
    }
      // check for valid info
   bool result;
    if (turn == 1)
        result = InvalidInfo(board2, row, col);
    else
        result = InvalidInfo(board1, row, col);

    if (result)
      continue;

    // call func for results to see if hit or miss
  // or sunken ship
    bool shot_hit ;
    if (turn == 1)
        shot_hit = Results(board2, row, col, count);
    else
        shot_hit = Results(board1, row, col, count2);

    if (shot_hit == false)
    {
     cout << "You missed. " << endl;
    }
        //cout << ".......";
    // display updated boards
   if (turn == 1)
    displayBoards(board1.board, board2.board);
    if (turn == 2)
    displayBoardsEnemy(board1.board, board2.board);
    // prints who won the game
    if (count == 5 || count2 == 5)
    {
        cout << "Player " << turn << " sunk the fleet!!! They win!!!" << endl;
        break;
    }
      // turn change
    if (turn == 1)
        turn = turn + 1;
    else if (turn == 2)
        turn = turn - 1;
  }
}

/**********************************************************
*
* FUNCTION GetCompShot
*_________________________________________________________
*   This function takes in a PlayerBoard by reference  PB
*    reference row, referecne col coordinates of position on the board,
*    calls for CompShot
*   - returns nothing (chnages values )
*_________________________________________________________
* PRE-CONDITIONS
*   The following need previously defined values:
*    playerboard p: (by reference) holds info
*    int row: (reference) nums for rows for coordinate
*    int col : (reference) nums for col for coordinate
* POST-CONDITIONS
*   This function will return nothing (chnages values)
***********************************************************/
void getCompShot(PlayerBoard& PB, int& row, int& col)
{
  // call func
    CompShot(PB, row, col);
}
/**********************************************************
*
* FUNCTION CompShot
*_________________________________________________________
*   This function takes in a PlayerBoard object by reference PB
*    reference row, referecne col coordinates of position on the board,
*    It checks four sides of shot to find a new shot to fire
*    If it doesnt find any it checks a new point to check
*    re
*   - returns nothing (value)
*_________________________________________________________
* PRE-CONDITIONS
*   The following need previously defined values:
*    playerboard PB: (by reference) holds info
*    int row: (reference) nums for rows for coordinate
*    int col : (reference) nums for col for coordinate
* POST-CONDITIONS
*   This function will return nothing (value)
***********************************************************/

void CompShot(PlayerBoard& PB, int& row, int& col)
{
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
       //check all the sides to hit
       if (PB.board[i][j] == 'H')
       {
         //left side to check if ship
         if ( (j-1) >= 0)
         {
           int temp_J;
           temp_J = j-1; //-1
           if (PB.board[i][temp_J] != 'H' && PB.board[i][temp_J] != 'M')
           {
             row = i;
             col = temp_J;

             return;
           }

         }
         // right side to check if ship
         if ((j+1) <= 9)
         {
           int temp_J = j+1;
           if (PB.board[i][temp_J] != 'H' &&
             PB.board[i][temp_J] != 'M')
           {
             row = i;
             col = temp_J;
             return;
           }
         }
         // top side to check if ship
         if ((i-1) >=0)
         {
           int temp_I = i-1;
           if (PB.board[temp_I][j] != 'H' && PB.board[temp_I][j] != 'M')
           {
             row = temp_I;
             col = j;
             return;
           }
         }
         // bottom side to check if ship
         if ((i+1) <= 9)
         {
           int temp_I = i+1;
           if (PB.board[temp_I][j] != 'H' && PB.board[temp_I][j] != 'M')
           {
             row = temp_I;
             col = j;
             return;
           }
         }

      }
    }
  }
  // random coordinate to check
  while (true)
  {
    int rowTemp, colTemp;
    rowTemp =  1 + rand() % 10;
    colTemp =  1 + rand() % 10;
    if (PB.board[rowTemp][colTemp] != 'H' &&
       PB.board[rowTemp][colTemp] != 'M')
      {
         row = rowTemp - 1;
         col = colTemp - 1 ;
         break;
      }
  }
}


/**********************************************************
*
* FUNCTION InvalidInfo
*_________________________________________________________
*   This function takes in a PlayerBoard object by reference PB ,row
*   , col coordinates of position on the board, checks if the
*    specified row or column is greater than 9.
*   Should it be greater than 9 the function will prints invalid.
*   Next, the function will check if the position already has a hit or miss
*     showing invalid again if it does
*   If it is valid wihout the limitation shows true
*   - returns a bool for true or false true if invalid or valid
*_________________________________________________________
* PRE-CONDITIONS
*   The following need previously defined values:
*    playerboard PB: (by reference) holds info
*    int row: nums for rows for coordinate
*    int col : nums for col for coordinate
* POST-CONDITIONS
*   This function will return a bool
***********************************************************/
bool InvalidInfo(PlayerBoard &PB, int row, int col)
{
  if ((row > 9) || (col > 9))
  {
    // invalid if outside parameters
    cout << "Invalid " << endl;
    return true;
  }
    /// invalid if already hit or miss
  else if (PB.board[row][col] == 'H' || PB.board[row][col] == 'M')
  {
    cout << "Invalid. " << endl;
    return true;
  }
  else
    return false;
}


/**********************************************************
*
* FUNCTION Results
*_________________________________________________________
*   This function takes in a PlayerBoard object by reference PB,row
*   , col coordinates of position on the board, and an integer counter
*    by reference for size. Then it checks if the position on the
*   board matches the row and col coordinates that contains a ship
*   IF it matches, the function will display it hit. The
    function returns true to indicate that a ship was hit.
*   But if the position doesnt macth a ship the function sets
    the position to display a miss and return false
*   - returns a bool for true or false
*_________________________________________________________
* PRE-CONDITIONS
*   The following need previously defined values:
*    playerboard PB: (by reference) holds info
*    int row: nums for rows for coordinate
*    int col : nums for col for coordinate
*    count: (reference) count var for size of ship
* POST-CONDITIONS
*   This function will return a bool
***********************************************************/
bool Results(PlayerBoard &PB,int row, int col, int &count)
{
  if (PB.board[row][col] == 's')
  {
    // if matches with ship print hit
    cout << "Hit!!!" << endl;
    // stores h in that specific postion of the board
    PB.board[row][col] = 'H';
    for (int i = 0; i < FLEET_SIZE; i++)
    {
      Ship& ship = PB.ships[i];
      vector<Point>& position = ship.shipIndices;
      for (int j =0; j < position.size(); j++)
      {
        Point& point =  position.at(j);
        if (point.row == row && point.col == col)
        {
          ship.hitcount = ship.hitcount + 1;
          // print if all of the ship is hit, say sunk
          if (ship.hitcount == ship.size)
          {
            cout << "You sunk the " << ship.name << "!!!" << endl;
            count++;
          }
        }
      }
    }
    return true;
  }
  else
  {
    // print miss for the shot
    PB.board[row][col] = 'M';
    return false;
  }
}


 /**********************************************************
*
* FUNCTION CloseFile
*_________________________________________________________
*   This function gets the type of game and closes the PVP
*    file
*   - returns nothing.
*_________________________________________________________
* PRE-CONDITIONS
*   The following need previously defined values:
*  none
   var of type and myFile
*
* POST-CONDITIONS
*   This function will return nothing
***********************************************************/
void CloseFile()
{
  // close file
    if (type == 'P')
    myFile.close();
}

/**********************************************************
*
* FUNCTION displayBoardsEnemy
*_________________________________________________________
*   This function takes in a char board1 and board2
*    and it will set and display the boards of each but the
*    enemy board first (switches)
*   - returns nothing
*_________________________________________________________
* PRE-CONDITIONS
*   The following need previously defined values:
*    char board1:  array - info of board 1
*    char board2: array - info of board 2
*
*
* POST-CONDITIONS
*   This function will return  nothing
***********************************************************/
void displayBoardsEnemy(char board1[][10], char board2[][10])
{

   string horiz_spacer(10, ' ');
   const int rowss = 10;
   //char array[rows][10];
   cout <<  "                 Enemy Board                 " << "          ";
   cout <<  "                  Your Board"             << endl;
    cout << "    1   2   3   4   5   6   7   8   9   10" << "          "
         << "    1   2   3   4   5   6   7   8   9   10" << endl;
    cout << "  -----------------------------------------" << "          "
         << "  -----------------------------------------" << endl;
    for(int i=0; i < rowss;i++)
    {
        //print row of board2
        cout << static_cast<char>('A' + i) << " |";

        for (int j=0; j < 10; j++)
        {
            cout << " " << board2[i][j] << " |";

        }
       // print board 1
        cout << "          " << static_cast<char>('A' + i) << " |";
        for (int j=0; j < 10; j++)
        {
        cout << " " << board1[i][j] << " |";
        }
        //finish closing the board
        cout << endl;
        cout << "  -----------------------------------------" << "          "
         << "  -----------------------------------------" << endl;
     }
}









