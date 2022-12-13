#pragma once

#include "Piece.h"

class King : public Piece
{
public:
	bool isValidMove(string dest) const override;


};