#include "Piece.hpp"

Piece::Piece(bool isBlackPiece, string name): isBlack(isBlackPiece), name(name){
	/*
	Class constructor 'Piece'.
	*/
}

string Piece::toString() const{
	/*
	Method to convert 'Piece' object into 'string'.
	*/
	if(isBlack){
		char c = name[0];
		c = toupper(c);
		string s;
		s = c;
		return s + name[1];
	}
	else return name.substr(0,2);
}

bool Piece::getIsBlack() const{
	/*
	Getter method to 'isBlack' attribute.
	*/
	return isBlack;
}

void Piece::setFirstMove(){
	/*
	Turns the boolean attribute 'firstMove' into 'true'.
	*/
}

void Piece::resetFirstMove(){
	/*
	Reset the boolean attribute 'firstMove' to 'false'.
	*/
}

bool Piece::getFirstMove() const{
	/*
	Getter method to 'firstMove' attribute.
	*/
	return false;
}

unordered_set<Position, PositionHash> Piece::getValidMoves(const Position &start, Board* board) const{
	/*
	Method to get all the valid movements of a piece from 'start'.
	*/
	unordered_set<Position, PositionHash> positions = board->getPossiblePositions(start);
	unordered_set<Position, PositionHash> possibleMoves;
	for(auto it = positions.begin(); it != positions.end(); it++){
		if(isValidMove(start, *it, board)) possibleMoves.insert(*it);
	}
	return possibleMoves;
}

Position Piece::isValidCatch(const Position &start, const Position &end, const Board* board, const Position &initialPosition) const{
	/*
	Returns the 'Position' of the 'Piece' to catch if it is valid, 'Position(-1, -1)' otherwise.
	*/
	return Position(-1, -1);
}

bool Piece::isValidTrip(const Position &start, const Position &end, const Board* board) const{
	/*
	Returns 'true' if the 'Piece' in position 'start' can move to 'end' without catching or encountering any piece.
	*/
	return false;
}

Piece::~Piece(){
	/*
	Class destructor 'Piece'.
	*/
}
