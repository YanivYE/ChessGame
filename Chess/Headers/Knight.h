#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(string type, string placement, Player player);
	bool isValidMove(const string dest, const vector<Piece*> board) const override;


};