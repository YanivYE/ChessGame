#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	// bishop constructor
	Bishop(const string type, const string placement, const Player player);
	// bishop destructor
	~Bishop();

	// check if the moved bishop move is valid
	bool isValidMove(const string dest, const vector<Piece*> board) const override;
};
