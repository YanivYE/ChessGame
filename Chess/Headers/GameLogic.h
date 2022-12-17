#pragma once

// add defines, consts, comments
// check if move goes beiond another oppenent player

enum Player { White, Black, None };

#include <vector>
#include "Piece.h"

#define CHESS_BOARD_SIZE 64
#define CHESS_BOARD_SIDE 8
#define STARTING_PLAYER 65

#define ROOK "Rook"
#define KNIGHT "Knight"
#define BISHOP "Bishop"
#define KING "King"
#define QUEEN "Queen"
#define PAWN "Pawn"
#define EMPTY_PIECE "Empty Piece"

using std::string;
using std::vector;

class Piece;

class GameLogic
{
public:
	GameLogic(string graphicBoard);
	~GameLogic();
	std::vector<Piece*> toVector(string graphicBoard);		// convert graphic board string into vector
	string movePieces(string movment);		// return the code string for the givven move

	static int placementToIndex(string placement);
	static Player opponentColor(Player currentPlayer);

private:
	void switchTurn();
	Piece* charToPiece(char pieceLetter, int index);	// convert each char from graphic board into its piece
	string indexToPlacement(int index);
	Player findPieceColor(char pieceLetter);

	int movmentCode(string source, string destination);
	bool checkCode7(string source, string destination);
	bool checkCode2(Player sourcePlayer, Player currentPlayer);
	bool checkCode3(Player destPlayer, Player currentPlayer);
	bool checkCode6(Piece* srcP, Piece* destP);
	bool checkCode4(string source, string destination, Player currentPlayer);
	bool checkCode1(Player currentPlayer, string destination);

	void commitMove(string source, string destination);
	Piece* currPlayerKing(Player currentPlayer);
	int checkCodes(Piece* srcP, Piece* destP);

public:	
	static std::vector<Piece*> _boardPieces;
	Player _turn;
};
