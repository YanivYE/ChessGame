#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	bool isValidMove(string dest) const override;


};
