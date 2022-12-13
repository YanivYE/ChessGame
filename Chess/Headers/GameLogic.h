#pragma once

#include <vector>

#include "Piece.h"

class GameLogic
{
public:
	void toVector();		// convert graphic board string into vector
	void movePieces();		// commit changes on the board - pieces moved
	void toGraphicBoard();		// convert vector pieces into the graphic board string


private:
	string _graphicBoard;	
	std::vector<Piece*> _boardPieces;
	enum _turn;

};
