# include "DraughtsPawn.hpp"

DraughtsPawn::DraughtsPawn(bool isBlack): Piece(isBlack, "pawn"){
	/*
	Class constructor 'DraughtsPawn'.
	*/
}

bool DraughtsPawn::isValidMove(const Position &start, const Position &end, const Board* board) const{
	/*
	Returns 'true' if the move is valid (i.e. it does not exist a better one).
	*/
	vector<vector<movement>> bestMoves = board->getBestMoves(getIsBlack());
	for(int i = 0; i < bestMoves.size(); i ++){
		if(bestMoves[i].front().start == start && bestMoves[i].back().end == end) return true;
	}
  return false; // The proposed move is not among the best
}

Position DraughtsPawn::isValidCatch(const Position &start, const Position &end, const Board* board, const Position &initialPosition) const{
	/*
	Returns the 'Position' of the 'Piece' to catch if it is valid (i.e. one 'Piece' to catch
  between 'start' and 'end'), 'Position(-1, -1)' otherwise.
	*/
  Position posPiece = Position(-1, -1);
  int dy = start.get_distY(end);
	if(dy == 2 && dy == start.get_distX(end)){ // Same diagonal and move to two squares
    int x;
		int y;
		for(int d = 1; d < dy; d++){
			x = start.get_x() < end.get_x() ? start.get_x() + d : start.get_x() - d; // width movement
			y = start.get_y() < end.get_y() ? start.get_y() + d : start.get_y() - d; // height movement
			// Non-empty square
			if(!board->emptySquare(x, y)){
				// Occupied by a piece of the other colour
				if(Position(x, y) == initialPosition); // pass (It is allowed to go back to the 'initialPosition')
				else if(board->getPiece(Position(x, y))->getIsBlack() != getIsBlack()){
					if(posPiece.get_x() != -1) return Position(-1, -1); // More than one piece between 'start' and 'end'
					else posPiece = Position(x, y); // First piece encountered, i.e. we update the finded piece.
				}
	      // Occupied by a piece of the same colour
				else return Position(-1, -1);
			}
			else; // pass
		}
		return posPiece;
	}
	return posPiece;
}

bool DraughtsPawn::isValidTrip(const Position &start, const Position &end, const Board* board) const{
	/*
	Returns 'true' if the 'DraughtsPawn' in position 'start' can move to 'end' without catching or encountering any piece.
	*/
	// Only move forward
	if(getIsBlack()){ // Black
		if(end.get_y() >= start.get_y()) return false;
	}
	else{ // White
		if(start.get_y() >= end.get_y()) return false;
	}
  int dy = start.get_distY(end);
	if(dy == 1 && dy == start.get_distX(end)){ // Same diagonal
    int x;
		int y;
		for(int d = 1; d < dy; d++){
			x = start.get_x() < end.get_x() ? start.get_x() + d : start.get_x() - d; // width movement
			y = start.get_y() < end.get_y() ? start.get_y() + d : start.get_y() - d; // height movement
			// Non-empty square
			if(!board->emptySquare(x, y)) return false;
    }
    return true; // No pieces betwwen
  }
  return false; // Not on the same diagonal
}


unordered_set<Position, PositionHash> DraughtsPawn::getValidMoves(const Position &start, Board* board) const{
	/*
	Method to get all the valid movements of a 'DraughtsPawn' piece from 'start'.
	*/
	unordered_set<Position, PositionHash> possiblePositions;
  if(board->getBestMoves(getIsBlack()).size() == 0){ // First time
    // We must computing the bestMoves
    board->findBestMoves(getIsBlack());
  }

	for(auto it = board->getBestMoves(getIsBlack()).begin(); it != board->getBestMoves(getIsBlack()).end(); it++){
    if(it->front().start == start) possiblePositions.insert(it->end()->end);
    else; // pass
  }
  return possiblePositions;
}
