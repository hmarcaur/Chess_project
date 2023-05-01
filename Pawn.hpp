#ifndef _Pawn_hpp_
#define _Pawn_hpp_

# include "Piece.hpp"

using namespace std;

class Pawn : public Piece{
	private:
	bool firstMove;

	public:
	Pawn(bool isBlack);
	bool isValidMove(const Position &start, const Position &end, const Board* board) const;
	void setFirstMove();
	void resetFirstMove();
	bool getFirstMove() const;

};

#endif
