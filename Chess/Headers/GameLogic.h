#pragma once

#include <vector>

#include "Piece.h"

#define GRAPHIC_BOARD_LENGTH 66

class GameLogic
{
public:
	void toVector(string graphicBoard);		// convert graphic board string into vector
	Piece* charToPiece(char pieceLetter, int index);	// convert each char from graphic board into its piece
	string indexToPlacement(int index);
	void movePieces();		// commit changes on the board - pieces moved
	void toGraphicBoard();		// convert vector pieces into the graphic board string


private:	
	std::vector<Piece*> _boardPieces;
	enum _turn;

};
