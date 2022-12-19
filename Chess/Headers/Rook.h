#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
	// rook constructor
	Rook(const string type, const string placement, const Player player);
	// rook destructor
	~Rook();

	// check if the moved rook move is valid
	bool isValidMove(const string dest, const vector<Piece*> board) const override;
};