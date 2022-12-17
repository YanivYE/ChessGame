#include "../Headers/Bishop.h"


Bishop::Bishop(string type, string placement, Player player) : Piece(type, placement, player)
{
}

bool Bishop::isValidMove(string dest, vector<Piece*> board) const
{
    int row_difference = abs(dest[1] - this->_placement[1]);
    int col_difference = abs(dest[0] - this->_placement[0]);
    if (row_difference != col_difference) 
    {
        return false;
    }

    return true;
}
