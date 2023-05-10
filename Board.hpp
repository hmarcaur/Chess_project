#ifndef _Board_hpp_
#define _Board_hpp_

# include "Position.hpp"

# include <vector>
# include <array>
# include <unordered_set>

using namespace std;

struct movement{
	Position start;
	Position end;
};

class Piece;

class Board{

	private:
	int height;
	int width;
	movement lastMove;

	protected:
	Piece* *board;
	vector<Piece*> captured;
	// List of best moves make from single moves
	vector<vector<movement>> bestBlackMoves;
	vector<vector<movement>> bestWhiteMoves;
	Board(int height, int width);
	void add(Piece *pi, const Position &pos);
	void move(const Position &start, const Position &end, const string &promotion);
	void clear(const Position &pos);

	public:
	int getHeight() const;
	int getWidth() const;
	bool isInside(const Position &pos) const;
	Piece* getPiece(const Position &pos) const;
	void play(const Position &start, const Position &end, bool blackPlay, const string &promotion = "X");
	bool emptySquare(int x, int y) const;
	movement getLastMove() const;
	void setLastMove(const movement &move);
	void resetLastMove();
	Position getPosition(int i) const;
	vector<vector<movement>> getBestMoves(bool isBlack) const;
	vector<Piece*> getCaptured() const;
	vector<Piece*> getCaptured(bool isBlack) const;
	unordered_set<Position, PositionHash> getPiecePosition(const string &pieceName, bool isBlack) const;
	virtual string toString() const = 0;
	virtual void initialConditions() = 0;
	virtual void makeMove(const Position &start, const Position &end, const string &promotion) = 0;
	virtual void specificMove(const Position &start, const Position &end, const string &promotion) = 0;
	virtual void message(bool blackPlay) const = 0;
	virtual unordered_set<Position, PositionHash> getPossiblePositions(const Position &start) const = 0;
	virtual vector<movement> getAllValidMoves(bool isBlack) = 0;
	virtual void findBestMoves(bool isBlack) = 0;
	virtual ~Board();
};

#endif
