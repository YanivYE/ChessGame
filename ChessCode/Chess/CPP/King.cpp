#include "../Headers/King.h"

/*
* Function is the constructor for the king, it gets a type, placement, player color and sets the
* king object members to the function paramters.
* Input: type - the type of the piece(king)
*        placement - the placement of piece(a2, a3, f5)
*        player - the player color
* Output: none
*/
King::King(const string type, const string placement, const Player player) : Piece(type, placement, player)
{
    this->_inCheck = false;
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

    // check if moving more than 1 cube diagonoally/vertically/horizontally and not castling
    if ((rowDifference > 1 || colDifference > 1) && !isCastling(dest, board, this))
    {
        // if so bad move
        return false;
    }

    // else good move
    return true;
}

/*
* Function checks if the player is performing a valid castling - by the castling conditions
* Input: dest - a destiantion string(eg. a2, e4, f7)
*        board - the board pieces vector
*        king - the king performing the castling
* Output: True/False - valid castling or not
*/
bool King::isCastling(string dest, vector<Piece*> board, const Piece* king) 
{
    // check the row difference between the dest, and current pos
    int rowDifference = abs(dest[1] - king->_placement[1]);
    // check the col difference between the dest, and current pos
    int colDifference = abs(dest[0] - king->_placement[0]);

    // check castling
    if (colDifference == 2 && rowDifference == 0 && !((King*)king)->_inCheck && king->clearMovingPath(dest, board))
        // if the king moves 2 squares horizontally, not in check and has no interrupting pieces 
        // in his path - can currently make castling
    {
        if (king->_placement ==  WHITE_KING_INITIAL_PLACEMENT && !king->_moved) 
            // if the king is in the white king placement and hasn't moved yet
        {
            if (board[GameLogic::placementToIndex(RIGHT_WHITE_ROOK_INITIAL_PLACEMENT)]->_type == ROOK &&
                !board[GameLogic::placementToIndex(RIGHT_WHITE_ROOK_INITIAL_PLACEMENT)]->_moved || 
                board[GameLogic::placementToIndex(LEFT_WHITE_ROOK_INITIAL_PLACEMENT)]->_type == ROOK &&
                !board[GameLogic::placementToIndex(LEFT_WHITE_ROOK_INITIAL_PLACEMENT)]->_moved)
                // if the white rooks are in their initial placements and hasn't moved yet
            {
                return true;
            }
        }
        if (king->_placement == BLACK_KING_INITIAL_PLACEMENT && !king->_moved)
            // if the king is in the black king placement and hasn't moved yet
        {
            if (board[GameLogic::placementToIndex(RIGHT_BLACK_ROOK_INITIAL_PLACEMENT)]->_type == ROOK &&
                !board[GameLogic::placementToIndex(RIGHT_BLACK_ROOK_INITIAL_PLACEMENT)]->_moved ||
                board[GameLogic::placementToIndex(LEFT_BLACK_ROOK_INITIAL_PLACEMENT)]->_type == ROOK &&
                !board[GameLogic::placementToIndex(LEFT_BLACK_ROOK_INITIAL_PLACEMENT)]->_moved)
                // if the black rooks are in their initial placements and hasn't moved yet
            {

                return true;
            }
        }
    }

    // invalid castling performe
    return false;
}

/*
* Function gets a string vector of all possible king moves, depending on his location on the board
* the vector includes destination strings like- e2
* Input: pos - the current king position
* Output: possible destinations vector
*/
vector<string> King::getKingMoves(const string& pos)
{
    int r, c = 0;
    vector<string> kingMoves;
    string position = "";

    // The row and column of the king's position
    int row = pos[1] - '1';
    int col = pos[0] - 'a';

    // Check all eight directions the king can move in
    for (r = -1; r <= 1; r++)
    {
        for (c = -1; c <= 1; c++)
        {
            // Skip the position the king is already in
            if (r == 0 && c == 0) continue;

            // Check if the new position is on the board
            if (row + r >= 0 && row + r < CHESS_BOARD_SIDE && col + c >= 0 && col + c < CHESS_BOARD_SIDE)
            {
                // set position
                position = char(col + c + 'a');
                position += (char(row + r + '1'));

                // Add the new position to the list of moves
                kingMoves.push_back(position);
            }
        }
    }

    // return the possible king moves vector
    return kingMoves;
}