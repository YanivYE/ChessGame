#include "../Headers/BoardManager.h"

/*
* Function is the constructor for the board manager, it gets a graphicBoard and sets the
* bishop object member to the function paramter.
* Input: graphicBoard - the string of the board
* Output: none
*/
BoardManager::BoardManager(const string graphicBoard)
{
	// create vector pieces by string
	this->_boardPieces = toVector(graphicBoard);
}

/*
* Function is the destructor for the board manager
* Input: None
* Output: none
*/
BoardManager::~BoardManager()
{
	clearBoard(this->_boardPieces);
}

/*
* Function gets a vector of a board, and deletes all the elements.
* Input: board - a vector of a board
* Output: none
*/
void BoardManager::clearBoard(vector<Piece*> board)
{
	int i = 0;

	// loop throught out board
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		// delete current element
		delete(board[i]);
	}

	// clear all elements
	board.clear();
}

/*
* Function gets a vector of an original board, a copy board, and copies the elements from the 
* original baord to the copy board(deep copy).
* Input: originalBoard - a vector of an original board
*		 copyBoard - a vector of the copy board
* Output: none
*/
void BoardManager::copyBoard(vector<Piece*> originalBoard, vector<Piece*>& copyBoard)
{
	int i = 0;
	Piece* copiedPiece = nullptr;

	// loop through out the pieces
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		// copy piece
		copiedPiece = copyPiece(originalBoard[i]);

		// add it to the vector
		copyBoard.push_back(copiedPiece);
	}
}

/*
* Function gets a pointer to a piece, copies it to a new allocated piece, and returns the new piece
* Input: piece - the piece to copy
* Output: the copied piece pointer
*/
Piece* BoardManager::copyPiece(const Piece* piece)
{
	// get index
	int index = GameLogic::placementToIndex(piece->_placement);
	// turn char(gets the char from the original piece) to piece
	Piece* newPiece = GameLogic::charToPiece(getPieceLetter(piece), index);

	// set members
	newPiece->_type = piece->_type;
	newPiece->_placement = piece->_placement;
	newPiece->_color = piece->_color;
	newPiece->_moved = piece->_moved;

	if (piece->_type == KING)	// if the piece is a king copy the inCheck field
	{
		((King*)newPiece)->_inCheck = ((King*)piece)->_inCheck;
	}

	// return new members
	return newPiece;
}

/*
* Function gets a pointer to a piece, and returns their char in upper/lower case by the piece player.
* Input: piece - the piece to gets it's letter
* Output: the piece's char
*/
char BoardManager::getPieceLetter(const Piece* piece)
{
	// string "switch case" for the pieces names, and returns their char in upper/lower
	// case by the piece player.

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
	else 
	{
		return EMPTY_PIECE_CHAR;
	}
}

/*
* Function gets a pointer to a piece, a lower letter char and returns upper/lower letter by the piece
* color(black - 1, white - 0).
* Input: piece - the piece to gets it's color
*		 lowerLetter - the lower letter to return / change
* Output: the piece's char upper/lower
*/
char BoardManager::getUpperLower(const Piece* piece, char lowerLetter)
{
	// if black so return lower
	if (piece->_color == Black)
	{
		return lowerLetter;
	}

	// if white return upper
	return lowerLetter - LOWER_TO_UPPER;
}

/*
* Function gets a string of the board, and returns a vector with the pieces from the string.
* Input: graphicBoard - the string of the board
* Output: a vector with all the pieces from the string
*/
vector<Piece*> BoardManager::toVector(const string graphicBoard)
{
	int i = 0;

	// loop through out the board size
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		// add current piece from the current char in string
		this->_boardPieces.push_back(GameLogic::charToPiece(graphicBoard[i], i));
	}

	// return vector
	return this->_boardPieces;
}

/*
* Function gets a string movement string(d2d3), a gamelogic object and returns the code from the wanted
* movement.
* Input: movement - a string to move from to move to(d2d3)
*		 algorithm - a gamelogic object
* Output: the code from the wanted movement.
*/
string BoardManager::movePieces(const string movement, GameLogic& algorithm)
{
	// get valid/invalid code by sending "d2", "d3", and the vector of pieces
	int code = algorithm.movementCode(movement.substr(0, 2), movement.substr(2, 4), this->_boardPieces);
	char codeChr = code + '0'; // convert it to a char

	// create string with the char
	string returnCode(1, codeChr);

	if (code == 9)	// if code 9 - castling
	{
		returnCode += ",";
		returnCode += rookCastlingMovement(movement.substr(0, 2), movement.substr(2, 4), algorithm);
		// add the rook castling movement to the code string
	}

	// add NULL at the end of the string
	returnCode += '\0';

	// return the code string
	return returnCode;
}

/*
* Function gets a string movement for a rook castling. the string includes the source placement 
* and the destination for performing the castling, representned by two 2D array indexes seperated by coma
* the movement dependes on wich king is castling and which type of castking he chose- big or small
* Input: kingSource - chosen king initial placement
*		 kingDest - chosen king castling destination
*		 algorithm - the game logic algorithm for commiting the castling move on the baord
* Output: rook movement string
*/
string BoardManager::rookCastlingMovement(string kingSource, string kingDest, GameLogic& algorithm)
{
	string rookMovement = "";
	if (kingSource == WHITE_KING_INITIAL_PLACEMENT)	// white king castling
	{
		if (kingDest == SMALL_CASTLING_WHITE_KING_PLACEMENT)	// performing small castling
		{
			rookMovement += (convertRookIndexes(LEFT_WHITE_ROOK_INITIAL_PLACEMENT) + "," + 
				convertRookIndexes(LEFT_WHITE_ROOK_CASTLING_PLACEMENT));  // create rook castling indexes
			algorithm.commitMove(LEFT_WHITE_ROOK_INITIAL_PLACEMENT, LEFT_WHITE_ROOK_CASTLING_PLACEMENT, this->_boardPieces);
			// commit castling move
		}
		else
		{
			rookMovement += (convertRookIndexes(RIGHT_WHITE_ROOK_INITIAL_PLACEMENT) + "," + 
				convertRookIndexes(RIGHT_WHITE_ROOK_CASTLING_PLACEMENT));  // create rook castling indexes
			algorithm.commitMove(RIGHT_WHITE_ROOK_INITIAL_PLACEMENT, RIGHT_WHITE_ROOK_CASTLING_PLACEMENT, this->_boardPieces);
			// commit castling move
		}
	}
	else		
	{
		if (kingDest == SMALL_CASTLING_BLACK_KING_PLACEMENT)	// performing small castling
		{
			rookMovement += (convertRookIndexes(LEFT_BLACK_ROOK_INITIAL_PLACEMENT) + "," +
				convertRookIndexes(LEFT_BLACK_ROOK_CASTLING_PLACEMENT));	// create rook castling indexes
			algorithm.commitMove(LEFT_BLACK_ROOK_INITIAL_PLACEMENT, LEFT_BLACK_ROOK_CASTLING_PLACEMENT, this->_boardPieces);
			// commit castling move
		}
		else
		{
			rookMovement += (convertRookIndexes(RIGHT_BLACK_ROOK_INITIAL_PLACEMENT) + "," + 
				convertRookIndexes(RIGHT_BLACK_ROOK_CASTLING_PLACEMENT));	// create rook castling indexes
			algorithm.commitMove(RIGHT_BLACK_ROOK_INITIAL_PLACEMENT, RIGHT_BLACK_ROOK_CASTLING_PLACEMENT, this->_boardPieces);
			// commit castling move
		}
	}
	return rookMovement;
}

/*
* Function converts board placements indexes to 2D array indexes seperated by a coma
* Input: boardIndex - board index string- e2
* Output: rook index
*/
string BoardManager::convertRookIndexes(string boardIndex)
{
	string rookIndex = "";

	rookIndex += std::to_string((CHESS_BOARD_SIDE - (boardIndex[1] - '1') - 1));  // convert board index number 
	// to 2D array index 
	rookIndex += ",";
	rookIndex += std::to_string((boardIndex[0] - 'a'));		// convert board index letter to 2D array index 

	return rookIndex;
}