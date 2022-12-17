#include "../Headers/Pawn.h"


Pawn::Pawn(string type, string placement, Player player) : Piece(type, placement, player)
{
}

bool Pawn::isValidMove(string dest) const
{
    int index = GameLogic::placementToIndex(dest);

    Piece* destPiece = GameLogic::_boardPieces[index];

    // Pawn can move forward one square if the destination is empty
    if (dest[1] == this->_placement[1] + 1 && dest[0] == this->_placement[0] &&
        destPiece->_type == EMPTY_PIECE)
    {
        return true;
    }
    // On its first move, a pawn may move forward two squares if the destination is empty
    if (this->_placement[1] == 1 && dest[1] == this->_placement[1] + 2 && dest[0] == this->_placement[0] &&
        destPiece->_type == EMPTY_PIECE)
    {
        return true;
    }

    // Pawn can capture an enemy piece by moving diagonally
    if (abs(dest[1] - this->_placement[1]) == 1 && abs(dest[0] - this->_placement[0]) == 1)
    {
        // Check if there is an enemy piece at the new position
        if (destPiece->_color == GameLogic::opponentColor(this->_color))
        {
            return true;
        }
    }

    return false;
}
