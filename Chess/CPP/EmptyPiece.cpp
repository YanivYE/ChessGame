#include "../Headers/EmptyPiece.h"

EmptyPiece::EmptyPiece(const string type, const string placement, const Player player) : Piece(type, placement, player)
{
}

bool EmptyPiece::isValidMove(const string dest, const vector<Piece*> board) const
{
    return false;
}
