#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
	bool isValidMove(string dest) const override;


};