#ifndef _Chessboard_hpp_
#define _Chessboard_hpp_

# include "Utils.hpp"
# include "Board.hpp"
# include "Pawn.hpp"
# include "Queen.hpp"
# include "Bishop.hpp"
# include "Knight.hpp"
# include "Rook.hpp"
# include "King.hpp"

# include <queue>

using namespace std;

class Chessboard : public Board{

	protected:
	Position posBlackKing;
	Position posWhiteKing;
	bool blackKingisChecking;
	bool whiteKingisChecking;

	public:
	Chessboard();
	void initialConditions();
	bool getKingIsChecking(bool isBlack) const;
	void update();
	string toString() const;
	bool checksKing() const;
	bool checksOpponentKing() const;
	bool checkTie() const;
	void endOfGame();
	void cancelLastMove(bool firstMove, bool wasEmpty, const string &promotion);
	void makeMove(const Position &start, const Position &end, const string &promotion);
	void specificMove(const Position &start, const Position &end, const string &promotion);
	void message(bool blackPlay) const;
	unordered_set<Position, PositionHash> getPossiblePositions(const Position &start) const;
	vector<movement> getAllValidMoves(bool isBlack);
	void findBestMoves(bool isBlack);
};

#endif
