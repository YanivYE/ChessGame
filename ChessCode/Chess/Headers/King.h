#pragma once

#include "Piece.h"
#include "GameLogic.h"

// king placements defines
#define WHITE_KING_INITIAL_PLACEMENT "d1"
#define SMALL_CASTLING_WHITE_KING_PLACEMENT "b1"
#define SMALL_CASTLING_BLACK_KING_PLACEMENT "b8"
#define BLACK_KING_INITIAL_PLACEMENT "d8"

class King : public Piece
{
public:
	// king constructor
	King(const string type, const string placement, const Player player);

	// king destructor
	~King();

	// check if the moved king move is valid
	bool isValidMove(const string dest, const vector<Piece*> board) const override;

	// check if performing a castling
	static bool isCastling(string dest, vector<Piece*> board, const Piece* king);

	// get a vector that contains all the possible king moves
	vector<string> getKingMoves(const string& pos);

	bool _inCheck;		// is the king in check	
};