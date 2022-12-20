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


int GameLogic::movementCode(const string source, const string destination, vector<Piece*>& board)
{
	if (checkCode7(source, destination))
	{
		return INVALID_MOVE_NO_MOVMENT;
	}
	return checkCodes(board[placementToIndex(source)], board[placementToIndex(destination)], board);
}

/*
* Function gets the source, dest placements, and returns if the source and dest placements are the same.
* Input: source - the source placement
*		 destination - the destination placement
* Output: if the source and dest placements are the same
*/
bool GameLogic::checkCode7(const string source, const string destination) const
{
	// if the source and dest placements are the same
	return source == destination;
}

/*
* Function gets the source player, dest placement, and returns if the source player to move doesn't
* have piece of current player.
* Input: sourcePlayer - the source placement
*		 currentPlayer - the destination placement
* Output: if the source player to move doesn't have piece of current player
*/
bool GameLogic::checkCode2(const Player sourcePlayer, const Player currentPlayer) const
{
	// if the source player to move doesn't have piece of current player
	return sourcePlayer != currentPlayer;
}

/*
* Function gets the dest, current player colors and returns if the dest player
* piece has current player piece.
* Input: destPlayer - the source placement
*		 currentPlayer - the destination placement
* Output: if the dest player piece has current player piece
*/
bool GameLogic::checkCode3(const Player destPlayer, const Player currentPlayer) const
{
	return destPlayer == currentPlayer;
}

/*
* Function gets the source, dest pieces, a vector of the board, and return the if the moving
* src to dest is valid move.
* Input: srcP - the source placement
*		 destP - the destination placement
*		 board - the vector of the board
* Output: if the moving src to dest is valid move
*/
bool GameLogic::checkCode6(const Piece* srcP, const Piece* destP, vector<Piece*> board) const
{
	// check if valid or not move
	return srcP->isValidMove(destP->_placement, board);
}

/*
* Function gets the source, dest placement, the current player, a vector of the board, and return
* if check will accure on player because he moved a piece.
* Input: source - the source placement
*		 destination - the destination placement
*		 currentPlayer - the current player
*		 board - the vector of the board
* Output: if check will accure on player because he moved a piece
*/
bool GameLogic::checkCode4(const string source, const string destination, const Player currentPlayer, vector<Piece*>& board)
{
	int i = 0;
	bool isCheck = false;
	vector<Piece*> currStateVector; 
	// copy current state of vector and save it
	BoardManager::copyBoard(board, currStateVector);

	// change vector to the given move
	commitMove(source, destination, board);

	// loop through out the board 
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		// check if current piece color is openent color
		if (board[i]->_color == opponentColor(currentPlayer))
		{
			// if so, check if check will happen on current player because of the movement of 
			// current player
			isCheck = board[i]->isValidMove(currPlayerKing(currentPlayer, board)->_placement, board);

			if (isCheck)
			{
				// if so clear old board 
				BoardManager::clearBoard(board);

				// return vector to prevoius state
				board = currStateVector;

				return isCheck;
			}
		}
	}
	
	// if not, clear copied board
	BoardManager::clearBoard(currStateVector);
	
	// return false
	return isCheck;
}

/*
* Function gets the current player color, the destiantion placement, a vector of the board and returns 
* if check will accure on openent if we move a piece to the destiantion.
* Input: currentPlayer - the current player color
*		 destination - the destination placement 
		 board - the vector of the board
* Output: if check will accure on openent if we move a piece to the destiantion
*/
bool GameLogic::checkCode1(const Player currentPlayer, const string destination, vector<Piece*> board) const
{
	// get openent king
	Piece* opponentKing = currPlayerKing(opponentColor(currentPlayer), board);

	// after we already moved the player, we check if the destination piece can make move on king,
	// if so, so it's threatening the openents king
	return board[placementToIndex(destination)]->isValidMove(opponentKing->_placement, board);
}

//bool GameLogic::checkCode8(const Player currentPlayer, const string destination, vector<Piece*> board) const
//{
//	
//}

/*
* Function gets the current player color, and returns the current player's king
* Input: currentPlayer - the current player color
*		 board - the vector of the board
* Output: the current player's king
*/
Piece* GameLogic::currPlayerKing(const Player currentPlayer, vector<Piece*> board) const
{
	int i = 0;

	// loop through out the board
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		// check if currnt piece type is king
		if (board[i]->_type == KING)
		{
			// if king, check if it's this player's king
			if (board[i]->_color == currentPlayer)
			{
				// if so return this piece
				return board[i];
			}
		}
	}
}

/*
* Function gets the current player color, and returns the opposite color.
* Input: currentPlayer - the current player color
* Output: the opposite player color
*/
Player GameLogic::opponentColor(const Player currentPlayer) 
{
	// if white, return black
	if (currentPlayer == White)
	{
		return Black;
	}

	// if black, return white
	return White;
}

/*
* Function gets a source, dest placement, a vector of the board, and moves the piece from the 
* source placement, to the dest placement.
* Input: srcP - the source piece placement
*		 destP - the dest piece placement
*		 board - the vectoro of the board
* Output: none
*/
void GameLogic::commitMove(const string source, const string destination, vector<Piece*>& board)
{
	// get moving piece(source)
	Piece* movedPiece = board[GameLogic::placementToIndex(source)];

	// set source piece in board the empty new piece
	board[GameLogic::placementToIndex(source)] = new EmptyPiece(EMPTY_PIECE, source, None);

	// delete old piece from vector
	delete(board[GameLogic::placementToIndex(destination)]);

	// set new placement
	movedPiece->_placement = destination;
	
	// set moved piece in vector
	board[GameLogic::placementToIndex(destination)] = movedPiece;
}

/*
* Function gets a source, dest piece, a vector of the board, and returns the code that should happen
* if we move source piece to dest piece
* Input: srcP - the source piece
*		 destP - the dest piece
*		 board - the vectoro of the board
* Output: the code that should happen if we move source piece to dest piece
*/
int GameLogic::checkCodes(const Piece* srcP, Piece* destP, vector<Piece*>& board)
{
	// get index of dest piece
	int despPieceIndex = placementToIndex(destP->_placement);

	// check if user tried to move player that isn't his
	if (checkCode2(srcP->_color, this->_turn))
	{
		return INVALID_MOVE_NOT_YOUR_PLAYER;
	}
	// check if destination not free
	if (checkCode3(destP->_color, this->_turn))
	{
		return INVALID_MOVE_DESTINATION_NOT_FREE;
	}
	// check if invalid movement with piece
	if (!checkCode6(srcP, destP, board))
	{
		return INVALID_MOVE_ILLEGAL_MOVMENT;
	}
	// check if chess will accure because of move
	if (checkCode4(srcP->_placement, destP->_placement, this->_turn, board))
	{
		return INVALID_MOVE_CHESS_WILL_OCCURE;
	}

	// get dest p because we changed it after check code 4
	destP = board[despPieceIndex];

	// check if valid move, and made chess
	if (checkCode1(this->_turn, destP->_placement, board))
	{
		//if (checkCode8(this->_turn, destP->_placement, board))
		//{
		//	// add code 8
		// 
		//	switchTurn();
		//	return VALID_MOVE_CHECKMATE;
		//}

		// change turns
		switchTurn();

		return VALID_MOVE_MADE_CHESS;
	}

	// change turns
	switchTurn();

	// good move(code 0)
	return VALID_MOVE;
}