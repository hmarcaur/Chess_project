# include "Knight.hpp"

Knight::Knight(bool isBlack): Piece(isBlack, "Knight"){
	/*
	Class constructor 'Knight'.
	*/
}

bool Knight::isValidMove(const Position &start, const Position &end, const Board* board) const{
	/*
	Returns 'true' if the move is valid.
	*/
	int distX = start.get_distX(end);
	int distY = start.get_distY(end);
	// 2,1 or -2,-1, or -1,2... (8)
	return distX != 0 && distY != 0 && distX + distY == 3;
}
