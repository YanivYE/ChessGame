#include "../Headers/Queen.h"

/*
* Function is the constructor for the queen, it gets a type, placement, player color and sets the
* queen object members to the function paramters.
* Input: type - the type of the piece(queen)
*        placement - the placement of piece(a2, a3, f5)
*        player - the player color
* Output: none
*/
Queen::Queen(const string type, const string placement, const Player player) : Piece(type, placement, player)
{
}

/*
* Function is the destructor for the queen
* Input: None
* Output: none
*/
Queen::~Queen()
{
}

/*
* Function checks if the queen destination is valid to move to. It gets a destiantion string(eg. a2, e4, f7)
* the board vector, and returns if it is a valid move or not.
* Input: dest - a destiantion string(eg. a2, e4, f7)
*        board - the board vector
* Output: True/False - depends if move is valid or not.
*/
bool Queen::isValidMove(const string dest, const vector<Piece*> board) const
{
    if (dest[0] == this->_placement[0] || dest[1] == this->_placement[1] ||
        abs(dest[0] - this->_placement[0]) == abs(dest[1] - this->_placement[1])) 
        // if the queen moves verticly - cols are the same, horizontly - rows are the same or diagnoly-
        // the absolute value of the difference between the rows and cols is the same
    {
        if (clearMovingPath(dest, board))
            // and if the path between the dest and the current position is clear
        {
            return true;
            // move is valid
        }
    }

    return false;
    // move is not valid
}

