#include "../Headers/King.h"

/*
* Function is the constructor for the king, it gets a type, placement, player color and sets the
* king object members to the function paramters.
* Input: type - the type of the piece(king)
*        placement - the placement of biece(a2, a3, f5)
*        player - the player color
* Output: none
*/
King::King(const string type, const string placement, const Player player) : Piece(type, placement, player)
{
}

/*
* Function is the destructor for the king
* Input: None
* Output: none
*/
King::~King()
{
}

/*
* Function checks if the king destination is valid to move to. It gets a destiantion string(eg. a2, e4, f7)
* the board vector, and returns if it is a valid move or not.
* Input: dest - a destiantion string(eg. a2, e4, f7)
*        board - the board vector
* Output: True/False - depends if move is valid or not.
*/
bool King::isValidMove(string dest, vector<Piece*> board) const
{
    // check the row difference between the dest, and current pos
    int rowDifference = abs(dest[1] - this->_placement[1]);
    // check the col difference between the dest, and current pos
    int colDifference = abs(dest[0] - this->_placement[0]);

    // check if moving more than 1 cube diagonoally/vertically/horizontally
    if (rowDifference > 1 || colDifference > 1) 
    {
        // if so bad move
        return false;
    }

    // else good move
    return true;
}
