#include "../Headers/King.h"

King::King(string type, string placement, Player player) : Piece(type, placement, player)
{
    this->_isKing = true;
}

bool King::isValidMove(string dest) const
{
    return false;
}
