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
	Board(int height, int width);
	void add(Piece *pi, const Position &pos);
	void move(const Position &start, const Position &end, string promotion);

	public:
	int getHeight() const;
	int getWidth() const;
	bool isInside(const Position &pos) const;
	Piece* getPiece(const Position &pos) const;
	void play(const Position &start, const Position &end, bool blackPlay, string promotion = "");
	bool emptySquare(int x, int y) const;
	movement getLastMove() const;
	void setLastMove(const movement &move);
	Position getPosition(int i) const;
	unordered_set<Position, PositionHash> getPiecePosition(string pieceName, bool isBlack) const;
	unordered_set<Position, PositionHash> getPossiblePositions(const Position &start) const;
	virtual void initialConditions() = 0;
	virtual void update() = 0;
	virtual bool checksKing() const = 0;
	virtual void endOfGame(string promotion) = 0;
	virtual void cancelLastMove(bool firstMove, bool wasEmpty, string promotion) = 0;
	virtual void specificMove(const Position &start, const Position &end, string promotion) = 0;

};

#endif
