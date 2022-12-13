#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
	bool isValidMove(string dest) const override;


};