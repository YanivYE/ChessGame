#pragma once

#include <vector>

#include "Piece.h"

#define GRAPHIC_BOARD_LENGTH 66
#define CHESS_BOARD_SIDE 8

#define ROOK "Rook"
#define KNIGHT "Knight"
#define BISHOP "Bishop"
#define KING "King"
#define QUEEN "Queen"
#define PAWN "Pawn"
#define EMPTY_PIECE "Empty Piece"

class GameLogic
{
public:
	GameLogic(string graphicBoard);
	std::vector<Piece*> toVector(string graphicBoard);		// convert graphic board string into vector
	void movePieces();		// commit changes on the board - pieces moved


private:
	Piece* charToPiece(char pieceLetter, int index);	// convert each char from graphic board into its piece
	string indexToPlacement(int index);
	Player findPieceColor(char pieceLetter);

private:	
	std::vector<Piece*> _boardPieces;
	Player _turn;

};
