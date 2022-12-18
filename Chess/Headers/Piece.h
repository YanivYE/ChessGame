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
	Piece(const string type, const string placement, const Player color);
	Piece(const Piece& other);

	virtual bool isValidMove(const string dest, const vector<Piece*> board) const = 0;
	bool clearMovingPath(const string dest, const vector<Piece*> board) const;
	// check for each piece is the move valid depends on its rules

	Piece& operator=(const Piece& other);

public:
	string _type;
	string _placement;
	Player _color;
};
