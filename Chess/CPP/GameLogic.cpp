#include "../Headers/GameLogic.h"
#include "../Headers/Rook.h"
#include "../Headers/Knight.h"
#include "../Headers/Bishop.h"
#include "../Headers/King.h"
#include "../Headers/Queen.h"
#include "../Headers/Pawn.h"
#include "../Headers/EmptyPiece.h"

using namespace std;

void GameLogic::toVector(string graphicBoard)
{
	int i = 0;
	for (i = 0; i < GRAPHIC_BOARD_LENGTH; i++)
	{
		this->_boardPieces.push_back(charToPiece(graphicBoard[i], i));
	}
	
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
	int row = 8 - (index / 8);
	int col = index % 8;

	char col_letter = 'a' + col;

	string chess_board_index = string(1, col_letter) + to_string(row);

	return chess_board_index;
}

Player GameLogic::findPieceColor(char pieceLetter)
{
	if (isupper(pieceLetter))
	{
		return White;
	}
	return Black;
}

void GameLogic::movePieces()
{
}

void GameLogic::toGraphicBoard()
{
}
