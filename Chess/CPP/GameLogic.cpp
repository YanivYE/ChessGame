#include "../Headers/GameLogic.h"
#include "../Headers/Rook.h"

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
		Rook * r = new Rook("Rook", );
		break;
	case 'n':
		break;
	case 'b':
		break;
	case 'k':
		break;
	case 'q':
		break;
	case 'p':
		break;
	default:
		break;
	}
}

string GameLogic::indexToPlacement(int index)
{
	return string();
}

void GameLogic::movePieces()
{
}

void GameLogic::toGraphicBoard()
{
}
