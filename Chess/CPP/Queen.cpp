#include "../Headers/Queen.h"

Queen::Queen(string type, string placement, Player player) : Piece(type, placement, player)
{
}

bool Queen::isValidMove(string dest) const
{
    return false;
}
