#include "../Headers/Piece.h"

Piece::Piece(string type, string placement, Player color)
{
	this->_placement = placement;
	this->_type = type;
	this->_color = color;
}
