#pragma once

#include "GameLogic.h"
#include "Piece.h"

#define WHITE_MULTIPLIER 1
#define BLACK_MULTIPLIER -1

class Pawn : public Piece
{
public:
	// pawn constructor
	Pawn(const string type, const string placement, const Player player);

	// pawn destructor
	~Pawn();

	// check if the moved pawn move is valid
	bool isValidMove(const string dest, const vector<Piece*> board) const override;

private:
	// function to get -1 or 1 by color(needed for valid move)
	int getColorMultiplier(const Player color) const;

};