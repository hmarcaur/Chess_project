# include "Bishop.hpp"

Bishop::Bishop(bool isBlack): Piece(isBlack, "Bishop"){
	/*
	Class constructor 'Bishop'.
	*/
}

bool Bishop::isValidMove(const Position &start, const Position &end, const Board* board) const{
	/*
	Returns 'true' if the move is valid.
	*/
	int dy = start.get_distY(end);
	if(dy == start.get_distX(end)){
		for(int d = 1; d < dy; d++){
			if(!board->emptySquare(start.get_x() + d, start.get_y() + d)) return false; // non-empty square
		}
		return true;
	}
	return false;
}
