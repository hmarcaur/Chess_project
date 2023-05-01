# include "Rook.hpp"

Rook::Rook(bool isBlack): Piece(isBlack, "Rook"){
	/*
	Class constructor 'Rook'.
	*/
	firstMove = true;
}

bool Rook::isValidMove(const Position &start, const Position &end, const Board* board) const{
	/*
	Returns 'true' if the move is valid.
	*/
	if(start.get_x() == end.get_x()) { // in column
		for(int y = min(start.get_y(), end.get_y()) + 1; y < max(start.get_y(), end.get_y()); y++){
			if(!board->emptySquare(start.get_x(), y)) return false; // non-empty square
		}
		return true;
	}

	if(start.get_y() == end.get_y()){ // in row
		for(int x = min(start.get_x(), end.get_x()) + 1; x < max(start.get_x(), end.get_x()); x++){
			if(!board->emptySquare(x, start.get_y())) return false; // non-empty square
		}
		return true;
	}
	return false;
}


void Rook::setFirstMove(){
	/*
	Turns the boolean attribute 'firstMove' into 'true'.
	*/
	firstMove = false;
}

void Rook::resetFirstMove(){
	/*
	Reset the boolean attribute 'firstMove' to 'false'.
	*/
	firstMove = true;
}

bool Rook::getFirstMove() const{
	/*
	Getter method to 'firstMove' attribute.
	*/
	return firstMove;
}
