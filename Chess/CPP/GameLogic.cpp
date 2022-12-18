#include "../Headers/GameLogic.h"
#include "../Headers/Rook.h"
#include "../Headers/Knight.h"
#include "../Headers/Bishop.h"
#include "../Headers/King.h"
#include "../Headers/Queen.h"
#include "../Headers/Pawn.h"
#include "../Headers/EmptyPiece.h"

using namespace std;

GameLogic::GameLogic(const string graphicBoard)
{
	this->_boardPieces = toVector(graphicBoard);
	this->_turn = charToPlayer(graphicBoard[STARTING_PLAYER]);
}

GameLogic::~GameLogic()
{
	int i = 0;
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		delete(this->_boardPieces[i]);
	}
	this->_boardPieces.clear();
}

vector<Piece*> GameLogic::toVector(const string graphicBoard)
{
	int i = 0;
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		this->_boardPieces.push_back(charToPiece(graphicBoard[i], i));
	}
	return this->_boardPieces;
}

Piece* GameLogic::charToPiece(const char pieceLetter, const int index) const
{
	switch (pieceLetter)
	{
	case ROOK_CHAR_LOWER:
	case ROOK_CHAR_UPPER:
		return new Rook(ROOK, indexToPlacement(index), findPieceColor(pieceLetter));
		break;
	case KNIGHT_CHAR_LOWER:
	case KNIGHT_CHAR_UPPER:
		return new Knight(KNIGHT, indexToPlacement(index), findPieceColor(pieceLetter));
		break;
	case BISHOP_CHAR_LOWER:
	case BISHOP_CHAR_UPPER:
		return new Bishop(BISHOP, indexToPlacement(index), findPieceColor(pieceLetter));
		break;
	case KING_CHAR_LOWER:
	case KING_CHAR_UPPER:
		return new King(KING, indexToPlacement(index), findPieceColor(pieceLetter));
		break;
	case QUEEN_CHAR_LOWER:
	case QUEEN_CHAR_UPPER:
		return new Queen(QUEEN, indexToPlacement(index), findPieceColor(pieceLetter));
		break;
	case PAWN_CHAR_LOWER:
	case PAWN_CHAR_UPPER:
		return new Pawn(PAWN, indexToPlacement(index), findPieceColor(pieceLetter));
		break;
	default:
		return new EmptyPiece(EMPTY_PIECE, indexToPlacement(index), findPieceColor(pieceLetter));
		break;
	}
}

string GameLogic::indexToPlacement(const int index) const
{
	int row = CHESS_BOARD_SIDE - (index / CHESS_BOARD_SIDE);
	int col = index % CHESS_BOARD_SIDE;

	char col_letter = 'a' + col;

	string chess_board_index = string(1, col_letter) + to_string(row);

	return chess_board_index;
}

int GameLogic::placementToIndex(const string placement)
{
	// Get the column letter from the placement string
	char col_letter = placement[0];

	// Convert the column letter to a number, with 'a' being 0 and 'h' being 7
	int col = col_letter - 'a';

	// Get the row number from the placement string
	int row = placement[1] - '0';

	// Convert the row number to a zero-based index, with 1 being 0 and 8 being 7
	row = CHESS_BOARD_SIDE - row;

	// Return the index by combining the row and column indices
	return row * CHESS_BOARD_SIDE + col;
}

void GameLogic::switchTurn()
{
	if (this->_turn == White)
	{
		this->_turn = Black;
	}
	else
	{
		this->_turn = White;
	}
}

Player GameLogic::findPieceColor(const char pieceLetter) const
{
	if (pieceLetter == EMPTY_PIECE_CHAR)
	{
		return None;
	}
	if (isupper(pieceLetter))
	{
		return White;
	}
	return Black;
}

Player GameLogic::charToPlayer(const char playerChar) const
{
	if (playerChar == '0')
	{
		return White;
	}

	return Black;
}
string GameLogic::movePieces(const string movment)
{
	int code = movmentCode(movment.substr(0, 2), movment.substr(2, 4));
	char codeChr = code + '0';

	string returnCode(1, codeChr);

	returnCode += '\0';


	return returnCode;
}

int GameLogic::movmentCode(const string source, const string destination) 
{
	if (checkCode7(source, destination))
	{
		return CODE_7;
	}
	return checkCodes(this->_boardPieces[placementToIndex(source)], this->_boardPieces[placementToIndex(destination)]);
}

bool GameLogic::checkCode7(const string source, const string destination) const
{
	return source == destination;
}

bool GameLogic::checkCode2(const Player sourcePlayer, const Player currentPlayer) const
{
	return sourcePlayer != currentPlayer;
}

bool GameLogic::checkCode3(const Player destPlayer, const Player currentPlayer) const
{
	return destPlayer == currentPlayer;
}

bool GameLogic::checkCode6(const Piece* srcP, const Piece* destP) const
{
	return srcP->isValidMove(destP->_placement, this->_boardPieces);
}

bool GameLogic::checkCode4(const string source, const string destination, const Player currentPlayer) 
{
	int i = 0;
	bool isCheck = false;
	vector<Piece*> currStateVector = this->_boardPieces;
	// change vector to the givven move
	commitMove(source, destination);
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		if (this->_boardPieces[i]->_color == opponentColor(currentPlayer))
		{
			isCheck = this->_boardPieces[i]->isValidMove(currPlayerKing(currentPlayer)->_placement, this->_boardPieces);
		}
	}
	if (isCheck)
	{
		// return vector to prevoius state
		this->_boardPieces = currStateVector;
	}

	return isCheck;
}

bool GameLogic::checkCode1(const Player currentPlayer, const string destination) const
{
	Piece* opponentKing = currPlayerKing(opponentColor(currentPlayer));

	return this->_boardPieces[placementToIndex(destination)]->isValidMove(opponentKing->_placement, this->_boardPieces);
}

void GameLogic::commitMove(const string source, const string destination)
{
	Piece* movedPiece = this->_boardPieces[placementToIndex(source)];

	this->_boardPieces[placementToIndex(source)] = new EmptyPiece(EMPTY_PIECE, source, None);

	delete(this->_boardPieces[placementToIndex(destination)]);

	movedPiece->_placement = destination;

	this->_boardPieces[placementToIndex(destination)] = movedPiece;

}

Piece* GameLogic::currPlayerKing(const Player currentPlayer) const
{
	int i = 0;
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		if (this->_boardPieces[i]->_type == KING)
		{
			if (this->_boardPieces[i]->_color == currentPlayer)
			{
				return this->_boardPieces[i];
			}
		}
	}
}

Player GameLogic::opponentColor(const Player currentPlayer) 
{
	if (currentPlayer == White)
	{
		return Black;
	}
	return White;
}

int GameLogic::checkCodes(const Piece* srcP, Piece* destP) 
{
	int despPiecePlacemnt = placementToIndex(destP->_placement);

	if (checkCode2(srcP->_color, this->_turn))
	{
		return CODE_2;
	}
	if (checkCode3(destP->_color, this->_turn))
	{
		return CODE_3;
	}
	if (!checkCode6(srcP, destP))
	{
		return CODE_6;
	}
	if (checkCode4(srcP->_placement, destP->_placement, this->_turn))
	{
		return CODE_4;
	}

	destP = this->_boardPieces[despPiecePlacemnt];

	if (checkCode1(this->_turn, destP->_placement))
	{
		switchTurn();
		return CODE_1;
	}

	switchTurn();
	return CODE_0;
}