#include "../Headers/BoardManager.h"


BoardManager::BoardManager(const string graphicBoard)
{
	this->_boardPieces = toVector(graphicBoard);
}

BoardManager::~BoardManager()
{
	clearBoard(this->_boardPieces);
}

void BoardManager::clearBoard(vector<Piece*> board)
{
	int i = 0;
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		delete(board[i]);
	}

	board.clear();
}

void BoardManager::copyBoard(vector<Piece*> originalBoard, vector<Piece*>& copyBoard)
{
	int i = 0;
	Piece* copiedPiece = nullptr;

	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		copiedPiece = copyPiece(originalBoard[i]);

		copyBoard.push_back(copiedPiece);
	}
}

Piece* BoardManager::copyPiece(Piece* piece)
{
	int index = GameLogic::placementToIndex(piece->_placement);
	Piece* newPiece = GameLogic::charToPiece(getPieceLetter(piece), index);

	newPiece->_type = piece->_type;
	newPiece->_placement = piece->_placement;
	newPiece->_color = piece->_color;

	return newPiece;
}

char BoardManager::getPieceLetter(Piece* piece)
{
	if (strcmp(piece->_type.c_str(), ROOK) == 0)
	{
		return getUpperLower(piece, ROOK_CHAR_LOWER);
	}
	else if (strcmp(piece->_type.c_str(), KNIGHT) == 0)
	{
		return getUpperLower(piece, KNIGHT_CHAR_LOWER);
	}
	else if (strcmp(piece->_type.c_str(), BISHOP) == 0)
	{
		return getUpperLower(piece, BISHOP_CHAR_LOWER);
	}
	else if (strcmp(piece->_type.c_str(), KING) == 0)
	{
		return getUpperLower(piece, KING_CHAR_LOWER);
	}
	else if (strcmp(piece->_type.c_str(), QUEEN) == 0)
	{
		return getUpperLower(piece, QUEEN_CHAR_LOWER);
	}
	else if (strcmp(piece->_type.c_str(), PAWN) == 0)
	{
		return getUpperLower(piece, PAWN_CHAR_LOWER);
	}
	else //if (strcmp(piece->_type.c_str(), EMPTY_PIECE) == 0)
	{
		return EMPTY_PIECE_CHAR;
	}
}

char BoardManager::getUpperLower(Piece* piece, char lowerLetter)
{
	if (piece->_color == Black)
	{
		return lowerLetter;
	}

	return lowerLetter - 32;
}

vector<Piece*> BoardManager::toVector(const string graphicBoard)
{
	int i = 0;
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		this->_boardPieces.push_back(GameLogic::charToPiece(graphicBoard[i], i));
	}
	return this->_boardPieces;
}

string BoardManager::movePieces(const string movment, GameLogic& algorithm)
{
	int code = algorithm.movmentCode(movment.substr(0, 2), movment.substr(2, 4), this->_boardPieces);
	char codeChr = code + '0';

	string returnCode(1, codeChr);

	returnCode += '\0';


	return returnCode;
}


