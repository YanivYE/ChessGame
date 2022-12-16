#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(string type, string placement, Player player);
	bool isValidMove(string dest) const override;


};