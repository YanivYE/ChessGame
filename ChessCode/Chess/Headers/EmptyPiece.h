#pragma once

#include "Piece.h"

class EmptyPiece : public Piece
{
public:
	// empty piece constructor
	EmptyPiece(const string type, const string placement, const Player player);

	// empty piece destructor
	~EmptyPiece();

	// check if the "moved" empty piece move is valid(always false)
	bool isValidMove(const string dest, const vector<Piece*> board) const override;
};