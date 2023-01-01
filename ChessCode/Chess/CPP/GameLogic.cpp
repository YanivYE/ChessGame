#include "../Headers/GameLogic.h"


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
* Function checks code 7 case. gets the source, dest placements, and returns if the source and dest placements are the same.
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
* Function checks code 2 case. gets the source player, dest placement, and returns if the source player to move doesn't
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
* Function checks code 3 case. gets the dest, current player colors and returns if the dest player
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
* Function checks code 6 case. gets the source, dest pieces, a vector of the board, and return the if the moving
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
* Function checks code 4 case - if chess will accure on player because he moved a piece. it just uses the 
* madeChess function following this move and operating it on the current player that made this move
* Input: source - the source placement
*		 destination - the destination placement
*		 currentPlayer - the current player
*		 board - the vector of the board
*		 checkingKingEscape - is this made chess function cheking king escape from chess case
* Output: if check will accure on player because he moved a piece
*/
bool GameLogic::checkCode4(const string source, const string destination, const Player currentPlayer, 
	vector<Piece*>& board, bool checkingKingEscape)
{
	return madeChess(source, destination, currentPlayer, board, checkingKingEscape);
}

/*
* Function checks code 1 case - if chess will accure on oppenent player because this player moved a piece. it just uses 
* the madeChess function following this move and operating it on the opponent player that will be in threat.
* it also changes the opponent king inCheck field to true 
* Input: source - the source placement
*		 destination - the destination placement
*		 opponentPlayer - the opponent player
*		 board - the vector of the board
*		 checkingKingEscape - is this made chess function cheking king escape from chess case
* Output: if check will accure on opponent because we moved a piece
*/
bool GameLogic::checkCode1(const string source, const string destination, const Player opponentPlayer,
	vector<Piece*>& board, bool checkingKingEscape) 
{
	bool isCheck = false;

	Piece* opponentKing = nullptr;

	// after we already moved the player, we check if the destination piece can make move on king,
	// if so, so it's threatening the openents king
	isCheck = madeChess(source, destination, opponentPlayer, board, checkingKingEscape);

	// get openent king
	opponentKing = currPlayerKing(opponentPlayer, board);

	if (isCheck)	// if the opponent king is in check
	{
		((King*)opponentKing)->_inCheck = true;
	}
	else
	{
		((King*)opponentKing)->_inCheck = false;
	}

	// return if we made check or not
	return isCheck;
}

/*
* Function checks code 8 case - if checkmate will accure on oppenent player because this player moved a piece. 
* it checks all checkmate conditions: the king is in check, he has no escape from the threat, it is not possible to 
* capture the attacker and it is not possible to interpose in the path between the attacker and the king
* Input: opponentPlayer - the opponent player
*		 board - the vector of the board
*		 attacker - the attacking piece
* Output: if checkmate will accure on opponent because we moved a piece
*/
bool GameLogic::checkCode8(const Player opponentPlayer, const Piece* attacker, vector<Piece*>& board)
{
	Piece* opponentKing = currPlayerKing(opponentPlayer, board);	// get opponent's king
	Piece* copiedAttacker = BoardManager::copyPiece(attacker);	// get copied attacker piece
	Piece* copiedKing = BoardManager::copyPiece(opponentKing);	// get copied opponent's king piece
	if (isPossibleKingEscape(opponentKing, opponentPlayer, board)||
		isPossibleSquareCapture(copiedAttacker->_placement, opponentPlayer, board) ||
		isPossibleInterpose(copiedAttacker, copiedKing, board))
		// check codeitions
	{
		return false;	// invalid checkmate
	}
	return true;	// made checkmate
}

/*
* Function checks code 9 case - if player made castling on his king.
* it checks if the source piece is a king and if made valid castling
* Input: srcP - the source piece
*		 destP - the destination piece
*		 board - the pieces vector of the board	
* Output: if made valid castling on king
*/
bool GameLogic::checkCode9(const Piece* srcP, const Piece* destP, const vector<Piece*> board) const
{
	return srcP->_type == KING && King::isCastling(destP->_placement, board, srcP);
}

/*
* Function checks if chess will accure on given player because of moved a piece. 
* it creates a copy of the current board- before performing this move, and changes the original board by the move 
* that was made. then it checks if there is any opponent piece that has a valid move to the current king, which means 
* he is in chess position
* Input: source - the source placement
*		 destination - the destination placement
*		 currentPlayer - the current player
*		 board - the vector of the board
*		 checkingKingEscape - is cheking king escape from chess case
* Output: if check will accure on given player following a moved piece
*/
bool GameLogic::madeChess(const string source, const string destination, const Player currentPlayer,
	vector<Piece*>& board, bool checkingKingEscape)
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
	if (checkingKingEscape)
	{
		// if so clear old board 
		BoardManager::clearBoard(board);
		board = currStateVector;
	}
	else
	{
		// if not, clear copied board
		BoardManager::clearBoard(currStateVector);
	}
	return isCheck;
}

/*
* Function checks if the given king has any possible escape from a chess threat
* it creates a vector of all possible king moves(one square around him), and checks if he has a valid move to one of them
* that hasnt caused chess too
* Input: king - the given king to check his escape
*		 currentPlayer - the current player
*		 board - the vector of the board
* Output: is there a possible square the king can escape to
*/
bool GameLogic::isPossibleKingEscape(Piece* king, const Player currentPlayer, vector<Piece*>& board)
{
	int i = 0;
	Piece* copiedKing = BoardManager::copyPiece(king);	// copied king
	vector<string> possibleMoves = ((King*)king)->getKingMoves(king->_placement);	// possible king moves vector

	for (i = 0; i < possibleMoves.size(); i++)	// running on the vector 
	{
		if (king->isValidMove(possibleMoves[i], board) && !checkCode3(board[placementToIndex(possibleMoves[i])]->_color, currentPlayer))
			// checks if the king has a valid move to the current square and it is not taken by own pieces
		{
			if (!madeChess(king->_placement, possibleMoves[i], currentPlayer, board, true))
				// checks if move hasnt made chess
			{
				king = copiedKing;	// return original king
				return true;
			}
			king = copiedKing;	// return original king
		}
	}
	// no possible escape
	return false;
}

/*
* Function checks if there is any opponent player that has a valid move to the given placement and hasn't made chess 
* it is used to check if there is a possible way to cpture the attacking piece that is threatning the king
* Input: destPlacement - the given destiantion
*		 currentPlayer - the current player
*		 board - the vector of the board
* Output: is there a possible valid square capture
*/
bool GameLogic::isPossibleSquareCapture(const string destPlacement, const Player oppenentPlayer, vector<Piece*>& board)
{
	int i = 0;
	for (i = 0; i < CHESS_BOARD_SIZE; i++)
	{
		if (board[i]->_color == oppenentPlayer)	// check every opponent player piece
		{
			if (board[i]->isValidMove(destPlacement, board))	// if 8the piece has a valid move to destination
			{
				if (!madeChess(board[i]->_placement, destPlacement, oppenentPlayer, board, true))	
					// checks if move hasnt made chess
				{
					return true;
				}
			}
		}
	}
	// no possible capture
	return false;
}

/*
* Function checks if the there is any possible interpose between the king and the attacking piece - to prevent chess threat
* it checks every square between the 2 pieces and findes out if any current player piece can capture it 
* Input: attacker - the attacking piece
*		 king - the current player king - undes chess
*		 board - the vector of the board
* Output: is there a possible interpose to prevent chess
*/
bool GameLogic::isPossibleInterpose(const Piece* attacker, const Piece* king, vector<Piece*>& board)
{
	// set two "points" of dest and current position like 2D array indexes
	int curPos[2] = { CHESS_BOARD_SIDE - (attacker->_placement[1] - '1') - 1, attacker->_placement[0] - 'a' };
	int destPos[2] = { CHESS_BOARD_SIDE - (king->_placement[1] - '1') - 1, king->_placement[0] - 'a' };
	string boardPlacement = "";

	if (attacker->_type == ROOK || attacker->_type == QUEEN)
		// if the piece is rook or queen - checking horizontal and vertical moves
	{
		if (curPos[1] == destPos[1])    // if the cols are the same - moving verticaly
		{
			for (int i = std::min(curPos[0], destPos[0]) + 1; i < std::max(curPos[0], destPos[0]); i++) // checking every square
			{
				boardPlacement = string(1, curPos[1] + 'a') + std::to_string(CHESS_BOARD_SIDE - i);	// square board placement
				if (isPossibleSquareCapture(boardPlacement, king->_color, board))
				{
					return true;
				}
				// every iteration gets a square between. check on the 
				// square if any of the king color players can move there
			}
		}
		else if (curPos[0] == destPos[0])   // if the rows are the same - moving horizontaly
		{
			for (int i = std::min(curPos[1], destPos[1]) + 1; i < std::max(curPos[1], destPos[1]); i++) // checking every square
			{
				boardPlacement = string(1, i + 'a') + std::to_string(CHESS_BOARD_SIDE - curPos[0]);		// square board placement
				if (isPossibleSquareCapture(boardPlacement, king->_color, board))
				{
					return true;
				}
				// every iteration gets a square between. check on the 
				// square if any of the king color players can move there
			}
		}
	}
	if (attacker->_type == BISHOP || attacker->_type == QUEEN)
		// if the piece is bishop or queen - checking diagnoly moves
	{
		if (abs(curPos[0] - destPos[0]) == abs(curPos[1] - destPos[1]))
			// if the cols difference is the same as the rows difference - moving diagnoly
		{
			int rowDir = (destPos[0] - curPos[0]) / abs(destPos[0] - curPos[0]);
			int colDir = (destPos[1] - curPos[1]) / abs(destPos[1] - curPos[1]);
			// dirs determine if we should decrease or increase the rows and cols each time 
			// when we check the diagnol

			int row = curPos[0] + rowDir;
			int col = curPos[1] + colDir;
			// row and col is the current placment in the diagnol we check

			while (row != destPos[0] && col != destPos[1])  // as long as we dont reach the diagnol end - checking every square
			{
				boardPlacement = string(1, col + 'a') + std::to_string(CHESS_BOARD_SIDE - row);		// square board placement
				if (isPossibleSquareCapture(boardPlacement, king->_color, board))
				{
					return true;
				}
				// every iteration gets a square between. check on the 
				// square if any of the king color players can move there
				
				// set next index in diangol
				row += rowDir;
				col += colDir;
			}
		}
	}
	// no possible interpose
	return false;
}

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
	Piece* movedPiece = board[placementToIndex(source)];
	if (movedPiece->_type == KING || movedPiece->_type == ROOK)
	{
		movedPiece->_moved = true;
	}

	// set source piece in board the empty new piece
	board[placementToIndex(source)] = new EmptyPiece(EMPTY_PIECE, source, None);

	// delete old piece from vector
	delete(board[placementToIndex(destination)]);

	// set new placement
	movedPiece->_placement = destination;
	
	// set moved piece in vector
	board[placementToIndex(destination)] = movedPiece;
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
	int destPieceIndex = placementToIndex(destP->_placement);
	Piece* initialSrc = nullptr;
	Piece* initialDst = nullptr;

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

	// copy pieces
	initialSrc = BoardManager::copyPiece(srcP);
	initialDst = BoardManager::copyPiece(destP);

	// check if chess will accure because of move
	if (checkCode4(srcP->_placement, destP->_placement, this->_turn, board, false))
	{
		delete(initialSrc);
		delete(initialDst);
		return INVALID_MOVE_CHESS_WILL_OCCURE;
	}

	// get dest p because we changed it after check code 4
	destP = board[destPieceIndex];

	// check if valid move, and made chess
	if (checkCode1(srcP->_placement, destP->_placement, opponentColor(this->_turn), board, false))
	{
		// get dest p because we changed it after check code 1
		destP = board[destPieceIndex];

		// check if valid move, and made checkmate
		if (checkCode8(opponentColor(this->_turn), destP, board))
		{
			switchTurnAndClearMemory(initialSrc, initialDst);
			return VALID_MOVE_CHECKMATE;
		}

		switchTurnAndClearMemory(initialSrc, initialDst);
		return VALID_MOVE_MADE_CHESS;
	}

	// check if valid move, and made castling
	if (checkCode9(initialSrc, initialDst, board))
	{
		switchTurnAndClearMemory(initialSrc, initialDst);
		return VALID_MOVE_MADE_CASTLING;
	}

	switchTurnAndClearMemory(initialSrc, initialDst);

	// good move(code 0)
	return VALID_MOVE;
}

/*
* Function switches the game turn after a valid move and deletes the copied pieces
* Input: initialSrc - the source piece
*		 initialDst - the dest piece
* Output: none
*/
void GameLogic::switchTurnAndClearMemory(Piece* initialSrc, Piece* initialDst)
{
	// change turns
	switchTurn();
	delete(initialSrc);
	delete(initialDst);
}