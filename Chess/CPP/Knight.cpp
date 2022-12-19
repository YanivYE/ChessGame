#include "../Headers/Knight.h"

Knight::Knight(const string type, const string placement, const Player player) : Piece(type, placement, player)
{
}

bool Knight::isValidMove(const string dest, const vector<Piece*> board) const
{
    if (abs(dest[0] - this->_placement[0]) == 2 && abs(dest[1] - this->_placement[1]) == 1 ||
        abs(dest[0] - this->_placement[0]) == 1 && abs(dest[1] - this->_placement[1]) == 2) 
    {
        return true;
    }

    return false;
}
