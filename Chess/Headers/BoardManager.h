#pragma once

#include "GameLogic.h"
#include "EmptyPiece.h"

class BoardManager 
{
public:
	BoardManager(const string graphicBoard);
	~BoardManager();
	vector<Piece*> toVector(const string graphicBoard);		// convert graphic board string into vector
	string movePieces(const string movment, GameLogic& algorithm);		// return the code string for the givven move

	static void clearBoard(vector<Piece*> board);
	static void copyBoard(vector<Piece*> originalBoard, vector<Piece*>& copyBoard);
	static Piece* copyPiece(Piece* piece);
	static char getPieceLetter(Piece* piece);
	static char getUpperLower(Piece* piece, char lowerLetter);

	

private:
	vector<Piece*> _boardPieces;
};