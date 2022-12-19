#pragma once

#include "Piece.h"

class King : public Piece
{
public:
	// king constructor
	King(const string type, const string placement, const Player player);
	// king destructor
	~King();

	// check if the moved king move is valid
	bool isValidMove(const string dest, const vector<Piece*> board) const override;
};