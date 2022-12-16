#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(string type, string placement, Player player);

	bool isValidMove(string dest) const override;


};