#include "../Headers/Pawn.h"

/*
* Function is the constructor for the pawn, it gets a type, placement, player color and sets the
* pawn object members to the function paramters.
* Input: type - the type of the piece(pawn)
*        placement - the placement of piece(a2, a3, f5)
*        player - the player color
* Output: none
*/
Pawn::Pawn(const string type, const string placement, const Player player) : Piece(type, placement, player)
{
}

/*
* Function is the destructor for the pawn
* Input: None
* Output: none
*/
Pawn::~Pawn()
{
}

/*
* Function checks if the pawn destination is valid to move to. It gets a destiantion string(eg. a2, e4, f7)
* the board vector, and returns if it is a valid move or not.
* Input: dest - a destiantion string(eg. a2, e4, f7)
*        board - the board vector
* Output: True/False - depends if move is valid or not.
*/
bool Pawn::isValidMove(const string dest, const vector<Piece*> board) const
{
    // get index of dest cube
    int index = GameLogic::placementToIndex(dest);
    // get dest row
    int destRow = dest[1] - '0';
    // get this current placement row
    int thisRow = this->_placement[1] - '0';
    // get dest piece
    Piece* destPiece = board[index];
    // get color multiplier - suppose to determine if we should decrease / increase to row(white 
    // gows straight by increasing row index, and black by decreasing)
    int colorMultiplier = getColorMultiplier(this->_color);
    
    // check if is moving forward one cube, if the destination cube is empty, and if it is going on
    // the same col
    if (destRow == thisRow + (1 * colorMultiplier) && destPiece->_type == EMPTY_PIECE
        && dest[0] == this->_placement[0])
    {
        // if so good move
        return true;
    }
    // check if we are on first move, is moving forward two cubes, if the destination cube is empty,
    // and going on the same col
    if (thisRow == getInitialRow(this) && destRow == thisRow + (2 * colorMultiplier) && 
        dest[0] == this->_placement[0] && destPiece->_type == EMPTY_PIECE)
    {
        // if so good move
        return true;
    }

    // check if is capturing an enemy piece by moving diagonally 1
    if (abs(destRow - thisRow) == 1 && abs(dest[0] - this->_placement[0]) == 1)
    {
        // check if there is openent piece at dest
        if (destPiece->_color == GameLogic::opponentColor(this->_color))
        {
            // if so we eat and good move
            return true;
        }
    }

    // else bad move
    return false;
}

/*
* Function gets a player color, and returns a multiplier that is or -1 or 1 that is suppose to determine
* if we should decrease / increase to row(white gows straight by increasing row index,
* and black by decreasing)
* Input: color - the color(black - white)
* Output: a multiplier that is or -1 or 1
*/
int Pawn::getColorMultiplier(const Player color) const
{
    if (color == White)
    {
        // return white multiplier  
        return WHITE_MULTIPLIER;
    }
    // return black multiplier

    return BLACK_MULTIPLIER;
}

