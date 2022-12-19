#include "../Headers/King.h"

King::King(const string type, const string placement, const Player player) : Piece(type, placement, player)
{
}

bool King::isValidMove(string dest, vector<Piece*> board) const
{
    int row_difference = abs(dest[1] - this->_placement[1]);
    int col_difference = abs(dest[0] - this->_placement[0]);
    if (row_difference > 1 || col_difference > 1) 
    {
        return false;
    }

    return true;
}
