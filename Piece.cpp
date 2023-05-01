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

unordered_set<Position, PositionHash> Piece::getValidMoves(const Position &start, const Board* board) const{
	/*
	Method to get all the valid movements of a piece.
	*/
	unordered_set<Position, PositionHash> positions = board->getPossiblePositions(start);
	unordered_set<Position, PositionHash> possibleMoves;
	for(auto it = positions.begin(); it != positions.end(); it++){
		if(isValidMove(start, *it, board)) possibleMoves.insert(*it);
	}
	return possibleMoves;
	return positions;
}

Piece::~Piece(){
	/*
	Class destructor 'Piece'.
	*/
}
