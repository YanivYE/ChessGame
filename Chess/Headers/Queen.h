#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
	bool isValidMove(string dest) const override;


};