#ifndef _Draughtsboard_hpp_
#define _Draughtsboard_hpp_

# include "Utils.hpp"
# include "Board.hpp"
# include "DraughtsPawn.hpp"
# include "DraughtsQueen.hpp"

# include <algorithm>
# include <map>
# include <queue>

using namespace std;

class Draughtsboard : public Board{

	private:
	bool newQueen;
	vector<vector<Position>> positionPieceToRemove;
	int nbInitialPieces;
	vector<Position> positionToClear;

	public:
	Draughtsboard();
	void initialConditions();
	string toString() const;
	void endOfGame();
	void makeMove(const Position &start, const Position &end, const string &promotion);
	void specificMove(const Position &start, const Position &end, const string &promotion);
	void message(bool blackPlay) const;
	vector<movement> getAllValidMoves(bool isBlack);
	void findBestMoves(bool isBlack);
	unordered_set<Position, PositionHash> getPossiblePositions(const Position &start) const;
	void recursiveSearch(const Position &start, const Position &initialPosition, vector<movement> currentMoves, vector<Position> currentPositionPieceToRemove);
};

#endif
