#include "../Headers/Knight.h"

/*
* Function is the constructor for the knight, it gets a type, placement, player color and sets the
* knight object members to the function paramters.
* Input: type - the type of the piece(knight)
*        placement - the placement of piece(a2, a3, f5)
*        player - the player color
* Output: none
*/
Knight::Knight(const string type, const string placement, const Player player) : Piece(type, placement, player)
{
}

/*
* Function is the destructor for the knight
* Input: None
* Output: none
*/
Knight::~Knight()
{
}

/*
* Function checks if the knight destination is valid to move to. It gets a destiantion string(eg. a2, e4, f7)
* the board vector, and returns if it is a valid move or not.
* Input: dest - a destiantion string(eg. a2, e4, f7)
*        board - the board vector
* Output: True/False - depends if move is valid or not.
*/
bool Knight::isValidMove(const string dest, const vector<Piece*> board) const
{
    // check the row difference between the dest, and current pos
    int rowDifference = abs(dest[1] - this->_placement[1]);
    // check the col difference between the dest, and current pos
    int colDifference = abs(dest[0] - this->_placement[0]);

    // check if moving at least 2 cols and 1 row(L shape - approach no.1) or moving 
    // 1 col, 2 rows(L shape - approach no.2)
    if (colDifference == 2 && rowDifference == 1 || colDifference == 1 && rowDifference == 2)
    {
        // if so, ok move
        return true;
    }

    // else bad move
    return false;
}
