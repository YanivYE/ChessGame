#pragma once

#include "Piece.h"
#include <vector>
#include "GameLogic.h"

using std::string;


class Pawn : public Piece
{
public:
	Pawn(string type, string placement, Player player);
	bool isValidMove(string dest, vector<Piece*> board) const override;

};