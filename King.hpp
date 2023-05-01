#ifndef _King_hpp_
#define _King_hpp_

# include "Piece.hpp"

using namespace std;

class King : public Piece{

	private:
	bool firstMove;

	public:
	King(bool isBlack);
	bool isValidMove(const Position &start, const Position &end, const Board* board) const;
	void setFirstMove();
	void resetFirstMove();
	bool getFirstMove() const;

};

#endif
