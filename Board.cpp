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
	if(pos.get_y() >= height || pos.get_x() >= width) throw Exception(4, "The position has coordinates outside the board.", 1);
	board[height * pos.get_y() + pos.get_x()] = pi;
}

void Board::clear(const Position &pos){
	/*
	Method to remove piece on the square in position 'pos'.
	*/
	Piece *ptr = nullptr;
	if(!emptySquare(pos.get_x(), pos.get_y())){
		board[height * pos.get_y() + pos.get_x()] = ptr;
	}
}

void Board::resetLastMove(){
	/*
	Method to reset the 'lastMove' attribute (i.e. with positions out of the board).
	*/
	movement move = {Position(-1, -1), Position(-1, -1)};
	lastMove = move;
}

void Board::move(const Position &start, const Position &end, const string &promotion){
	/*
	Method to move a 'Piece' on the 'Board'.
	*/
	makeMove(start, end, promotion);

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
	if(pos.get_y() >= height || pos.get_x() >= width) throw Exception(4, "The position has coordinates outside the board.", 1);
	if(emptySquare(pos.get_x(), pos.get_y())) throw Exception(5, "The square is empty.", 1);
	return board[height * pos.get_y() + pos.get_x()];
}

void Board::play(const Position &start, const Position &end, bool blackPlay, const string &promotion){
	/*
	Method to play a 'movement' on the 'Board'. The 'movement' is playing only if it is allowed (i.e. after passing all controls).
	*/
	if(!isInside(start)) throw Exception(6, "Starting coordinate outside the board.", 1);
	if(!isInside(end)) throw Exception(7, "Arrival coordinate outside the board.", 1);
	if(emptySquare(start.get_x(), start.get_y())) throw Exception(8, "The sarting square is empty.", 1);
	if(getPiece(start)->getIsBlack() != blackPlay) throw Exception(9, "The starting square is occupied by a piece of the other colour.", 1);
	// If the arrival square is not empty, we check whether it is not occupied by a piece of the same colour.
	if(!emptySquare(end.get_x(), end.get_y())) if(board[height * end.get_y() + end.get_x()]->getIsBlack() == blackPlay) \
	throw Exception(10, "The arrival square is occupied by a piece of the same colour.", 1);
	specificMove(start, end, promotion);
}

bool Board::emptySquare(int x, int y) const{
	/*
	Returns true is the square (x, y) is empty.
	*/
	return(!board[height * y + x]); // ptr NULL
}

vector<vector<movement>> Board::getBestMoves(bool isBlack) const{
	/*
	Getter method to 'bestMoves' attribute of color 'isBlack'.
	*/
	return isBlack ? bestBlackMoves : bestWhiteMoves;
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

vector<Piece*> Board::getCaptured() const{
	/*
	Getter method to 'captured' attribute (i.e. all the captured pieces).
	*/
	return captured;
}

vector<Piece*> Board::getCaptured(bool isBlack) const{
	/*
 	Method to get all the captured pieces of one color.
	*/
	vector<Piece*> capturedPieces;
	for(auto it = captured.begin(); it != captured.end(); it++){
		if((*it)->getIsBlack() == isBlack) capturedPieces.push_back(*it);
	}
	return capturedPieces;
}

unordered_set<Position, PositionHash> Board::getPiecePosition(const string &pieceName, bool isBlack) const{
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
		s = c + pieceName[1];
		for(int i = 0; i < getHeight() * getWidth(); i++){
			if(!emptySquare(i % height, i / height)){
				if(board[i]->toString() == s) positions.insert(getPosition(i));
			}
		}
	}
	return positions;
}

Board::~Board(){
	/*
	Class destructor 'Board'.
	*/
	for(int i = 0; i < getHeight() * getWidth(); i++){
    delete board[i];
  }
}
