#pragma once

#include "Piece.h"
#include <vector>
#include "GameLogic.h"

using std::string;

#define WHITE_MULTIPLIER 1
#define BLACK_MULTIPLIER -1
#define INITIAL_ROW_INDEX_WHITE 2
#define INITIAL_ROW_INDEX_BLACK 7

class Pawn : public Piece
{
public:
	// pawn constructor
	Pawn(const string type, const string placement, const Player player);
	// pawn constructor
	~Pawn();

	// check if the moved pawn move is valid
	bool isValidMove(const string dest, const vector<Piece*> board) const override;
private:
	// function to get -1 or 1 by color(needed for valid move)
	int getColorMultiplier(const Player color) const;
	// function to get the row index of initial pawn placement by color(needed for valid move)
	int getInitialRowOfPawn(const Player color) const;
};