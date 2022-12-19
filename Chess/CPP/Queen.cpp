#include "../Headers/Queen.h"

Queen::Queen(const string type, const string placement, const Player player) : Piece(type, placement, player)
{
}

Queen::~Queen()
{
}

bool Queen::isValidMove(const string dest, const vector<Piece*> board) const
{
    if (dest[0] == this->_placement[0] || dest[1] == this->_placement[1] ||
        abs(dest[0] - this->_placement[0]) == abs(dest[1] - this->_placement[1])) 
    {
        if (clearMovingPath(dest, board))
        {
            return true;
        }
    }

    return false;
}

