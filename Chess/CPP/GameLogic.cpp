#include "../Headers/GameLogic.h"
#include "../Headers/Rook.h"
#include "../Headers/Knight.h"
#include "../Headers/Bishop.h"
#include "../Headers/King.h"
#include "../Headers/Queen.h"
#include "../Headers/Pawn.h"
#include "../Headers/EmptyPiece.h"

using namespace std;

GameLogic::GameLogic(string graphicBoard)
{
	this->_boardPieces = toVector(graphicBoard);
	this->_turn = Player(int(graphicBoard[STARTING_PLAYER]) - '0');
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

std::vector<Piece*> GameLogic::toVector(string graphicBoard)
{
	int i = 0;
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		this->_boardPieces.push_back(charToPiece(graphicBoard[i], i));
	}
	return this->_boardPieces;
}

Piece* GameLogic::charToPiece(char pieceLetter, int index)
{
	switch (pieceLetter)
	{
	case 'r':
		return new Rook(ROOK, indexToPlacement(index), findPieceColor(pieceLetter));
		break;
	case 'n':
		return new Knight(KNIGHT, indexToPlacement(index), findPieceColor(pieceLetter));
		break;
	case 'b':
		return new Bishop(BISHOP, indexToPlacement(index), findPieceColor(pieceLetter));
		break;
	case 'k':
		return new King(KING, indexToPlacement(index), findPieceColor(pieceLetter));
		break;
	case 'q':
		return new Queen(QUEEN, indexToPlacement(index), findPieceColor(pieceLetter));
		break;
	case 'p':
		return new Pawn(PAWN, indexToPlacement(index), findPieceColor(pieceLetter));
		break;
	default:
		return new EmptyPiece(EMPTY_PIECE, indexToPlacement(index), findPieceColor(pieceLetter));
		break;
	}
}

string GameLogic::indexToPlacement(int index)
{
	int row = CHESS_BOARD_SIDE - (index / 8);
	int col = index % 8;

	char col_letter = 'a' + col;

	string chess_board_index = string(1, col_letter) + to_string(row);

	return chess_board_index;
}

int GameLogic::placementToIndex(string placement)
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


Player GameLogic::findPieceColor(char pieceLetter)
{
	if (pieceLetter == '#')
	{
		return None;
	}
	if (isupper(pieceLetter))
	{
		return White;
	}
	return Black;
}

string GameLogic::movePieces(string movment)
{
	int code = 0;
	string source = movment.substr(0, 2);
	string destination = movment.substr(2, 4);
	
	code = movmentCode(source, destination);

	switchTurn();
	string charCode = "";
	charCode = (int(code) - '0') + '\0';
	return charCode;
}

void GameLogic::switchTurn()
{
	if (this->_turn == White)
	{
		this->_turn == Black;
	}
	else
	{
		this->_turn == White;
	}
}

int GameLogic::movmentCode(string source, string destination)
{
	if (checkCode7(source, destination))
	{
		return 7;
	}
	return checkCodes(this->_boardPieces[placementToIndex(source)], this->_boardPieces[placementToIndex(destination)]);
}

bool GameLogic::checkCode7(string source, string destination)
{
	return source == destination;
}

bool GameLogic::checkCode2(Player sourcePlayer, Player currentPlayer)
{
	return sourcePlayer != currentPlayer;
}

bool GameLogic::checkCode3(Player destPlayer, Player currentPlayer)
{
	return destPlayer == currentPlayer;
}

bool GameLogic::checkCode6(Piece* srcP, Piece* destP)
{
	return srcP->isValidMove(destP->_placement);
}

bool GameLogic::checkCode4(Player currentPlayer)
{
	int i = 0;
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		if (this->_boardPieces[i]->_color == opponentColor(currentPlayer))
		{
			return this->_boardPieces[i]->isValidMove(currPlayerKing(currentPlayer)->_placement);
		}
	}
}

Piece* GameLogic::currPlayerKing(Player currentPlayer)
{
	int i = 0;
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		if (this->_boardPieces[i]->_isKing)
		{
			if (this->_boardPieces[i]->_color == currentPlayer)
			{
				return this->_boardPieces[i];
			}
		}
	}
}

Player GameLogic::opponentColor(Player currentPlayer)
{
	if (currentPlayer == White)
	{
		return Black;
	}
	return White;
}

int GameLogic::checkCodes(Piece* srcP, Piece* destP)
{
	if (checkCode2(srcP->_color, this->_turn))
	{
		return 2;
	}
	if (checkCode3(destP->_color, this->_turn))
	{
		return 3;
	}
	if (checkCode6(srcP, destP))
	{
		return 6;
	}
	if (checkCode4(this->_turn))
	{
		return 4;
	}

}


