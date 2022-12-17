#include "../Headers/Piece.h"
using namespace std;

Piece::Piece(string type, string placement, Player color)
{
	this->_placement = placement;
	this->_type = type;
	this->_color = color;
}

bool Piece::clearMovingPath(string dest, vector<Piece*> board) const
{
    // Convert the positions from strings to pairs of (row, col) integers
    pair<int, int> curPos = { 8 - (this->_placement[1] - '1'), this->_placement[0] - 'a' };
    pair<int, int> destPos = { 8 - (dest[1] - '1'), dest[0] - 'a' };
    // Check if piece is a rook or queen (can move horizontally or vertically)
    if (this->_type == ROOK || this->_type == QUEEN)
    {
        // Check if piece is moving horizontally
        if (curPos.second == destPos.second) {
            // Check if there are any pieces between the current position and the destination
            // along the row
            for (int i = min(curPos.first, destPos.first) + 1; i < max(curPos.first, destPos.first); i++) 
            {
                if (board[i * CHESS_BOARD_SIDE + curPos.second]->_type != EMPTY_PIECE) 
                {
                    return false;
                }
            }
        }
        // Check if piece is moving vertically
        else if (curPos.first == destPos.first) 
        {
            // Check if there are any pieces between the current position and the destination
            // along the column
            for (int i = min(curPos.second, destPos.second) + 1; i < max(curPos.second, destPos.second); i++) 
            {
                if (board[curPos.first * CHESS_BOARD_SIDE + i]->_type != EMPTY_PIECE) 
                {
                    return false;
                }
            }
        }
    }
    // Check if piece is a bishop or queen (can move diagonally)
    if (this->_type == BISHOP || this->_type == QUEEN) 
    {
        // Check if piece is moving diagonally
        if (abs(curPos.first - destPos.first) == abs(curPos.second - destPos.second)) {
            // Check if there are any pieces between the current position and the destination
            // along the diagonal
            int rowDir = (destPos.first - curPos.first) / abs(destPos.first - curPos.first);
            int colDir = (destPos.second - curPos.second) / abs(destPos.second - curPos.second);
            int row = curPos.first + rowDir;
            int col = curPos.second + colDir;
            while (row != destPos.first && col != destPos.second) 
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
    // If none of the above conditions are met, the path is clear
    return true;
}
