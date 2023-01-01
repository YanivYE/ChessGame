#pragma once

#include "Piece.h"

// rook initial placements defiens
#define RIGHT_WHITE_ROOK_INITIAL_PLACEMENT "h1"
#define LEFT_WHITE_ROOK_INITIAL_PLACEMENT "a1"
#define RIGHT_BLACK_ROOK_INITIAL_PLACEMENT "h8"
#define LEFT_BLACK_ROOK_INITIAL_PLACEMENT "a8"

// rook casting placements defines
#define LEFT_WHITE_ROOK_CASTLING_PLACEMENT "c1"
#define RIGHT_WHITE_ROOK_CASTLING_PLACEMENT "e1"
#define LEFT_BLACK_ROOK_CASTLING_PLACEMENT "c8"
#define RIGHT_BLACK_ROOK_CASTLING_PLACEMENT "e8"

class Rook : public Piece
{
public:
	// rook constructor
	Rook(const string type, const string placement, const Player player);

	// rook destructor
	~Rook();

	// check if the moved rook move is valid
	bool isValidMove(const string dest, const vector<Piece*> board) const override;

};