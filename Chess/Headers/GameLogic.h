#pragma once

enum Player { White, Black, None };

#include <vector>
#include "Piece.h"

using std::vector;

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

#define VALID_MOVE 0
#define VALID_MOVE_MADE_CHESS 1
#define INVALID_MOVE_NOT_YOUR_PLYAER 2
#define INVALID_MOVE_DESTINATION_NOT_FREE 3
#define INVALID_MOVE_CHESS_WILL_OCCURE 4
#define INVALID_MOVE_ILLEGAL_MOVMENT 6
#define INVALID_MOVE_NO_MOVMENT 7
#define VALID_MOVE_CHECKMATE 8

using std::string;

class Piece;

class GameLogic
{
public:
	GameLogic(const string graphicBoard);
	static int placementToIndex(const string placement);
	static Player opponentColor(const Player currentPlayer);
	static Piece* charToPiece(const char pieceLetter, const int index);	// convert each char from graphic board into its piece
	int movmentCode(const string source, const string destination, vector<Piece*>& board);

private:
	void switchTurn();
	
	static string indexToPlacement(const int index);
	static Player findPieceColor(const char pieceLetter);

	
	bool checkCode1(const Player currentPlayer, const string destination, vector<Piece*> board) const;
	bool checkCode2(const Player sourcePlayer, const Player currentPlayer) const;
	bool checkCode3(const Player destPlayer, const Player currentPlayer) const;
	bool checkCode4(const string source, const string destination, const Player currentPlayer, vector<Piece*>& board);
	bool checkCode6(const Piece* srcP, const Piece* destP, vector<Piece*> board) const;
	bool checkCode7(const string source, const string destination) const;
	//bool checkCode8(const Player currentPlayer, const string destination, vector<Piece*> board) const;
	
	Piece* currPlayerKing(const Player currentPlayer, vector<Piece*> board) const;
	void commitMove(const string source, const string destination, vector<Piece*>& board);
	int checkCodes(const Piece* srcP, Piece* destP, vector<Piece*>& board);

	Player charToPlayer(const char playerChar) const;

private:
	Player _turn;

};
