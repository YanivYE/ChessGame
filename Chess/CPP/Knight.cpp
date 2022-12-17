#include "../Headers/Knight.h"

Knight::Knight(string type, string placement, Player player) : Piece(type, placement, player)
{
}

bool Knight::isValidMove(string dest, vector<Piece*> board) const
{
    if (abs(dest[0] - this->_placement[0]) == 2 && abs(dest[1] - this->_placement[1]) == 1 ||
        abs(dest[0] - this->_placement[0]) == 1 && abs(dest[1] - this->_placement[1]) == 2) 
    {
        return true;
    }

    return false;
}
