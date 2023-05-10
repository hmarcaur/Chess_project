# include "Bishop.hpp"

Bishop::Bishop(bool isBlack): Piece(isBlack, "bishop"){
	/*
	Class constructor 'Bishop'.
	*/
}

bool Bishop::isValidMove(const Position &start, const Position &end, const Board* board) const{
	/*
	Returns 'true' if the move is valid.
	*/
	int dy = start.get_distY(end);
	if(dy == start.get_distX(end)){ // Same diagonal
		int x;
		int y;
		for(int d = 1; d < dy; d++){
			x = start.get_x() < end.get_x() ? start.get_x() + d : start.get_x() - d; // width movement
			y = start.get_y() < end.get_y() ? start.get_y() + d : start.get_y() - d; // height movement
			if(!board->emptySquare(x, y)) return false; // non-empty square
		}
		return true;
	}
	return false;
}
