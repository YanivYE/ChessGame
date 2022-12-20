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
	// piece constructor
	Piece(const string type, const string placement, const Player color);
	// pawn copy constructor
	Piece(const Piece& other);

	// pure virtual for all pieces to use, and check there move if its valid
	virtual bool isValidMove(const string dest, const vector<Piece*> board) const = 0;

	// check if there is no possible to interpose between the piece and the destination
	bool clearMovingPath(const string dest, const vector<Piece*> board) const;
	
	// deep copy piece function
	Piece& operator=(const Piece& other);
public:
	string _type; // the type(name) of the piece
	string _placement; // the placement of the piece(eg. a2, f5, g7)
	Player _color; // the color(player) of the piece
};
