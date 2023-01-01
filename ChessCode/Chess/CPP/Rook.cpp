#include "../Headers/Rook.h"

/*
* Function is the constructor for the rook, it gets a type, placement, player color and sets the
* rook object members to the function paramters.
* Input: type - the type of the piece(rook)
*        placement - the placement of piece(a2, a3, f5)
*        player - the player color
* Output: none
*/
Rook::Rook(const string type, const string placement, const Player player) : Piece(type, placement, player)
{
}

/*
* Function is the destructor for the rook
* Input: None
* Output: none
*/
Rook::~Rook()
{
}

/*
* Function checks if the rook destination is valid to move to. It gets a destiantion string(eg. a2, e4, f7)
* the board vector, and returns if it is a valid move or not.
* Input: dest - a destiantion string(eg. a2, e4, f7)
*        board - the board vector
* Output: True/False - depends if move is valid or not.
*/
bool Rook::isValidMove(const string dest, const vector<Piece*> board) const
{
    if (dest[0] == this->_placement[0] || dest[1] == this->_placement[1]) 
        // if the rook moves verticly - cols are the same or horizontly - rows are the same 
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
