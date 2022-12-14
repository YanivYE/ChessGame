#include "Piece.h"

Piece::Piece(string type, string placement, Player player)
{
	this->_placement = placement;
	this->_type = type;
	this->_player = player;
}
