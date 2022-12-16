#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(string type, string placement, Player player);
	bool isValidMove(string dest) const override;


};
