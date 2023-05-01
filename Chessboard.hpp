#ifndef _Chessboard_hpp_
#define _Chessboard_hpp_

# include "Board.hpp"
# include "Pawn.hpp"
# include "Queen.hpp"
# include "Bishop.hpp"
# include "Knight.hpp"
# include "Rook.hpp"
# include "King.hpp"

using namespace std;

class Chessboard : protected Board{

	protected:
	Position posBlackKing;
	Position posWhiteKing;
	bool blackKingisChecking;
	bool whiteKingisChecking;

	public:
	Chessboard();
	void initialConditions();
	void update();
	string toString() const;
	bool checksKing() const;
	bool checksOpponentKing() const;
	void endOfGame(string promotion);
	void cancelLastMove(bool firstMove, bool wasEmpty, string promotion);
	void specificMove(const Position &start, const Position &end, string promotion);
};

#endif
