#pragma once

enum Player { White, Black, None };

#include <vector>
#include "Piece.h"

#define CHESS_BOARD_SIZE 64
#define CHESS_BOARD_SIDE 8
#define STARTING_PLAYER 64

#define ROOK "Rook"
#define KNIGHT "Knight"
#define BISHOP "Bishop"
#define KING "King"
#define QUEEN "Queen"
#define PAWN "Pawn"
#define EMPTY_PIECE "Empty Piece"

#define ROOK_CHAR_LOWER 'r'
#define ROOK_CHAR_UPPER 'R'
#define KNIGHT_CHAR_LOWER 'n'
#define KNIGHT_CHAR_UPPER 'N'
#define BISHOP_CHAR_LOWER 'b'
#define BISHOP_CHAR_UPPER 'B'
#define KING_CHAR_LOWER 'k'
#define KING_CHAR_UPPER 'K'
#define QUEEN_CHAR_LOWER 'q'
#define QUEEN_CHAR_UPPER 'Q'
#define PAWN_CHAR_LOWER 'p'
#define PAWN_CHAR_UPPER 'P'
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
	void switchTurn();

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
	int checkCodes(const Piece* srcP, Piece* destP);

	Player charToPlayer(const char playerChar) const;
public:	
	vector<Piece*> _boardPieces;
	Player _turn;
};
