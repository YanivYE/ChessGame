#include "../Headers/Piece.h"

/*
* Function is the constructor for a piece, it gets a type, placement, player color and sets the
* piece object members to the function paramters.
* Input: type - the type of the piece
*        placement - the placement of piece(a2, a3, f5)
*        player - the player color
* Output: none
*/
Piece::Piece(const string type, const string placement, const Player color)
{
	this->_placement = placement;
	this->_type = type;
	this->_color = color;
    this->_moved = false;
}

/*
* Function is the copy constructor for a piece, it gets other piece and copies it into this object
* Input: other - other piece object reference
* Output: none
*/
Piece::Piece(const Piece& other)
{
    *this = other;
}

/*
* Function is checking if there is any possible to interpose between the piece and the destination
* so basiclly if the moving path is clear of players- yours and yout opponent's
* Input: dest - the destination to move the piece to
*        board - board pieces vector
* Output: path clear or not
*/
bool Piece::clearMovingPath(const string dest, const vector<Piece*> board) const
{
    // set two "points" of dest and current position like 2D array indexes
    int curPos[2] = { CHESS_BOARD_SIDE - (this->_placement[1] - '1') - 1, this->_placement[0] - 'a' };
    int destPos[2] = { CHESS_BOARD_SIDE - (dest[1] - '1') - 1, dest[0] - 'a' };

    if (this->_type == ROOK || this->_type == QUEEN || this->_type == KING)
        // if the piece is rook or queen - checking horizontal and vertical moves
    {
        if (curPos[1] == destPos[1])    // if the cols are the same - moving verticaly
        {
            for (int i = std::min(curPos[0], destPos[0]) + 1; i < std::max(curPos[0], destPos[0]); i++)
            {
                // take every square of the chess board between the two indexes and check if it is taken 
                // by any piece other than an empty piece
                if (board[i * CHESS_BOARD_SIDE + curPos[1]]->_type != EMPTY_PIECE)
                {
                    return false;
                    // return false if it is taken
                }
            }
        }
        else if (curPos[0] == destPos[0])   // if the rows are the same - moving horizontaly
        {
            for (int i = std::min(curPos[1], destPos[1]) + 1; i < std::max(curPos[1], destPos[1]); i++)
            {
                // take every square of the chess board between the two indexes and check if it is taken 
                // by any piece other than an empty piece
                if (board[curPos[0] * CHESS_BOARD_SIDE + i]->_type != EMPTY_PIECE)
                {
                    return false;
                    // return false if it is taken
                }
            }
        }
    }
    if (this->_type == BISHOP || this->_type == QUEEN)
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

            while (row != destPos[0] && col != destPos[1])  // as long as we dont reach the diagnol end
            {
                // take every square of the chess board between the two indexes and check if it is taken 
                // by any piece other than an empty piece
                if (board[row * CHESS_BOARD_SIDE + col]->_type != EMPTY_PIECE)
                {
                    return false;
                    // return false if it is taken
                }
                // set next index in diangol
                row += rowDir;
                col += colDir;
            }
        }
    }
    return true;
}

/*
* Function is overriding the = operator - deep copies another piece into this piece
* Input: other - other piece object reference
* Output: piece reference
*/
Piece& Piece::operator=(const Piece& other)
{
    if (this == &other) 
        // tries to copy the object to itself
    {
        return *this;
    }

    // shallow copy fields
    this->_color = other._color;
    this->_placement = other._placement;
    this->_type = other._type;
    this->_moved = other._moved;


    return *this;
}


/*
* Function gets a player color, and returns the intial row pos of the pawn from that color
* Input: color - the color(black - white)
* Output: the intial row pos of the pawn from that color
*/
int Piece::getInitialRow(const Piece* piece) const
{
    if (piece->_type == PAWN)
    {
        if (piece->_color == White)
        {
            // return white initial row
            return PAWN_INITIAL_ROW_INDEX_WHITE;
        }

        // return black initial row
        return PAWN_INITIAL_ROW_INDEX_BLACK;
    }
    if (piece->_color == White)
    {
        // return white initial row
        return PIECE_INITIAL_ROW_INDEX_WHITE;
    }

    // return black initial row
    return PIECE_INITIAL_ROW_INDEX_BLACK;
    
}
