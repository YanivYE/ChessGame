#include "../Headers/GameLogic.h"
#include "../Headers/Rook.h"
#include "../Headers/Knight.h"
#include "../Headers/Bishop.h"
#include "../Headers/King.h"
#include "../Headers/Queen.h"
#include "../Headers/Pawn.h"
#include "../Headers/EmptyPiece.h"
#include "../Headers/BoardManager.h"


/*
* Function is the constructor for the game logic object, it gets the graphic board string
* Input: graphicBoard - the initial board arangment string
* Output: none
*/
GameLogic::GameLogic(const string graphicBoard)
{
	this->_turn = charToPlayer(graphicBoard[STARTING_PLAYER]);	
	// set the initial turn as the 64th char in the string
}

/*
* Function is converting the board string char to its piece type
* Input: pieceLetter - the char from the string
*        index - the index of the char
* Output: piece pointer
*/
Piece* GameLogic::charToPiece(const char pieceLetter, const int index) 
{
	switch (pieceLetter)
	{
	case ROOK_CHAR_LOWER:
	case ROOK_CHAR_UPPER:
		// the letter r represents a rook type
		return new Rook(ROOK, indexToPlacement(index), findPieceColor(pieceLetter));  // create a rook
		break;
	case KNIGHT_CHAR_LOWER:
	case KNIGHT_CHAR_UPPER:
		// the letter n represents a knight type
		return new Knight(KNIGHT, indexToPlacement(index), findPieceColor(pieceLetter)); // create a knight
		break;
	case BISHOP_CHAR_LOWER:
	case BISHOP_CHAR_UPPER:
		// the letter b represents a bishop type
		return new Bishop(BISHOP, indexToPlacement(index), findPieceColor(pieceLetter)); // create a bishop
		break;
	case KING_CHAR_LOWER:
	case KING_CHAR_UPPER:
		// the letter k represents a king type
		return new King(KING, indexToPlacement(index), findPieceColor(pieceLetter)); // create a king
		break;
	case QUEEN_CHAR_LOWER:
	case QUEEN_CHAR_UPPER:
		// the letter q represents a queen type
		return new Queen(QUEEN, indexToPlacement(index), findPieceColor(pieceLetter)); // create a queen
		break;
	case PAWN_CHAR_LOWER:
	case PAWN_CHAR_UPPER:
		// the letter p represents a pawn type
		return new Pawn(PAWN, indexToPlacement(index), findPieceColor(pieceLetter)); // create a pawn
		break;
	default:
		// deafult option - empty piece type
		return new EmptyPiece(EMPTY_PIECE, indexToPlacement(index), findPieceColor(pieceLetter)); // create a rook
		break;
	}
}

/*
* Function is converting the vector index to its board placement
* Input: index - the index of the piece in the vector
* Output: chess board index
*/
string GameLogic::indexToPlacement(const int index) 
{
	int row = CHESS_BOARD_SIDE - (index / CHESS_BOARD_SIDE);
	int col = index % CHESS_BOARD_SIDE;
	// get the 2D array indexes of the vector index

	char col_letter = 'a' + col;	// set col as a letter

	string chess_board_index = string(1, col_letter) + std::to_string(row); 
	// create a string from the index like e2 for example

	return chess_board_index;
}

/*
* Function is converting the board placement to its vector index
* Input: placement - the board placement of the piece
* Output: vector index
*/
int GameLogic::placementToIndex(const string placement)
{
	// Get the column letter from the placement string
	char col_letter = placement[0];

	// Convert the column letter to a number
	int col = col_letter - 'a';

	// Get the row number from the placement string
	int row = placement[1] - '0';

	// Convert the row number to a row index
	row = CHESS_BOARD_SIDE - row;

	// Return the vector index 
	return row * CHESS_BOARD_SIDE + col;
}

/*
* Function is switching the current game turn - sets the opposite player 
* Input: none
* Output: none
*/
void GameLogic::switchTurn()
{
	if (this->_turn == White)
	{
		// if white switch to black
		this->_turn = Black;
	}
	else
	{
		// if black switch to white
		this->_turn = White;
	}
}

/*
* Function is getting the current piece letter color - if the letter is upper it is white, 
* and if it is lower than its black
* Input: pieceLetter - the char from the string
* Output: color
*/
Player GameLogic::findPieceColor(const char pieceLetter) 
{
	if (pieceLetter == EMPTY_PIECE_CHAR)
	{
		// if the char is '#' than this is an empty piece so return none color
		return None;
	}
	if (isupper(pieceLetter))
	{
		// if the char is upper than this is a white piece 
		return White;
	}
	// if the char is lower than this is a black piece 
	return Black;
}

/*
* Function is converting the string 64th char into the starting player
* Input: playerChar - the char from the string that represents the starting player turn
* Output: starting player color
*/
Player GameLogic::charToPlayer(const char playerChar) const
{
	if (playerChar == '0')
		// char '0' - is white color 
	{
		return White;
	}
	// any other char is black color
	return Black;
}

/*
* Function is checking the given movment and returns the suitable code for this move
* Input: source - the current placement string of the piece 
*        destination - the destination placement string of the piece 
*	     board - board pieces vector
* Output: movement code
*/
int GameLogic::movementCode(const string source, const string destination, vector<Piece*>& board)
{
	if (checkCode7(source, destination))
		// if code 7 function returned true return 7 as the code
	{
		return INVALID_MOVE_NO_MOVMENT;
	}
	return checkCodes(board[placementToIndex(source)], board[placementToIndex(destination)], board);
	// check the rest of codes
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

//bool GameLogic::checkCode8(const Player currentPlayer, const string destination, vector<Piece*> board) const
//{
//	
//}

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
		return INVALID_MOVE_NOT_YOUR_PLAYER;
	}
	if (checkCode3(destP->_color, this->_turn))
	{
		return INVALID_MOVE_DESTINATION_NOT_FREE;
	}
	if (!checkCode6(srcP, destP, board))
	{
		return INVALID_MOVE_ILLEGAL_MOVMENT;
	}
	if (checkCode4(srcP->_placement, destP->_placement, this->_turn, board))
	{
		return INVALID_MOVE_CHESS_WILL_OCCURE;
	}

	destP = board[despPiecePlacemnt];

	if (checkCode1(this->_turn, destP->_placement, board))
	{
		//if (checkCode8(this->_turn, destP->_placement, board))
		//{
		//	// add code 8
		// 
		//	switchTurn();
		//	return VALID_MOVE_CHECKMATE;
		//}
		switchTurn();
		return VALID_MOVE_MADE_CHESS;
	}

	switchTurn();
	return VALID_MOVE;
}