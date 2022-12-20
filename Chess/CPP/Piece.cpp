#include "../Headers/Piece.h"

/*
* Function is the constructor for a piece, it gets a type, placement, player color and sets the
* piece object members to the function paramters.
* Input: type - the type of the piece
*        placement - the placement of piece(a2, a3, f5)
*        player - the player color
* Output: none
*/
Piece::Piece(const string type, const string placement, const Player color)
{
	this->_placement = placement;
	this->_type = type;
	this->_color = color;
}

/*
* Function is the copy constructor for a piece, it gets other piece and copies it into this object
* Input: other - other piece object reference
* Output: none
*/
Piece::Piece(const Piece& other)
{
    *this = other;
}

bool Piece::clearMovingPath(const string dest, const vector<Piece*> board) const
{
    int curPos[2] = { CHESS_BOARD_SIDE - (this->_placement[1] - '1') - 1, this->_placement[0] - 'a' };
    int destPos[2] = { CHESS_BOARD_SIDE - (dest[1] - '1') - 1, dest[0] - 'a' };

    if (this->_type == ROOK || this->_type == QUEEN)
    {
        if (curPos[1] == destPos[1])
        {
            for (int i = std::min(curPos[0], destPos[0]) + 1; i < std::max(curPos[0], destPos[0]); i++)
            {
                if (board[i * CHESS_BOARD_SIDE + curPos[1]]->_type != EMPTY_PIECE)
                {
                    return false;
                }
            }
        }
        else if (curPos[0] == destPos[0])
        {
            for (int i = std::min(curPos[1], destPos[1]) + 1; i < std::max(curPos[1], destPos[1]); i++)
            {
                if (board[curPos[0] * CHESS_BOARD_SIDE + i]->_type != EMPTY_PIECE)
                {
                    return false;
                }
            }
        }
    }
    if (this->_type == BISHOP || this->_type == QUEEN)
    {
        if (abs(curPos[0] - destPos[0]) == abs(curPos[1] - destPos[1]))
        {
            int rowDir = (destPos[0] - curPos[0]) / abs(destPos[0] - curPos[0]);
            int colDir = (destPos[1] - curPos[1]) / abs(destPos[1] - curPos[1]);
            int row = curPos[0] + rowDir;
            int col = curPos[1] + colDir;
            while (row != destPos[0] && col != destPos[1])
            {
                if (board[row * CHESS_BOARD_SIDE + col]->_type != EMPTY_PIECE)
                {
                    return false;
                }
                row += rowDir;
                col += colDir;
            }
        }
    }
    return true;
}

Piece& Piece::operator=(const Piece& other)
{
    if (this == &other) // tries to copy the object to itself
    {
        return *this;
    }

    // shallow copy fields
    this->_color = other._color;
    this->_placement = other._placement;
    this->_type = other._type;

    return *this;
}

