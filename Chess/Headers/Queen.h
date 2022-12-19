#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(const string type, const string placement, const Player player);
	bool isValidMove(const string dest, const vector<Piece*> board) const override;

};