#pragma once

#include "GameLogic.h"
#include "EmptyPiece.h"

#define LOWER_TO_UPPER 32

class BoardManager 
{
public:
	// constructor for board manager
	BoardManager(const string graphicBoard);

	// destructor for board manager
	~BoardManager();

	// convert graphic board string into vector
	vector<Piece*> toVector(const string graphicBoard);	
	// return the code string for the given move
	string movePieces(const string movement, GameLogic& algorithm);		

	// clear board vector
	static void clearBoard(vector<Piece*> board);
	// copy board vector from original to copy
	static void copyBoard(vector<Piece*> originalBoard, vector<Piece*>& copyBoard);
	// copy piece and return new pointer to copied piece
	static Piece* copyPiece(Piece* piece);
	// get piece letter(Pawn = P / p - depends on color)
	static char getPieceLetter(Piece* piece);
	// check if piece letter should be upper or lower case and return the letter
	static char getUpperLower(Piece* piece, char lowerLetter);

private:
	// vector for the board pieces
	vector<Piece*> _boardPieces;
};