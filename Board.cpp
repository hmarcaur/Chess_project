# include "Board.hpp"
# include "Piece.hpp"

Board::Board(int h, int w): height(h), width(w), lastMove{Position(-1, -1), Position(-1, -1)}{
	/*
	Class constructor 'Board'.
	*/
	board = new Piece * [height * width];
}

void Board::add(Piece *pi, const Position &pos){
	/*
	Method to add a 'Piece' on the 'Board'.
	*/
	if(pos.get_y() >= height || pos.get_x() >= width) throw string("The position has coordinates outside the board.");
	board[height * pos.get_y() + pos.get_x()] = pi;
}

void Board::move(const Position &start, const Position &end, string promotion){
	/*
	Method to move a 'Piece' on the 'Board'.
	*/
	Piece *ptr = nullptr;
	specificMove(start, end, promotion);
	board[height * start.get_y() + start.get_x()] = ptr;

	lastMove.start = start;
	lastMove.end = end;

}

int Board::getHeight() const{
	/*
	Getter method to 'height' attribute.
	*/
	return height;
}

int Board::getWidth() const{
	/*
	Getter method to 'width' attribute.
	*/
	return width;
}

bool Board::isInside(const Position &pos) const{
	/*
	Returns 'true' if the 'Position' is inside the 'Board'.
	*/
	return pos.get_y() < height && pos.get_x() < width;
}

Piece* Board::getPiece(const Position &pos) const{
	if(pos.get_y() >= height || pos.get_x() >= width) throw string("The position has coordinates outside the board.");
	if(emptySquare(pos.get_x(), pos.get_y())) throw string("The square is empty.");
	return board[height * pos.get_y() + pos.get_x()];
}

void Board::play(const Position &start, const Position &end, bool blackPlay, string promotion){
	/*
	Method to play a 'movement' on the 'Board'. The 'movement' is playing only if it is allowed (i.e. after passing all controls).
	*/
	if(isInside(start)) throw string("Starting coordinate outside the board.");
	if(isInside(end)) throw string("Arrival coordinate outside the board.");
	if(emptySquare(start.get_x(), start.get_y())) throw string("The square is empty.");
	if(getPiece(start)->getIsBlack() != blackPlay) throw string("The starting square is occupied by a piece of the other color.");
	if(board[height * end.get_y() + end.get_x()]->getIsBlack() == blackPlay) throw string("The arrival square is occupied by a piece of the same color.");
	if(start.get_x() == end.get_x() && start.get_y() == end.get_y()) throw string("The arrival square is identical to the starting square.");
	if(!getPiece(start)->isValidMove(start, end, this)) throw string("Invalid movement. Please propose another movement.");
	movement previousMove = lastMove;
	bool firstMove = getPiece(start)->getFirstMove();
	bool wasEmpty = emptySquare(end.get_x(), end.get_y());
	move(start, end, promotion);
	if(!checksKing()){ // The movement is allowed.
		update();
		endOfGame(promotion);
	}
	else{ // The movement is not allowed (i.e. it checks his own king).
		cancelLastMove(firstMove, wasEmpty, promotion);
		lastMove = previousMove;
		throw string("The movement is forbidden as your king is checking after it. Please propose another movement.");
	}
}

bool Board::emptySquare(int x, int y) const{
	/*
	Returns true is the square (x, y) is empty.
	*/
	return(!board[height * y + x]); // ptr NULL
}

movement Board::getLastMove() const{
	/*
	Getter method to 'lastMove' attribute.
	*/
	return lastMove;
}

void Board::setLastMove(const movement &move){
	/*
	Setter method to 'lastMove' attribute.
	*/
	lastMove = move;
}

Position Board::getPosition(int i) const{
	/*
	Method to get the position associated with an index of the board.
	*/
	return Position(i % height, i / height);
}

unordered_set<Position, PositionHash> Board::getPiecePosition(string pieceName, bool isBlack) const{
	/*
	Method to get position(s) of piece(s) on the 'Board'.
	*/
	unordered_set<Position, PositionHash> positions;
	if(pieceName == "all"){ // All the pieces black or white
		for(int i = 0; i < getHeight() * getWidth(); i++){
			if(!emptySquare(i % height, i / height)){
				if(board[i]->getIsBlack() == isBlack) positions.insert(getPosition(i));
			}
		}
	}
	else{ // Only 'pieceName' pieces black or white
		char c = pieceName[0];
		string s;
		c = isBlack ? toupper(c) : tolower(c);
		s = c;
		pieceName = s + pieceName[1];
		for(int i = 0; i < getHeight() * getWidth(); i++){
			if(!emptySquare(i % height, i / height)){
				if(board[i]->toString() == pieceName) positions.insert(getPosition(i));
			}
		}
	}
	return positions;
}

unordered_set<Position, PositionHash> Board::getPossiblePositions(const Position& start) const{
	/*
	Method to get all the positions potentially available from start.
	(i.e. occupied by a 'Piece' of the other color or empties)
	*/
	bool isBlack = getPiece(start)->getIsBlack();
	unordered_set<Position, PositionHash> possiblePositions;
	for(int i = 0; i < getHeight() * getWidth(); i++){
		if(!emptySquare(i % height, i / height)) possiblePositions.insert(getPosition(i));
		else if(getPiece(getPosition(i))->getIsBlack() != isBlack) possiblePositions.insert(getPosition(i));
	}
	return possiblePositions;
}
