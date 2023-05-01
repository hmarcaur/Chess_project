#ifndef _Position_hpp_
#define _Position_hpp_

# include <iostream>
# include <string>
# include <cmath>

using namespace std;

class Position{

	private:
	// Attributes
	int x;
	int y;

	public:
	// Methods
	Position(int x, int y);
	Position(const Position &p, int dx, int dy);
	Position(string str);
	string toString() const;
	int get_x() const;
	int get_y() const;
	int get_distX(const Position &pos) const;
	int get_distY(const Position &pos) const;
	bool operator==(const Position &p) const;
	bool operator!=(const Position &p) const;
	bool sameDiagonal(const Position &pos) const;

};

// Class to produce the associated 'hash' that we will use (in unordered_set).
class PositionHash{
  public:
  size_t operator() (const Position &pos) const
  {
		size_t xHash = std::hash<int>()(pos.get_x());
    size_t yHash = std::hash<int>()(pos.get_y());
    return xHash ^ yHash;
  }
};

#endif
