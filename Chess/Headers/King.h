#pragma once

#include "Piece.h"

class King : public Piece
{
public:
	King(const string type, const string placement, const Player player);
	bool isValidMove(const string dest, const vector<Piece*> board) const override;

};