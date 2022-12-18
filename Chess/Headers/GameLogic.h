#pragma once

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

#define ROOK_CHAR 'r'
#define KNIGHT_CHAR 'n'
#define BISHOP_CHAR 'b'
#define KING_CHAR 'k'
#define QUEEN_CHAR 'q'
#define PAWN_CHAR 'p'
#define EMPTY_PIECE_CHAR '#'

#define CODE_0 0
#define CODE_1 1
#define CODE_2 2
#define CODE_3 3
#define CODE_4 4
#define CODE_6 6
#define CODE_7 7
#define CODE_8 8

using std::string;
using std::vector;

class Piece;

class GameLogic
{
public:
	GameLogic(const string graphicBoard);
	~GameLogic();
	std::vector<Piece*> toVector(const string graphicBoard);		// convert graphic board string into vector
	string movePieces(const string movment);		// return the code string for the givven move

	static int placementToIndex(const string placement);
	static Player opponentColor(const Player currentPlayer);

private:
	Piece* charToPiece(const char pieceLetter, const int index) const;	// convert each char from graphic board into its piece
	string indexToPlacement(const int index) const;
	Player findPieceColor(const char pieceLetter) const;

	int movmentCode(const string source, const string destination);
	bool checkCode7(const string source, const string destination) const;
	bool checkCode2(const Player sourcePlayer, const Player currentPlayer) const;
	bool checkCode3(const Player destPlayer, const Player currentPlayer) const;
	bool checkCode6(const Piece* srcP, const Piece* destP) const;
	bool checkCode4(const string source, const string destination, const Player currentPlayer);
	bool checkCode1(const Player currentPlayer, const string destination) const;

	void commitMove(const string source, const string destination);
	Piece* currPlayerKing(const Player currentPlayer) const;
	int checkCodes(const Piece* srcP, const Piece* destP);

public:	
	vector<Piece*> _boardPieces;
	Player _turn;
};
