#ifndef _Piece_hpp_
#define _Piece_hpp_

# include "Board.hpp"

using namespace std;

class Piece{

	private:
	string name;
	bool isBlack;

	public:
	Piece(bool isBlack, string name);
	string toString() const;
	bool getIsBlack() const;
	unordered_set<Position, PositionHash> getValidMoves(const Position &start, Board* board) const;
	virtual void setFirstMove();
	virtual void resetFirstMove();
	virtual bool getFirstMove() const;
	virtual bool isValidMove(const Position &start, const Position &end, const Board* board) const = 0;
	virtual Position isValidCatch(const Position &start, const Position &end, const Board* board, const Position &initialPosition) const;
	virtual bool isValidTrip(const Position &start, const Position &end, const Board* board) const;
	virtual ~Piece();

};

#endif
