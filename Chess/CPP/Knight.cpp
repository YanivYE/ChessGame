#include "../Headers/Knight.h"

Knight::Knight(string type, string placement, Player player) : Piece(type, placement, player)
{
}

bool Knight::isValidMove(string dest) const
{
    return false;
}
