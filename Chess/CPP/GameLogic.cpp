#include "../Headers/GameLogic.h"
#include "../Headers/Rook.h"
#include "../Headers/Knight.h"
#include "../Headers/Bishop.h"
#include "../Headers/King.h"
#include "../Headers/Queen.h"
#include "../Headers/Pawn.h"
#include "../Headers/EmptyPiece.h"
#include "../Headers/BoardManager.h"



GameLogic::GameLogic(const string graphicBoard)
{
	this->_turn = charToPlayer(graphicBoard[STARTING_PLAYER]);
}

Piece* GameLogic::charToPiece(const char pieceLetter, const int index) 
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

string GameLogic::indexToPlacement(const int index) 
{
	int row = CHESS_BOARD_SIDE - (index / CHESS_BOARD_SIDE);
	int col = index % CHESS_BOARD_SIDE;

	char col_letter = 'a' + col;

	string chess_board_index = string(1, col_letter) + std::to_string(row);

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

Player GameLogic::findPieceColor(const char pieceLetter) 
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


int GameLogic::movmentCode(const string source, const string destination, vector<Piece*>& board)
{
	if (checkCode7(source, destination))
	{
		return CODE_7;
	}
	return checkCodes(board[placementToIndex(source)], board[placementToIndex(destination)], board);
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

bool GameLogic::checkCode6(const Piece* srcP, const Piece* destP, vector<Piece*> board) const
{
	return srcP->isValidMove(destP->_placement, board);
}

bool GameLogic::checkCode4(const string source, const string destination, const Player currentPlayer, vector<Piece*>& board)
{
	int i = 0;
	bool isCheck = false;
	vector<Piece*> currStateVector;
	BoardManager::copyBoard(board, currStateVector);
	// change vector to the givven move
	commitMove(source, destination, board);
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		if (board[i]->_color == opponentColor(currentPlayer))
		{
			isCheck = board[i]->isValidMove(currPlayerKing(currentPlayer, board)->_placement, board);
			if (isCheck)
			{
				BoardManager::clearBoard(board);
				// return vector to prevoius state
				board = currStateVector;
				return isCheck;
			}
		}
	}
	
	BoardManager::clearBoard(currStateVector);
	
	return isCheck;
}

bool GameLogic::checkCode1(const Player currentPlayer, const string destination, vector<Piece*> board) const
{
	Piece* opponentKing = currPlayerKing(opponentColor(currentPlayer), board);

	return board[placementToIndex(destination)]->isValidMove(opponentKing->_placement, board);
}

Piece* GameLogic::currPlayerKing(const Player currentPlayer, vector<Piece*> board) const
{
	int i = 0;
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		if (board[i]->_type == KING)
		{
			if (board[i]->_color == currentPlayer)
			{
				return board[i];
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

void GameLogic::commitMove(const string source, const string destination, vector<Piece*>& board)
{
	Piece* movedPiece = board[GameLogic::placementToIndex(source)];

	board[GameLogic::placementToIndex(source)] = new EmptyPiece(EMPTY_PIECE, source, None);

	delete(board[GameLogic::placementToIndex(destination)]);

	movedPiece->_placement = destination;

	board[GameLogic::placementToIndex(destination)] = movedPiece;

}

int GameLogic::checkCodes(const Piece* srcP, Piece* destP, vector<Piece*>& board)
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
	if (!checkCode6(srcP, destP, board))
	{
		return CODE_6;
	}
	if (checkCode4(srcP->_placement, destP->_placement, this->_turn, board))
	{
		return CODE_4;
	}

	destP = board[despPiecePlacemnt];

	if (checkCode1(this->_turn, destP->_placement, board))
	{
		switchTurn();
		return CODE_1;
	}

	switchTurn();
	return CODE_0;
}