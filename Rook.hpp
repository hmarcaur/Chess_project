#ifndef _Rook_hpp_
#define _Rook_hpp_

# include "Piece.hpp"

using namespace std;

class Rook : public virtual Piece{

	private:
	bool firstMove;

	public:
	Rook(bool isBlack);
	bool isValidMove(const Position &start, const Position &end, const Board* board) const;
	void setFirstMove();
	void resetFirstMove();
	bool getFirstMove() const;

};

#endif
