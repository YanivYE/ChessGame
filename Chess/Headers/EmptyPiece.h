#pragma once

#include "Piece.h"

class EmptyPiece : public Piece
{
public:
	bool isValidMove(string dest) const override;


};