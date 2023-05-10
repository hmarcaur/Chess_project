# include "King.hpp"

King::King(bool isBlack): Piece(isBlack, "king"){
	/*
	Class constructor 'King'.
	*/
	firstMove = true;
}

bool King::isValidMove(const Position &start, const Position &end, const Board* board) const{
	/*
	Returns 'true' if the move is valid.
	*/
	if(start.get_distX(end) <= 1 && start.get_distY(end) <= 1) return true;
	else if(start.get_y() == end.get_y() && start.get_distX(end) == 2){ // Castling
		if(!firstMove) return false;
		// It is its first movement
		int min_x = min(start.get_x(), end.get_x());
		unordered_set<Position, PositionHash> positions = board->getPiecePosition("all", !board->getPiece(start)->getIsBlack());
		for(int d = 0; d <= 2; d++){ // The king moves from two squares
			for(auto it = positions.begin(); it != positions.end(); it++){
					if(board->getPiece(*it)->isValidMove(*it, Position(min_x + d, start.get_y()), board)) return false;
					// The king is (or could be) in check on at least one of the squares of its movement.
				}
				// Note : it is not necessary to move the king as it will not make new squares 'checking' !
				// i.e. The only case is if an opponent piece (rook or queen) is on the other side of the castling
				// but in which case the king would already be in check.
			if(min_x + d != start.get_x() && !board->emptySquare(min_x + d, start.get_y())) return false; // Non-empty squares
		}
		// The king is not in check on the squares of its movement and there are empties.
		string rookName = board->getPiece(start)->getIsBlack() ? "Ro" : "ro";
		if(end.get_x() > start.get_x()){ // On the right (little castling)
			Position rookPosition = Position(board->getWidth() - 1, start.get_y());
			if(board->getPiece(rookPosition)->toString() == rookName && board->getPiece(rookPosition)->getFirstMove()){
				// This is a rook and this is its first move (so this is the right one)
				return true;
			}
			else return false;
		}
		else{ // On the left (great castling)
			Position rookPosition = Position(0, start.get_y());
			if(board->getPiece(rookPosition)->toString() == rookName && board->getPiece(rookPosition)->getFirstMove()){
				// This is a rook and this is its first move (so this is the left one)
				return board->emptySquare(end.get_x() - 1, end.get_y()); // i.e. (1, y)
			}
			else return false;
		}
	}
	else return false;
}

void King::setFirstMove(){
	/*
	Turns the boolean attribute 'firstMove' into 'true'.
	*/
	firstMove = false;
}

void King::resetFirstMove(){
	/*
	Reset the boolean attribute 'firstMove' to 'false'.
	*/
	firstMove = true;
}

bool King::getFirstMove() const{
	/*
	Getter method to 'firstMove' attribute.
	*/
	return firstMove;
}
