#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(const string type, const string placement, const Player player);
	bool isValidMove(const string dest, const vector<Piece*> board) const override;


};