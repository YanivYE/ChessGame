#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
	bool isValidMove(string dest) const override;


};