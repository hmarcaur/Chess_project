#ifndef _DraughtsQueen_hpp_
#define _DraughtsQueen_hpp_

# include "Piece.hpp"

using namespace std;

class DraughtsQueen : public Piece{

	public:
	DraughtsQueen(bool isBlack);
	bool isValidMove(const Position &start, const Position &end, const Board* board) const;
	Position isValidCatch(const Position &start, const Position &end, const Board* board, const Position &initialPosition) const;
	unordered_set<Position, PositionHash> getValidMoves(const Position &start, Board* board) const;
	bool isValidTrip(const Position &start, const Position &end, const Board* board) const;
};

#endif
