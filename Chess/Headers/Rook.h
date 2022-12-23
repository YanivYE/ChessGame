#pragma once

#include "Piece.h"

#define RIGHT_WHITE_ROOK_INITIAL_PLACEMENT "h1"
#define LEFT_WHITE_ROOK_INITIAL_PLACEMENT "a1"
#define RIGHT_BLACK_ROOK_INITIAL_PLACEMENT "h8"
#define LEFT_BLACK_ROOK_INITIAL_PLACEMENT "a8"

#define RIGHT_WHITE_ROOK_CASTLING_PLACEMENT "f1"
#define LEFT_WHITE_ROOK_CASTLING_PLACEMENT "d1"
#define RIGHT_BLACK_ROOK_CASTLING_PLACEMENT "f8"
#define LEFT_BLACK_ROOK_CASTLING_PLACEMENT "d8"


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