#pragma once

#include "Piece.h"

class EmptyPiece : public Piece
{
public:
	EmptyPiece(string type, string placement, Player player);
	bool isValidMove(string dest, vector<Piece*> board) const override;


};