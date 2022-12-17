#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(const string type, const string placement, const Player player);
	bool isValidMove(const string dest, const vector<Piece*> board) const override;
	bool clearMovingPath(const string dest, const vector<Piece*> board) const;

};
