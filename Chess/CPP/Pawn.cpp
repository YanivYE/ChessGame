#include "../Headers/Pawn.h"

Pawn::Pawn(string type, string placement, Player player) : Piece(type, placement, player)
{
}

bool Pawn::isValidMove(string dest) const
{
	return false;
}
