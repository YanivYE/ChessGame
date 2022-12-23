#pragma once

#include "Piece.h"
#include "Rook.h"

#define WHITE_KING_INITIAL_PLACEMENT "e1"
#define BLACK_KING_INITIAL_PLACEMENT "e8"
#define SMALL_CASTLING_WHITE_KING_PLACEMENT "g1"
#define BIG_CASTLING_WHITE_KING_PLACEMENT "c1"
#define SMALL_CASTLING_BLACK_KING_PLACEMENT "g8"
#define BIG_CASTLING_BLACK_KING_PLACEMENT "c8"

class King : public Piece
{
public:
	// king constructor
	King(const string type, const string placement, const Player player);
	// king destructor
	~King();

	// check if the moved king move is valid
	bool isValidMove(const string dest, const vector<Piece*> board) const override;
	static bool isCastling(string dest, vector<Piece*> board, const Piece* king);

};