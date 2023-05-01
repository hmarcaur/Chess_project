# include "Queen.hpp"

Queen::Queen(bool isBlack): Bishop(isBlack), Rook(isBlack), Piece(isBlack, "Queen"){
	/*
	Class constructor 'Queen'.
	*/
}

bool Queen::isValidMove(const Position &start, const Position &end, const Board* board) const{
	/*
	Returns 'true' if the move is valid. This is verified by looking at the valid movements of
	the 'Rook' and the 'Bishop' from whom the 'Queen' inherits.
	*/
	return Rook::isValidMove(start, end, board) || Bishop::isValidMove(start, end, board);
}
