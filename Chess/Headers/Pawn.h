#pragma once

#include "Piece.h"
#include "GameLogic.h"

using std::string;
using std::vector;

class Pawn : public Piece
{
public:
	Pawn(string type, string placement, Player player);
	bool isValidMove(string dest) const override;

};