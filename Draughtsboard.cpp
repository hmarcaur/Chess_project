# include "Draughtsboard.hpp"

Draughtsboard::Draughtsboard(): Board(10, 10), newQueen(false){
	/*
	Class constructor 'Draughtsboard'
	*/
}

void Draughtsboard::initialConditions(){
	/*
	Method to initialize the 'Draughtsboard' in standard configuration.
	*/
  bool whiteSquareFirst = false;
  int startingSquare;
  nbInitialPieces = 0;
  for(int j = 0; j < getHeight(); j++){
    startingSquare = whiteSquareFirst ? 1 : 0;
    for(int i = startingSquare; i < getWidth(); i+=2){
      bool c = j > 3;
      if(j <= 3 || j >= 6){
        add(new DraughtsPawn(c), Position(i, j));
        nbInitialPieces += 1;
      }
      else clear(Position(i, j));
    }
    for(int i2 = 1 - startingSquare; i2 < getWidth(); i2+=2) clear(Position(i2, j));
    whiteSquareFirst = !whiteSquareFirst;
  }
  captured.clear();
	resetLastMove();
}

string Draughtsboard::toString() const{
	/*
	Method to convert 'Draughtsboard' object into 'string'.
	*/
	map<string, string> codePieces; // Unicode for draughts pieces.
	codePieces["Pa"] = "\u25EF";
	codePieces["pa"] = "\u2B24";
  codePieces["Qu"] = "\u29BE";
	codePieces["qu"] = "\u29BF";

	vector<Piece*> blackCaptured = getCaptured(true);
	vector<Piece*> whiteCaptured = getCaptured(false);

	queue<string> blackPiecesCaptured;
	int nbBlackCaptured = 0;
	for(auto it = blackCaptured.begin(); it != blackCaptured.end(); it++){
		blackPiecesCaptured.push(codePieces[(*it)->toString()]);
		nbBlackCaptured += 1;
	}
	string totalBlackPiecesCaptured = "            Total : " + to_string(nbBlackCaptured) + ".";

 	queue<string> whitePiecesCaptured;
	int nbWhiteCaptured = 0;
	for(auto it = whiteCaptured.begin(); it != whiteCaptured.end(); it++){
		whitePiecesCaptured.push(codePieces[(*it)->toString()]);
		nbWhiteCaptured += 1;
	}
	string totalWhitePiecesCaptured =  "            Total : " + to_string(nbWhiteCaptured) + ".";

  string whiteSquare = "\u2588\u2588\u2588\u2588\u2588";
	string blackSquare = "     ";

	string lineWhiteSquareBegin;
	string lineBlackSquareBegin;

	bool beginWhite = true;
	for(int i = 0; i < getWidth(); i++){
		if(beginWhite){
			lineWhiteSquareBegin += whiteSquare;
			lineBlackSquareBegin += blackSquare;
		}
		else{
			lineWhiteSquareBegin += blackSquare;
			lineBlackSquareBegin += whiteSquare;
		}
		beginWhite = !beginWhite;
	}

	beginWhite = true; // Reset beginWhite
	string line = lineWhiteSquareBegin;

	string titleWhitePieces = "      \u25A0 White pieces captured      ";
	string titleBlackPieces = "      \u25A1 Black pieces captured      ";

	string s; // Entire line (of a square)
	string square; // Entire line (of a square) without piece

	string letterString; // Turn character into string

	string block1, block2; // Parts of the square between its border and a piece

	int n = getHeight(); // Number of the square

	string space; // Space between the left border and the number
	string thirdOfSpace; // Space between the left border and the first captured piece
	for(int i = 0; i < titleBlackPieces.size(); i++){
		space += " ";
		if(i > 3 && i % 3 == 0) thirdOfSpace += " ";
	}

  string spaceTotal; // Gap between the totals and the first outline
	for(int s = 0; s < (space.size() - totalWhitePiecesCaptured.size()); s ++) spaceTotal += " ";


	// First line : upper line with letters
	string res = space + "  " + "   " + "  "; // (Number + space) + outline space + 2 spaces of the first square
	for(int letter = 'A'; letter < 'K'; letter++){
		letterString = letter;
		res += letterString + "    "; // Space betwwen two letter
	}
	res += "\n";

	// Second line : Upper part of the thin outline
	res += space + "  " + "\u250C\u2500\u2500"; // (Number + space)
	for(int i = 0; i < getWidth(); i++) res += "\u2500\u2500\u2500\u2500\u2500";
	res += "\u2500\u2500\u2510";
	res += "\n";

	// Third line : Upper part of the wide white outline arround the board
	res += titleWhitePieces + "    " + "\u2502 \u2584"; // First line (captured pieces) (Number + space)
	for(int i = 0; i < getWidth(); i++) res += "\u2584\u2584\u2584\u2584\u2584";
	res += "\u2584 \u2502  " + titleBlackPieces;
	res += "\n";

	// The board
	for(int j = getHeight() * getWidth() - 1 - 9; j > -1 ; j -= 10){ // Browsing of the lines from the upper part
		line = beginWhite ? lineWhiteSquareBegin : lineBlackSquareBegin; // Upper and lower line of the squares whitout pieces

		// First line of the square
		res += space;
		res += "  \u2502 \u2588" + line + "\u2588 \u2502" + "  ";
		res += "\n";
		// Second line of the square
		res += thirdOfSpace;
		if(!whitePiecesCaptured.empty()){ // At least one more white piece inside
			res += whitePiecesCaptured.front();
			whitePiecesCaptured.pop();
			res += thirdOfSpace + " ";
			if(!whitePiecesCaptured.empty()){ // Two more white pieces inside
				res += whitePiecesCaptured.front();
				whitePiecesCaptured.pop();
			}
			else res += " "; // Only one white piece inside
		}
		else res += " " + thirdOfSpace + " " + " "; // No more white pieces inside
		res += thirdOfSpace;
    if(n < 10) res += to_string(n) + "  \u2502 \u2588";
		else res += to_string(n) + " \u2502 \u2588";
		// Part with eventually the pieces
		for(int i = j; i <= j + 9; i++){
			square = beginWhite ? whiteSquare : blackSquare; // Line of an empty square
			block1 = beginWhite ? "\u2588\u2588" : "  "; // Two first characters for the line of a square with a piece
      block2 = beginWhite ? "\u2588\u2588" : "  "; // Last character for the line of a square with a piece
			if(!emptySquare(i % getHeight(), i / getHeight())) res += block1 + codePieces[board[i]->toString()] + block2; // Busy square
			else res += square; // Empty square
			beginWhite = !beginWhite;
		}
		res += "\u2588 \u2502 " + to_string(n);
    if(n < 10) res += " ";
		res += thirdOfSpace;
		if(!blackPiecesCaptured.empty()){ // At least one more black piece inside
      res += blackPiecesCaptured.front();
			blackPiecesCaptured.pop();
			res += thirdOfSpace + " ";
			if(!blackPiecesCaptured.empty()){ // Two more black pieces inside
				res += blackPiecesCaptured.front();
				blackPiecesCaptured.pop();
			}
			else res += " "; // Only one black piece inside
		}
		else res += " " + thirdOfSpace + " " + " "; // No more black pieces inside
		res += " \n";
		// Third line of the square
		// Second line (captured pieces)
		res += space;
		res += "  \u2502 \u2588" + line + "\u2588 \u2502";
		res += "\n";

		n -= 1;
		beginWhite = !beginWhite;
	}

	// Lower wide white outline arround the board (-3)
	res += totalWhitePiecesCaptured + spaceTotal + "  " + "\u2502 \u2580"; // Third line (captured pieces), (Number + space)
	for(int i = 0; i < getWidth(); i++) res += "\u2580\u2580\u2580\u2580\u2580";
	res += "\u2580 \u2502  " + totalBlackPiecesCaptured;
	res += "\n";

	// Lower thin outline (-2)
	res += space + "  " + "\u2514\u2500\u2500"; // (Number + space)
	for(int i = 0; i < getWidth(); i++) res += "\u2500\u2500\u2500\u2500\u2500";
	res += "\u2500\u2500\u2518";
	res += "\n";

	// Lower line with letters (-1)
	res += space + "  " + "   " + "  "; // (Number + space) + outline space + 2 spaces of the first square
	for(int letter = 'A'; letter < 'K'; letter++){
		letterString = letter;
		res += letterString + "    "; // Space betwwen two letter
	}

	return "\n" + space + "  " + "   " + "      " + "      " + "Draughtsboard " \
	+ to_string(getHeight()) + " x " + to_string(getWidth()) + ":" + "\n\n" + res + "\n";
}

void Draughtsboard::endOfGame(){
	/*
	Method to verify if that is the end of the game. Throws exception if that is.
  i.e. After that move, the opponent has no more pieces or he can not move any piece.
	*/
  bool isBlack = getPiece(getLastMove().end)->getIsBlack();
  string color = isBlack ? "blacks" : "whites";
  string opponentColor = !isBlack ? "blacks" : "whites";
  findBestMoves(!isBlack);
  // No more pieces
  if(getCaptured(!isBlack).size() == nbInitialPieces) \
  throw Exception(26, "The game ends as the " + opponentColor + " have no more pieces. The " + color + " won.", 3);
  // There are no more valid moves.
  else if(getBestMoves(!isBlack).size() == 0) throw Exception(27, "The game ends as the " + opponentColor + " have no more valid move. The " + color + " won.", 3);
  // There is at least one valid move
  else return;
}

void Draughtsboard::specificMove(const Position &start, const Position &end, const string &promotion){
	/*
	Method that makes the current 'movement'. Checks if that is a promotion
  to activate/descativate the associated attribute 'newQueen'.
	*/
  bool isBlack = getPiece(start)->getIsBlack();
  if(!emptySquare(end.get_x(), end.get_y())) throw Exception(10, "The arrival square is occupied by a piece of the other colour.", 3);

  // First time, otherwise it has already been computed in 'endOfGame' method.
  if(getBestMoves(isBlack).size() == 0) findBestMoves(isBlack);

  // Check the validity of the movement
  if(!getPiece(start)->isValidMove(start, end, this)) throw Exception(12, "Invalid movement.", 1);

  // Check if there are different ways for this move
  vector<vector<movement>> possibleMoves;
  vector<vector<Position>> possiblePositionToClear;
  int index = 0;
  vector<vector<movement>> bestMoves = getBestMoves(isBlack);

  // The move could not be unique
  if(positionPieceToRemove.size() >= 1){
    for(int i = 0; i < bestMoves.size(); i++){
  		if(bestMoves[i].front().start == start && bestMoves[i].back().end == end){
        possibleMoves.push_back(bestMoves[i]);
        possiblePositionToClear.push_back(positionPieceToRemove[i]);
      }
      index += 1;
    }
    vector<movement> moves; // Single moves associated with the current movement
    if(possibleMoves.size() > 1){ // 2 or more
      // Displaying the choices
      cout << "\n";
      int i;
      for(i = 0; i < possibleMoves.size(); i++){
        cout << "Move " << to_string(i + 1) << endl;
        for(int j = 0; j < possibleMoves[i].size(); j++){
          cout << "\t" << possibleMoves[i][j].start.toString() << " \u21D2 " << possibleMoves[i][j].end.toString() << endl;
        }
      }
      cout << "\n";
      // choose which one
      bool b = true;
      while(b){
        string m;
        cout << "Ambiguous move : please enter the [number] of the move you would want to make among those above : ";
        getline(cin, m);
        if(m == "quit") throw Exception(17, "'quit' command: Quit the platform.", 5);
        else if(m == "menu") throw Exception(18, "'menu' command: Go back to the main menu.", 5);
        else if(m == "back") throw Exception(19, "'back' command: Go back to the previous menu.", 5);
        else if(m == "commands" || m == "help" || m == "info") display(m);
        else{ // Try the given choice
          int ind = stoi(m); // Conversion to 'int'
          if(ind >= 1 && ind <= i){
            positionToClear = possiblePositionToClear[ind - 1];
            b = false;
          }
          // otherwise continue, i.e. ask for another argument.
        }
      }
    }
    else positionToClear = possiblePositionToClear[0]; // The first one, as it is the only one.
    positionPieceToRemove.clear(); // We empty the list of the position of the pieces to remove
  }
  else; // The move is bound to be unique (no pieces to remove)

  // Promotion if white goes to first row or black to last row
  string promo;
  if((end.get_y() == 0 && getPiece(start)->toString() == "Pa") \
  || (end.get_y() == getHeight() - 1 && getPiece(start)->toString() == "pa")) promo = "";
  else promo = "X";

  // Promotion (or not) imply to activate/descativate the 'newQueen' attribute
	newQueen = promo != "X";
	move(start, end, promo);
  endOfGame();
}

void Draughtsboard::makeMove(const Position &start, const Position &end, const string &promotion){
	/*
	Method to make a movement on the 'Draughtsboard'.
	*/
  bool isBlack = getPiece(start)->getIsBlack();

  add(getPiece(start), end);
  if(start != end) clear(start);

  if(promotion != "X"){
    // We replace the piece on the final square by a queen.
    add(new DraughtsQueen(isBlack), end);
  }
  for(auto it = positionToClear.begin(); it != positionToClear.end(); it ++){
    captured.push_back(getPiece(*it)); // We add the piece to the 'captured' list
    clear(*it); // We remove the piece on the board
  }
  positionToClear.clear(); // We remove all the position of the pieces in the list
}

void Draughtsboard::message(bool blackPlay) const{
	/*
	Method displaying specific message to 'Draughtsboard'.
	*/
  if(newQueen){
    string color = getPiece(getLastMove().end)->getIsBlack() ? "black" : "white";
    cout << "\t\t\t\t\t\t\t \u26A0 New " << color << " Queen !\n" << endl;
  }
}

vector<movement> Draughtsboard::getAllValidMoves(bool isBlack){
	/*
	Method to get all the valid movements on 'Draughtsboard' of player 'isBlack'.
	*/
  vector<movement> validMoves;
  // We must compte the 'bestMoves'
  if(getBestMoves(isBlack).size() == 0) findBestMoves(isBlack);
  vector<vector<movement>> bestMoves = getBestMoves(isBlack);
  for(int i = 0; i < bestMoves.size(); i++){
    movement m = {bestMoves[i].front().start, bestMoves[i].back().end};
    validMoves.push_back(m);
  }
  return validMoves;
}

void Draughtsboard::findBestMoves(bool isBlack){
  /*
  Method to find all the valid best moves on 'Draughtsboard' of player 'isBlack'.
  */
  // Position of the pieces of the current color.
  unordered_set<Position, PositionHash> posPieces = getPiecePosition("all", isBlack);

  // Empty squares
  unordered_set<Position, PositionHash> initialPossiblePositions = getPossiblePositions(*posPieces.begin()); // position of the first 'Piece' (i.e. here it does not matter)

  // Cleaning the list of the position of the 'Piece' to remove.
  positionPieceToRemove.clear();

  // Cleaning the list of the best moves
  if(isBlack) bestBlackMoves.clear(); // Blacks
  else bestWhiteMoves.clear(); // Whites

  // In-depth course
  for(auto it = posPieces.begin(); it != posPieces.end(); it ++){ // Browse of the pieces
    vector<movement> vm;
    vector<Position> vp;
    recursiveSearch(*it, *it, vm, vp); // Finding best catching moves recursively
  }

  if(positionPieceToRemove.empty()){ // No catch found
    // Does exist valid trips ?
    for(auto it = posPieces.begin(); it != posPieces.end(); it ++){
      for(auto it2 = initialPossiblePositions.begin(); it2 != initialPossiblePositions.end(); it2 ++){
        if(getPiece(*it)->isValidTrip(*it, *it2, this)){
          movement m = {*it, *it2};
          vector<movement> v = {m};
          if(isBlack) bestBlackMoves.push_back(v);
          else bestWhiteMoves.push_back(v);
        }
      }
    }
  }
}

void Draughtsboard::recursiveSearch(const Position &start, const Position &initialPosition, vector<movement> currentMoves, vector<Position> currentPositionPieceToRemove){
  /*
  Method to find recursively the best catching moves.
  */
  unordered_set<Position, PositionHash> possiblePositions = getPossiblePositions(initialPosition);
  for(auto it = possiblePositions.begin(); it != possiblePositions.end(); it++){
    Position p = getPiece(initialPosition)->isValidCatch(start, *it, this, initialPosition);
    if(p != Position(-1, -1) && count(currentPositionPieceToRemove.begin(), currentPositionPieceToRemove.end(), p) == 0){
      // We can add the position to the 'currentPositionPieceToRemove' and '*it' to 'currentMoves'
      currentPositionPieceToRemove.push_back(p);
      movement m = {start, *it};
      currentMoves.push_back(m);
      recursiveSearch(*it, initialPosition, currentMoves, currentPositionPieceToRemove);
      // Whatever we remove the last move and the last position of the piece to remove
      currentMoves.pop_back();
      currentPositionPieceToRemove.pop_back();
    }
  }

  bool isBlack = getPiece(initialPosition)->getIsBlack();
  if(isBlack){
    // First finded
    if(bestBlackMoves.empty() && currentMoves.size() > 0){
      bestBlackMoves.push_back(currentMoves);
      positionPieceToRemove.push_back(currentPositionPieceToRemove);
    }
    // Better than those found so far.
    else if(!bestBlackMoves.empty() && currentMoves.size() > bestBlackMoves.begin()->size()){
      bestBlackMoves.clear();
      bestBlackMoves.push_back(currentMoves);
      positionPieceToRemove.clear();
      positionPieceToRemove.push_back(currentPositionPieceToRemove);
    }
    // As good as those found so far
    else if(!bestBlackMoves.empty() && currentMoves.size() == bestBlackMoves.begin()->size()){
      bestBlackMoves.push_back(currentMoves);
      positionPieceToRemove.push_back(currentPositionPieceToRemove);
    }
    // Not as good as those found so far
    else; // pass
  }
  else{ // i.e. white
    // First finded
    if(bestWhiteMoves.empty() && currentMoves.size() > 0){
      bestWhiteMoves.push_back(currentMoves);
      positionPieceToRemove.push_back(currentPositionPieceToRemove);
    }
    // Better than those found so far.
    else if(!bestWhiteMoves.empty() && currentMoves.size() > bestWhiteMoves.begin()->size()){
      bestWhiteMoves.clear();
      bestWhiteMoves.push_back(currentMoves);
      positionPieceToRemove.clear();
      positionPieceToRemove.push_back(currentPositionPieceToRemove);
    }
    // As good as those found so far
    else if(!bestWhiteMoves.empty() && currentMoves.size() == bestWhiteMoves.begin()->size()){
      bestWhiteMoves.push_back(currentMoves);
      positionPieceToRemove.push_back(currentPositionPieceToRemove);
    }
    // Not as good as those found so far
    else; // pass
  }
}

unordered_set<Position, PositionHash> Draughtsboard::getPossiblePositions(const Position &start) const{
  /*
  Method to get all the positions that could be reached in a single move from
  position 'start', i.e. 'black' empty squares, as the white ones are never used.
  */
  unordered_set<Position, PositionHash> possiblePositions;
	for(int i = 0; i < getHeight() * getWidth(); i++){
    int x = i % getHeight();
    int y = i / getHeight();
    if(x % 2 == 0 && y % 2 == 1); // First half of the white squares, i.e. pass.
    else if(x % 2 == 1 && y % 2 == 0); // Second half of the white squares, i.e. pass.
		else{ // Black squares, i.e. on which we play.
      if(emptySquare(x, y)) possiblePositions.insert(getPosition(i));
    }
	}
	return possiblePositions;
}
