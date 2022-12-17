#pragma once

#include <string>
#include <iostream>
#include "GameLogic.h"

using std::string;
using std::vector;

class GameLogic;

class Piece 
{
public:
	Piece(string type, string placement, Player color);
	virtual bool isValidMove(string dest, vector<Piece*> board) const = 0;
	bool clearMovingPath(string dest, vector<Piece*> board) const;
	// check for each piece is the move valid depends on its rules

public:
	string _type;
	string _placement;
	Player _color;
};
