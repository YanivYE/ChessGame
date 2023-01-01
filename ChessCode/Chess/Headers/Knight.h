#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
	// knight constructor
	Knight(const string type, const string placement, const Player player);

	// knight destructor
	~Knight();

	// check if the moved knight move is valid
	bool isValidMove(const string dest, const vector<Piece*> board) const override;
};