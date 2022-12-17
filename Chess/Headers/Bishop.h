#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(string type, string placement, Player player);
	bool isValidMove(string dest, vector<Piece*> board) const override;
	bool clearMovingPath(string dest, vector<Piece*> board) const;

};
