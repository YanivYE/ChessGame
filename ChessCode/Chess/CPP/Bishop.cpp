#include "../Headers/Bishop.h"

/*
* Function is the constructor for the bishop, it gets a type, placement, player color and sets the 
* bishop object members to the function paramters.
* Input: type - the type of the piece(bishop)
*        placement - the placement of piece(a2, a3, f5)
*        player - the player color
* Output: none
*/
Bishop::Bishop(const string type, const string placement, const Player player) : Piece(type, placement, player)
{
}

/*
* Function is the destructor for the bishop
* Input: None
* Output: none
*/
Bishop::~Bishop()
{
}

/*
* Function checks if the bishop destination is valid to move to. It gets a destiantion string(eg. a2, e4, f7)
* the board vector, and returns if it is a valid move or not.
* Input: dest - a destiantion string(eg. a2, e4, f7)
*        board - the board vector
* Output: True/False - depends if move is valid or not.
*/
bool Bishop::isValidMove(const string dest, const vector<Piece*> board) const
{
    // check the row difference between the dest, and current pos
    int rowDifference = abs(dest[1] - this->_placement[1]);
    // check the col difference between the dest, and current pos
    int colDifference = abs(dest[0] - this->_placement[0]);

    // check if differnces aren't equal(not moving in a digonal), or if moving path not clear
    if (rowDifference != colDifference || !clearMovingPath(dest, board))
    {
        // if so, false move
        return false;
    }

    // else good move
    return true;
}


