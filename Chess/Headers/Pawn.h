#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(string type, string placement, Player player);
	bool isValidMove(string dest) const override;

private:
	bool _firstMove;
};