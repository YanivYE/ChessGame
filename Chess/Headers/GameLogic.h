#pragma once

#include "BoardManager.h"
#include "Piece.h"
#include "Bishop.h"
#include "EmptyPiece.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include <string>

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
#define INVALID_MOVE_NOT_YOUR_PLAYER 2
#define INVALID_MOVE_DESTINATION_NOT_FREE 3
#define INVALID_MOVE_CHESS_WILL_OCCURE 4
#define INVALID_MOVE_ILLEGAL_MOVMENT 6
#define INVALID_MOVE_NO_MOVMENT 7
#define VALID_MOVE_CHECKMATE 8
#define VALID_MOVE_MADE_CASTLING 9

class Piece;

class GameLogic
{
public:
	// constructor for game logic
	GameLogic(const string graphicBoard);

	// get placement string(eg. a2) and convert to index
	static int placementToIndex(const string placement);
	// get openent color
	static Player opponentColor(const Player currentPlayer);
	// convert each char from graphic board into its piece
	static Piece* charToPiece(const char pieceLetter, const int index);
	// get valid/invalid code from move
	int movementCode(const string source, const string destination, vector<Piece*>& board);

	// move piece from source to dest
	void commitMove(const string source, const string destination, vector<Piece*>& board);
private:
	// switch turn in engine
	void switchTurn();
	
	// index to placement(eg. a2)
	static string indexToPlacement(const int index);
	// get piece color by letter
	static Player findPieceColor(const char pieceLetter);

	// check if valid move, and made chess
	bool checkCode1(const Player currentPlayer, const string destination, vector<Piece*> board) const;
		// returns true if user tried to move player that isn't his
	bool checkCode2(const Player sourcePlayer, const Player currentPlayer) const;
	// returns true if destination not free
	bool checkCode3(const Player destPlayer, const Player currentPlayer) const;
	// returns true if chess on current player will accure because of move
	bool checkCode4(const string source, const string destination, const Player currentPlayer, vector<Piece*>& board);
		// returns true if invalid movement with piece
	bool checkCode6(const Piece* srcP, const Piece* destP, vector<Piece*> board) const;
	// returns if source and dest are the same
	bool checkCode7(const string source, const string destination) const;

	bool checkCode8(const Player currentPlayer, const Piece* attacker, vector<Piece*>& board);

	bool checkCode9(const Piece* srcP, const Piece* destP, const vector<Piece*> board) const;
	
	bool isPossibleKingEscape(Piece* king, const Player currentPlayer, vector<Piece*>& board);
	// return the king of the current player(black - white)

	bool isPossibleCapture(const string attackerPlacement, const Player oppenentPLayer, vector<Piece*> board);

	bool isPossibleInterpose(const Piece* attacker, const Piece* king, vector<Piece*> board);

	Piece* currPlayerKing(const Player currentPlayer, vector<Piece*> board) const;

	// check codes after moving piece
	int checkCodes(const Piece* srcP, Piece* destP, vector<Piece*>& board);

	// get player by char(0 - 1) - (white - black)
	Player charToPlayer(const char playerChar) const;

	void switchTurnAndClearMemory(Piece* initialSrc, Piece* initialDst);
private:
	// curent turn(black / white)
	Player _turn;
};
