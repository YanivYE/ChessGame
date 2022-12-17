#include "../Headers/Rook.h"

Rook::Rook(string type, string placement, Player player) : Piece(type, placement, player)
{
}

bool Rook::isValidMove(string dest, vector<Piece*> board) const
{
    if (dest[0] == this->_placement[0] || dest[1] == this->_placement[1]) 
    {
        return true;
    }

    return false;
}
