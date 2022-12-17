#pragma once

#include "Piece.h"

class King : public Piece
{
public:
	King(string type, string placement, Player player);
	bool isValidMove(string dest, vector<Piece*> board) const override;


};