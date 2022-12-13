#pragma once

#include <string>
#include <iostream>

using std::string;


class Piece
{
public:
	virtual bool isValidMove(string dest) const = 0;		
	// check for each piece is the move valid depends on its rules
	

protected:
	string _type;
	string _placement;
	enum _color;

};
