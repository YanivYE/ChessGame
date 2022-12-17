#include "../Headers/EmptyPiece.h"

EmptyPiece::EmptyPiece(string type, string placement, Player player) : Piece(type, placement, player)
{
}

bool EmptyPiece::isValidMove(string dest, vector<Piece*> board) const
{
    return false;
}
