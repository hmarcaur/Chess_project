#ifndef _Bishop_hpp_
#define _Bishop_hpp_

# include "Piece.hpp"

using namespace std;

class Bishop : public virtual Piece{

	public:
	Bishop(bool isBlack);
	bool isValidMove(const Position &start, const Position &end, const Board* board) const;

};

#endif
