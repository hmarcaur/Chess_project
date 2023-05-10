#ifndef _Game_hpp_
#define _Game_hpp_

# include <sstream>
# include <fstream>

# include "Utils.hpp"
# include "Chessboard.hpp"
# include "Draughtsboard.hpp"

using namespace std;

class Game{

  private:
  string fileName;
  string gameName;
  string name;
  bool endOfGame;
  vector<movement> movements;
  vector<string> promotions;

	public:
  Board* board;
  Game();
	Game(const string &file);
  Game(Board *board);
  string getFileName() const;
  void setFileName(string const &filename);
  vector<movement> getMovements() const;
  vector<string> getPromotions() const;
  void readFile();
  void playFile();
  void play(bool reset = false);
};

#endif
