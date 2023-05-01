#ifndef _Queen_hpp_
#define _Queen_hpp_

# include "Rook.hpp"
# include "Bishop.hpp"

using namespace std;

//class Plateau;

class Queen : public Bishop, public Rook{

	public:
	Queen(bool isBlack);
	bool isValidMove(const Position &start, const Position &end, const Board* board) const;

};

#endif
