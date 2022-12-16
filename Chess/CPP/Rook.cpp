#include "../Headers/Rook.h"

Rook::Rook(string type, string placement, Player player) : Piece(type, placement, player)
{
}

bool Rook::isValidMove(string dest) const
{
    return false;
}
