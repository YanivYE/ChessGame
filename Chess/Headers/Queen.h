#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
	// queen constructor
	Queen(const string type, const string placement, const Player player);

	// queen destructor
	~Queen();

	// check if the moved queen move is valid
	bool isValidMove(const string dest, const vector<Piece*> board) const override;
};