#include "../Headers/Queen.h"

Queen::Queen(string type, string placement, Player player) : Piece(type, placement, player)
{
}

bool Queen::isValidMove(string dest, vector<Piece*> board) const
{
    if (dest[0] == this->_placement[0] || dest[1] == this->_placement[1] ||
        abs(dest[0] - this->_placement[0]) == abs(dest[1] - this->_placement[1])) 
    {
        return true;
    }

    return false;
}
