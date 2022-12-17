#pragma once

#include "Piece.h"

class EmptyPiece : public Piece
{
public:
	EmptyPiece(const string type, const string placement, const Player player);
	bool isValidMove(const string dest, const vector<Piece*> board) const override;


};