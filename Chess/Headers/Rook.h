#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(const string type, const string placement, const Player player);
	bool isValidMove(const string dest, const vector<Piece*> board) const override;

};