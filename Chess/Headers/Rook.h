#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(string type, string placement, Player player);

	bool isValidMove(const string dest, const vector<Piece*> board) const override;
	//bool clearMovingPath(string dest, vector<Piece*> board) const;

};