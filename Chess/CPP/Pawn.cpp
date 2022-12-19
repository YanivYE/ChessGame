#include "../Headers/Pawn.h"


Pawn::Pawn(const string type, const string placement, const Player player) : Piece(type, placement, player)
{
}

bool Pawn::isValidMove(const string dest, const vector<Piece*> board) const
{
    int index = GameLogic::placementToIndex(dest);
    int destRow = dest[1] - '0';
    int thisRow = this->_placement[1] - '0';
    Piece* destPiece = board[index];
    int colorMultiplier = getColorMultiplier(this->_color);
    
    // Pawn can move forward one square if the destination is empty
    if (destRow == thisRow + (1 * colorMultiplier) && destPiece->_type == EMPTY_PIECE\
        && dest[0] == this->_placement[0])
    {
        return true;
    }
    // On the first move , pawn may move forward two squares if the destination is empty
    if (thisRow == getInitialColOfPawn(this->_color) && destRow == thisRow + (2 * colorMultiplier) && dest[0] == this->_placement[0] &&
        destPiece->_type == EMPTY_PIECE)
    {
        return true;
    }

    // Pawn can capture an enemy piece by moving diagonally
    if (abs(destRow - thisRow) == 1 && abs(dest[0] - this->_placement[0]) == 1)
    {
        // Check if there is an enemy piece at the new position
        if (destPiece->_color == GameLogic::opponentColor(this->_color))
        {
            return true;
        }
    }

    return false;
}

int Pawn::getColorMultiplier(const Player color) const
{
    if (color == White)
    {
        return 1;
    }

    return -1;
}

int Pawn::getInitialColOfPawn(const Player color) const
{
    if (color == White)
    {
        return 2;
    }

    return 7;
}