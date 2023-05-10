# include "Chessboard.hpp"
# include <map>

Chessboard::Chessboard(): Board(8, 8), posBlackKing(Position(-1, -1)), posWhiteKing(Position(-1, -1)), \
blackKingisChecking(false), whiteKingisChecking(false){
	/*
	Class constructor 'Chessboard'
	*/
}

void Chessboard::initialConditions(){
	/*
	Method to initialize the 'Chessboard' in standard configuration.
	*/
	add(new Rook(true), Position(0, 7));
	add(new Knight(true), Position(1, 7));
	add(new Bishop(true), Position(2, 7));
	add(new Queen(true), Position(3, 7));
	add(new King(true), Position(4, 7));
	add(new Bishop(true), Position(5, 7));
	add(new Knight(true), Position(6, 7));
	add(new Rook(true), Position(7, 7));

	add(new Rook(false), Position(0, 0));
	add(new Knight(false), Position(1, 0));
	add(new Bishop(false), Position(2, 0));
	add(new Queen(false), Position(3, 0));
	add(new King(false), Position(4, 0));
	add(new Bishop(false), Position(5, 0));
	add(new Knight(false), Position(6, 0));
	add(new Rook(false), Position(7, 0));

	for(int i = 0; i < getWidth(); i++){
		add(new Pawn(true), Position(i, 6));
		add(new Pawn(false), Position(i, 1));
		for(int j = 2; j < getWidth() - 2; j ++) clear(Position(i, j));
	}

	posBlackKing = Position(4, 7);
	posWhiteKing = Position(4, 0);
	blackKingisChecking = false;
	whiteKingisChecking = false;
	captured.clear();
	resetLastMove();
}

bool Chessboard::getKingIsChecking(bool isBlack) const{
	/*
	Method to get the 'boolean' attribute indicating if a king is currently checking.
	*/
	bool kingisChecking = isBlack ? blackKingisChecking :  whiteKingisChecking;
	return kingisChecking;
}

string Chessboard::toString() const{
	/*
	Method to convert 'Chessboard' object into 'string'.
	*/
	map<string, string> codePieces; // Unicode for chess pieces.
	codePieces["Pa"] = "\u265F";
	codePieces["pa"] = "\u2659";
	codePieces["kn"] = "\u265E";
	codePieces["Kn"] = "\u2658";
	codePieces["bi"] = "\u265D";
	codePieces["Bi"] = "\u2657";
	codePieces["ro"] = "\u265C";
	codePieces["Ro"] = "\u2656";
	codePieces["qu"] = "\u265B";
	codePieces["Qu"] = "\u2655";
	codePieces["ki"] = "\u265A";
	codePieces["Ki"] = "\u2654";

	map<string, int> pointsPieces; // Points of chess pieces.
	pointsPieces["Pa"] = 1;
	pointsPieces["pa"] = 1;
	pointsPieces["kn"] = 3;
	pointsPieces["Kn"] = 3;
	pointsPieces["bi"] = 3;
	pointsPieces["Bi"] = 3;
	pointsPieces["ro"] = 5;
	pointsPieces["Ro"] = 5;
	pointsPieces["qu"] = 9;
	pointsPieces["Qu"] = 9;
	// Note : no points for 'King' as they will never be captured.

	vector<Piece*> blackCaptured = getCaptured(true);
	vector<Piece*> whiteCaptured = getCaptured(false);

	queue<string> blackPiecesCaptured;
	int nbBlackCaptured = 0;
	int whitePoints = 0;
	for(auto it = blackCaptured.begin(); it != blackCaptured.end(); it++){
		blackPiecesCaptured.push(codePieces[(*it)->toString()]);
		nbBlackCaptured += 1;
		whitePoints += pointsPieces[(*it)->toString()];
	}
	string totalBlackPiecesCaptured = "    Total : " + to_string(nbBlackCaptured) \
	+ "   \u25B6   White points : " + to_string(whitePoints) + ".";

 	queue<string> whitePiecesCaptured;
	int nbWhiteCaptured = 0;
	int blackPoints = 0;
	for(auto it = whiteCaptured.begin(); it != whiteCaptured.end(); it++){
		whitePiecesCaptured.push(codePieces[(*it)->toString()]);
		nbWhiteCaptured += 1;
		blackPoints += pointsPieces[(*it)->toString()];
	}
	string totalWhitePiecesCaptured =  " Total : " + to_string(nbWhiteCaptured) \
	+ "   \u25B7   Black points : " + to_string(blackPoints) + ".";

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

	string titleWhitePieces = "       \u25A0 White pieces captured       ";
	string titleBlackPieces = "       \u25A1 Black pieces captured       ";

	string spaceTotal; // Gap between the totals and the first outline
	for(int s = 0; s < (titleWhitePieces.size() + 2 - totalWhitePiecesCaptured.size()); s ++) spaceTotal += " ";

	string s; // Entire line (of a square)
	string square; // Entire line (of a square) without piece

	string letterString; // Turn character into string

	string block; // Part of the square between its border and a piece

	int n = getHeight(); // Number of the square

	string space; // Space between the left border and the number
	string thirdOfSpace; // Space between the left border and the first captured piece
	for(int i = 0; i < titleBlackPieces.size(); i++){
		space += " ";
		if(i > 0 && i % 3 == 0) thirdOfSpace += " ";
	}

	// First line : upper line with letters
	string res = space + "  " + "   " + "  "; // (Number + space) + outline space + 2 spaces of the first square
	for(int letter = 'A'; letter < 'I'; letter++){
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
	for(int j = getHeight() * getWidth() - 1 - 7; j > -1 ; j -= 8){ // Browsing of the lines from the upper part
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
		else res += " " + thirdOfSpace + " "+ " "; // No more white pieces inside
		res += thirdOfSpace;
		res += to_string(n) + " \u2502 \u2588";
		// Part with eventually the pieces
		for(int i = j; i <= j + 7; i ++){
			square = beginWhite ? whiteSquare : blackSquare; // Line of an empty square
			block = beginWhite ? "\u2588\u2588" : "  "; // Two first characters for the line of a square with a piece
			if(!emptySquare(i % getHeight(), i / getHeight())) res += block + codePieces[board[i]->toString()] + block; // Busy square
			else res += square; // Empty square
			beginWhite = !beginWhite;
		}
		res += "\u2588 \u2502 " + to_string(n);
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
	for(int letter = 'A'; letter < 'I'; letter++){
		letterString = letter;
		res += letterString + "    "; // Space betwwen two letter
	}

	return "\n" + space + "  " + "   " + "      " + "      " + "Chessboard " \
	+ to_string(getHeight()) + " x " + to_string(getWidth()) + ":" + "\n\n" + res + "\n";
}

bool Chessboard::checksKing() const{
	/*
	Returns 'true' if after the last 'movement' his own king is checking.
	*/
	bool isBlack = getPiece(getLastMove().end)->getIsBlack();
	Position posKing = isBlack ? posBlackKing : posWhiteKing;
	unordered_set<Position, PositionHash> positions = getPiecePosition("all", !isBlack);
	for(auto it = positions.begin(); it != positions.end(); it++){
			if(getPiece(*it)->isValidMove(*it, posKing, this)) return true;
		}
	return false;
}

bool Chessboard::checksOpponentKing() const{
	/*
	Returns 'true' if after the last 'movement' opponent king is checking;
	*/
	bool isBlack = getPiece(getLastMove().end)->getIsBlack();
	Position posOpponentKing = !isBlack ? posBlackKing : posWhiteKing;
	unordered_set<Position, PositionHash> positions = getPiecePosition("all", isBlack);
	for(auto it = positions.begin(); it != positions.end(); it++){
			if(getPiece(*it)->isValidMove(*it, posOpponentKing, this)) return true;
		}
	return false;
}

void Chessboard::update(){
	/*
	Method to update the status of checking kings.
	*/
	// After the movement his own king is necessarily not checking as we know that if we call
	// the 'update' function the 'movement' is allowed.
	bool isBlack = getPiece(getLastMove().end)->getIsBlack();
	if(isBlack) blackKingisChecking = false;
	else whiteKingisChecking = false;

	if(checksOpponentKing()){
		if(isBlack) whiteKingisChecking = true;
		else blackKingisChecking = true;
	}
}

bool Chessboard::checkTie() const{
	/*
	Method to check the draw. The remaining pieces do not allow to checkmate one or the other king.
	*/
	unordered_set<Position, PositionHash> blackPieces = getPiecePosition("all", true);
	unordered_set<Position, PositionHash> whitePieces = getPiecePosition("all", false);
	int nbPieces = blackPieces.size() + whitePieces.size();
	if(nbPieces == 2){
		// King versus king (that is necessarily the case)
		return true;
	}
	else if(nbPieces == 3){
		// King and bishop versus king
		if(getPiecePosition("bi", true).size() + getPiecePosition("bi", false).size() == 1) return true;
		// King and knight versus king
		else if(getPiecePosition("kn", true).size() + getPiecePosition("kn", false).size() == 1) return true;
		return false;
	}
	else if(nbPieces == 4){
		// King and bishop versus king and bishop
		if(getPiecePosition("bi", true).size() == 1 && getPiecePosition("Bi", true).size() == 1) return true;
		return false;
	}
	else return false;
}

void Chessboard::endOfGame(){
	/*
	Method to verify if that is the end of the game. Throws exception if that is (i.e. checkmate or pat).
	*/
	bool isBlack = getPiece(getLastMove().end)->getIsBlack();
	string color = isBlack ? "blacks" : "whites";
	bool oppositeKingisChecking = isBlack ? whiteKingisChecking : blackKingisChecking;
	unordered_set<Position, PositionHash> positions = getPiecePosition("all", !isBlack);
	unordered_set<Position, PositionHash> validMoves;
	movement previousMove = getLastMove();
	bool tie = checkTie();
	string promo = "X";
	if(tie) throw Exception(14, "The game ends in a draw : the remaining pieces do not allow to checkmate.", 2);
	for(auto it = positions.begin(); it != positions.end(); it++){
		bool firstMove = getPiece(*it)->getFirstMove();
		validMoves = getPiece(*it)->getValidMoves(*it, this);
		if(getPiece(*it)->toString() == "pa" || getPiece(*it)->toString() == "Pa"){
			// If that is a pawn move, we replace the default argument 'X' by 'queen'.
			promo = "queen";
		}
		else promo = "X";
		for(auto itMove = validMoves.begin(); itMove != validMoves.end(); itMove++){
			bool wasEmpty = emptySquare(itMove->get_x(), itMove->get_y());
			move(*it, *itMove, promo);
			if(!checksKing()){
				cancelLastMove(firstMove, wasEmpty, promo);
				setLastMove(previousMove);
				return;
			}
			else{
				cancelLastMove(firstMove, wasEmpty, promo);
				setLastMove(previousMove);
			}
		}
	}
	if(oppositeKingisChecking) throw Exception(15, "The game ends with checkmate. The " + color + " won.", 2);
	else throw Exception(16, "The game ends with pat.", 2);
}

void Chessboard::specificMove(const Position &start, const Position &end, const string &promotion){
	/*
	Method that makes the current 'movement' if it does not checks his own king.
	*/
	if(start.get_x() == end.get_x() && start.get_y() == end.get_y()) throw Exception(11, "The arrival square is identical to the starting square.", 1);
	if(!getPiece(start)->isValidMove(start, end, this)) throw Exception(12, "Invalid movement.", 1);
	movement previousMove = getLastMove();
	bool firstMove = getPiece(start)->getFirstMove();
	bool wasEmpty = emptySquare(end.get_x(), end.get_y());
	string promo;
	if(getPiece(start)->toString() == "pa" || getPiece(start)->toString() == "Pa"){
		// If that is a pawn move, by default we replace the argument 'X' (if it is) by 'queen'.
		promo = (promotion != "X" ? promotion : "queen");
	}
	else promo = "X";
	move(start, end, promo);
	if(!checksKing()){ // The movement is allowed.
		update();
		endOfGame();
	}
	else{ // The movement is not allowed (i.e. it checks his own king).
		cancelLastMove(firstMove, wasEmpty, promo);
		setLastMove(previousMove);
		throw Exception(13, "The movement is forbidden as your king is checking after it.", 1);
	}
}

void Chessboard::makeMove(const Position &start, const Position &end, const string &promotion){
	/*
	Method to make a movement on the 'Chessboard'.
	*/
	Piece *ptr = nullptr;
	string figure;
	getPiece(start)->setFirstMove();
	bool isBlack = getPiece(start)->getIsBlack();
	// Update of the kings' position
	if(getPiece(start)->toString() == "Ki") posBlackKing = end;
	if(getPiece(start)->toString() == "ki") posWhiteKing = end;
	// Promotion
	if((getPiece(start)->toString() == "Pa" || getPiece(start)->toString() == "pa") && \
		(end.get_y() == getHeight() - 1 || end.get_y() == 0)){
			// By catching another piece
			if(!emptySquare(end.get_x(), end.get_y())){
				captured.push_back(getPiece(end));
			}
			bool isBlack = getPiece(start)->getIsBlack();
			bool b = true;
			string promo = promotion;
			while(b){
				try{
					if(promo == "queen"){
						add(new Queen(isBlack), end);
						b = false; // That is the argument by default
					}
					else if(promo == "rook"){
						add(new Rook(isBlack), end);
						b = false;
					}
					else if(promo == "bishop"){
						add(new Bishop(isBlack), end);
						b = false;
					}
					else if(promo == "knight"){
						add(new Knight(isBlack), end);
						b = false;
					}
					else{
						figure = isBlack ? "\u26AB" : "\u26AA";
						throw Exception(17, "The given argument for promotion '" + promo + "' is not available.", 2);
					}
				}
				catch(Exception const& e){
					cerr << "\nERROR: " << e.what() << endl; // Error 17
          cout << "\n" << figure << " Move : " << start.toString() << " \u21D2 " << end.toString() << endl;
					cout << "\nPlease enter a new argument among [queen, rook, bishop, knight] : ";
					string promoUser;
					getline(cin, promoUser);
					if(promoUser == "quit") throw Exception(17, "'quit' command: Quit the platform.", 2);
					else if(promoUser == "menu") throw Exception(18, "'menu' command: Go back to the main menu.", 2);
					else if(promoUser == "back") throw Exception(19, "'back' command: Go back to the previous menu.", 2);
					else if(promoUser == "commands" || promoUser == "help" || promoUser == "info") display(promoUser);
					else promo = promoUser; // continue (i.e. try the given 'promo' argument)
				}
			}
		}

	// Basic catch
	else if(!emptySquare(end.get_x(), end.get_y())){
		captured.push_back(getPiece(end));
		board[getHeight() * end.get_y() + end.get_x()] = getPiece(start);
	}
	// 'En passant' catching
	else if((getPiece(start)->toString() == "Pa" || getPiece(start)->toString() == "pa") && \
		emptySquare(end.get_x(), end.get_y()) && (start.get_x() != end.get_x())){
		Position p = Position(end.get_x(), start.get_y()); //  Position of the piece to catch
		captured.push_back(getPiece(p));
		clear(p); // We remove the piece
		board[getHeight() * end.get_y() + end.get_x()] = getPiece(start); // We change the pawn of square
	}
	// Castling
	else if((getPiece(start)->toString() == "Ki" || getPiece(start)->toString() == "ki") && start.get_distX(end) == 2){
		// The king
		board[getHeight() * end.get_y() + end.get_x()] = getPiece(start);
		// The rook
		if(end.get_x() - start.get_x() > 0){ // On the right
			board[getHeight() * end.get_y() + getWidth() - 1]->setFirstMove();
			board[getHeight() * end.get_y() + end.get_x() - 1] = board[getHeight() * end.get_y() + getWidth() - 1];
			board[getHeight() * end.get_y() + getWidth() - 1] = ptr;
		}
		else{ // On the left
			board[getHeight() * end.get_y()]->setFirstMove();
			board[getHeight() * end.get_y() + end.get_x() + 1] = board[getHeight() * end.get_y()]; // i.e. (1, 3)
			board[getHeight() * end.get_y()] = ptr; // i.e. '+ 0'
		}
	}
	else board[getHeight() * end.get_y() + end.get_x()] = getPiece(start); // Just a simple move
	clear(start);
	}

void Chessboard::cancelLastMove(bool firstMove, bool wasEmpty, const string &promotion){
	/*
	Method cancelling the last movement made on the 'Chessboard'.
	*/
	Piece *ptr = nullptr;
	Position start = getLastMove().start;
	Position end = getLastMove().end;

	// Promotion
	if((end.get_y() == getHeight() - 1 || end.get_y() == 0) && promotion != "X"){
		// We must check the 'promotion' parameter to know if that is a 'promotion' movement.
		// Note : if promotion != "X", the starting piece was a pawn, thus is this pawn was going
		// to a border of the board, it was necessarily for a promotion.
		add(new Pawn(getPiece(end)->getIsBlack()), start); // We return the pawn to its original position
		// By catching another piece
		if(!wasEmpty){
			add(captured.back(), end); // We replace the promoted piece by the one before
			captured.pop_back(); // We remove the promoted piece from the captured pieces
		}
		else board[getHeight() * end.get_y() + end.get_x()] = ptr;
		}
	// Basic catch
	else if(!wasEmpty){
		add(getPiece(end), start); // We put back the piece (starting position)
		board[getHeight() * end.get_y() + end.get_x()] = captured.back(); // We put back the catching piece
		captured.pop_back(); // We remove the piece from those that have been captured
	}
	// 'En passant' catching
	else if((getPiece(end)->toString() == "Pa" || getPiece(end)->toString() == "pa") && \
		wasEmpty && (start.get_x() != end.get_x())){
		board[getHeight() * start.get_y() + end.get_x()] = captured.back(); // We add again the piece
		captured.pop_back(); // We remove the piece from those that have been captured
		add(getPiece(end), start); // We put back the pawn to the starting position
		board[getHeight() * end.get_y() + end.get_x()] = ptr; // We remove the pawn to the arrival position
	}

	// Castling
	else if((getPiece(end)->toString() == "Ki" || getPiece(end)->toString() == "ki") && start.get_distX(end) == 2){
		// The king
		add(getPiece(end), start);
		board[getHeight() * end.get_y() + end.get_x()] = ptr;
		// The rook
		if(end.get_x() - start.get_x() > 0){ // On the right
			board[getHeight() * end.get_y() + getWidth() - 1] = board[getHeight() * end.get_y() + end.get_x() - 1];
			board[getHeight() * end.get_y() + end.get_x() - 1] = ptr; // i.e. (1, y)
			board[getHeight() * end.get_y() + getWidth() - 1]->resetFirstMove();
		}
		else{ // On the left
			board[getHeight() * end.get_y()] = board[getHeight() * end.get_y() + end.get_x() + 1];
			board[getHeight() * end.get_y() + end.get_x() + 1] = ptr;
			board[getHeight() * end.get_y()]->resetFirstMove();
		}
	}
	else{ // Just a simple move
		add(getPiece(end), start);
		board[getHeight() * end.get_y() + end.get_x()] = ptr;
	}
	if(firstMove) getPiece(start)->resetFirstMove();
	// Cancellation of the update of the kings' position
	if(getPiece(start)->toString() == "Ki") posBlackKing = start;
	if(getPiece(start)->toString() == "ki") posWhiteKing = start;
}

void Chessboard::message(bool blackPlay) const{
	/*
	Method displaying specific message to 'Chessboard'.
	*/
	if(getKingIsChecking(!blackPlay)) cout << "\t\t\t\t\t\t\t     \u26A0 Check !\n" << endl;
}

unordered_set<Position, PositionHash> Chessboard::getPossiblePositions(const Position& start) const{
	/*
	Method to get all the positions potentially available from start.
	(i.e. occupied by a 'Piece' of the other colour or empties)
	*/
	bool isBlack = getPiece(start)->getIsBlack();
	unordered_set<Position, PositionHash> possiblePositions;
	for(int i = 0; i < getHeight() * getWidth(); i++){
		if(emptySquare(i % getHeight(), i / getHeight())) possiblePositions.insert(getPosition(i));
		else if(getPiece(getPosition(i))->getIsBlack() != isBlack) possiblePositions.insert(getPosition(i));
	}
	return possiblePositions;
}

vector<movement> Chessboard::getAllValidMoves(bool isBlack){
	/*
	Method to get all the valid movements on 'Chessboard'.
	*/
	unordered_set<Position, PositionHash> piecePositions = getPiecePosition("all", isBlack);
	vector<movement> possibleMoves;
	for(auto it = piecePositions.begin(); it != piecePositions.end(); it++){
		unordered_set<Position, PositionHash> positions = getPossiblePositions(*it);
		for(auto it2 = positions.begin(); it2 != positions.end(); it2++){
			movement m = {*it, *it2};
			if(getPiece(m.start)->isValidMove(m.start, m.end, this)) possibleMoves.push_back(m);
		}
	}
	return possibleMoves;
}

void Chessboard::findBestMoves(bool isBlack){
	/*
  Method to find all the valid best moves on 'Chessboard' of player 'isBlack'.
  */
  vector<vector<movement>> bestMoves;
  // In-depth course
	if(isBlack) bestBlackMoves = bestMoves;
  else bestWhiteMoves = bestMoves;
}
