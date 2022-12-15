#include "../Headers/King.h"

King::King(string type, string placement, Player player) : Piece(type, placement, player)
{
}

bool King::isValidMove(string dest) const
{
    return false;
}
