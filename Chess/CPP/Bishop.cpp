#include "../Headers/Bishop.h"


Bishop::Bishop(string type, string placement, Player player) : Piece(type, placement, player)
{
}

bool Bishop::isValidMove(string dest) const
{
    return false;
}
