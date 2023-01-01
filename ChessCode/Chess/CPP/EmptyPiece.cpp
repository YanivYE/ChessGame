#include "../Headers/EmptyPiece.h"

/*
* Function is the constructor for the empty piece, it gets a type, placement, player color and sets the
* empty piece object members to the function paramters.
* Input: type - the type of the piece(empty piece)
*        placement - the placement of piece(a2, a3, f5)
*        player - the player color
* Output: none
*/
EmptyPiece::EmptyPiece(const string type, const string placement, const Player player) : Piece(type, placement, player)
{
}
/*
* Function is the destructor for the empty piece
* Input: None
* Output: none
*/
EmptyPiece::~EmptyPiece()
{
}

/*
* Function checks if the empty piece destination is valid to move to - which is always false cause empty
* piece cannot move to a different place
* Input: dest - a destiantion string(eg. a2, e4, f7)
*        board - the board vector
* Output: False
*/
bool EmptyPiece::isValidMove(const string dest, const vector<Piece*> board) const
{
    return false;
}
