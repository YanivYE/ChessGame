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