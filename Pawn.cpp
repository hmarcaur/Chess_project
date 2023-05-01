# include "Pawn.hpp"

Pawn::Pawn(bool isBlack): Piece(isBlack, "Pawn"){
	/*
	Class constructor 'Pawn'.
	*/
	firstMove = true;
}

bool Pawn::isValidMove(const Position &start, const Position &end, const Board* board) const{
	/*
	Returns 'true' if the move is valid.
	*/
	// Diagonal grip
	if(!board->emptySquare(end.get_x(), end.get_y()) && start.get_distX(end) == 1){
		if((getIsBlack() && end.get_y() == start.get_y() + 1) || (!getIsBlack() && end.get_y() == start.get_y() - 1)){
			return true;
		}
	}

	// If that is its first movement and the two squares in front of it are empties
	// it can move two squares forward.
	if(firstMove && getIsBlack() && start.get_y() == 1 && board->emptySquare(end.get_x(), end.get_y())){
		if((end.get_y() == start.get_y() + 1) || (end.get_y() == start.get_y() + 2 \
		&& board->emptySquare(start.get_x(), start.get_y() + 1))){
			return true;
		}
		return false;
	}
	if(firstMove && !getIsBlack() && start.get_y() == 6 && board->emptySquare(end.get_x(), end.get_y())){
		if((end.get_y() == start.get_y() - 1) || (end.get_y() == start.get_y() - 2 \
		&& board->emptySquare(start.get_x(), start.get_y() - 1))){
			return true;
		}
		return false;
	}

	// "Basic" movement
	if(getIsBlack() && end.get_y() == start.get_y() + 1 && end.get_x() == start.get_x() \
	&& board->emptySquare(end.get_x(), end.get_y())){
		return true;
	}
	if(!getIsBlack() && end.get_y() == start.get_y() - 1 && end.get_x() == start.get_x() \
	&& board->emptySquare(end.get_x(), end.get_y())){
		return true;
	}

	// 'En passant' catching
	Position p2 = Position(end.get_x(), start.get_y()); // Position of the pawn to catching
	if(getIsBlack() && start.get_y() == 4 && start.get_distX(end) == 1 && end.get_y() == start.get_y() + 1 \
		&& !board->emptySquare(end.get_x(), start.get_y()) && board->getPiece(p2)->toString() == "pi"){
		return board->emptySquare(end.get_x(), end.get_y()) && board->getPiece(p2)->getFirstMove() \
		&& (board->getLastMove().end == p2);
	}

	if(!getIsBlack() && start.get_y() == 3 && start.get_distX(end) == 1 && end.get_y() == start.get_y() + 1 \
		&& !board->emptySquare(end.get_x(), start.get_y()) && board->getPiece(p2)->toString() == "Pi"){
		return board->emptySquare(end.get_x(), end.get_y()) && board->getPiece(p2)->getFirstMove() && \
		(board->getLastMove().end == p2);
	}

	else return false;
}

void Pawn::setFirstMove(){
	/*
	Turns the boolean attribute 'firstMove' into 'true'.
	*/
	firstMove = false;
}

void Pawn::resetFirstMove(){
	/*
	Reset the boolean attribute 'firstMove' to 'false'.
	*/
	firstMove = true;
}

bool Pawn::getFirstMove() const{
	/*
	Getter method to 'firstMove' attribute.
	*/
	return firstMove;
}
