#pragma once

#include "Piece.h"
#include <vector>
#include "GameLogic.h"

using std::string;


class Pawn : public Piece
{
public:
	Pawn(string type, string placement, Player player);
	bool isValidMove(const string dest, const vector<Piece*> board) const override;
private:
	int getColorMultiplier(const Player color) const;
	int getInitialColOfPawn(const Player color) const;
};