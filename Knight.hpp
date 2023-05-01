#ifndef _Knight_hpp_
#define _Knight_hpp_

# include "Piece.hpp"

using namespace std;

class Knight : public Piece{

	public:
	Knight(bool isBlack);
	bool isValidMove(const Position &start, const Position &end, const Board* board) const;

};

#endif
