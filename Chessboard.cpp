# include "Chessboard.hpp"

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
	}

	posBlackKing = Position(4, 7);
	posWhiteKing = Position(4, 0);

}

string Chessboard::toString() const{
	/*
	Method to convert 'Chessboard' object into 'string'.
	*/
	string str = "";
	string s;
	for(int i = 0; i < getHeight() * getWidth(); i++){
		Position p = Position(i % 8, i / 8);
		if(!emptySquare(i % 8, i / 8)){
			s = board[i]->toString();
		}
		else{
			s = "  ";
		}
		str += p.toString() + " : " + s + "\n";
	}
	return "Chessboard " + to_string(getHeight()) + " x " + to_string(getWidth()) + ":" + "\n" + str;
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
	Method to update king positions and possibly indicate that the opponent king is checking.
	*/
	// After the movement his own king is necessarily not checking as we know that if we call
	// the 'update' function the 'movement' is allowed.
	bool isBlack = getPiece(getLastMove().end)->getIsBlack();
	if(isBlack) blackKingisChecking = false;
	else whiteKingisChecking = false;

	if(getPiece(getLastMove().end)->toString() == "Ki") posBlackKing = getLastMove().end;
	if(getPiece(getLastMove().end)->toString() == "ki") posWhiteKing = getLastMove().end;
	if(checksOpponentKing()){
		if(isBlack) whiteKingisChecking = true;
		else blackKingisChecking = true;
	}
}

void Chessboard::endOfGame(string promotion){
	/*
	Method to verify if that is the end of the game. Throws exception if that is (i.e. checkmate or pat).
	*/
	bool isBlack = getPiece(getLastMove().end)->getIsBlack();
	string color = isBlack ? "blacks" : "whites";
	bool oppositeKingisChecking = isBlack ? whiteKingisChecking : blackKingisChecking;
	unordered_set<Position, PositionHash> positions = getPiecePosition("all", !isBlack);
	unordered_set<Position, PositionHash> validMoves;
	movement previousMove = getLastMove();

	for(auto it = positions.begin(); it != positions.end(); it++){
		bool firstMove = getPiece(*it)->getFirstMove();
		validMoves = getPiece(*it)->getValidMoves(*it, this);
		for(auto itMove = validMoves.begin(); itMove != validMoves.end(); itMove++){
			bool wasEmpty = emptySquare(itMove->get_x(), itMove->get_y());
			move(*it, *itMove, promotion);
			if(!checksKing()){
				setLastMove(previousMove);
				return;
			}
			else{
				cancelLastMove(firstMove, wasEmpty, promotion);
				setLastMove(previousMove);
			}
		}
	}
	if(oppositeKingisChecking) throw string("The game ends with checkmate. The" + color + " won.");
	else throw string("The game ends with pat.");
}

void Chessboard::specificMove(const Position &start, const Position &end, string promotion){
	/*
	Method to make a movement on the 'Chessboard'.
	*/
	Piece *ptr = nullptr;
	getPiece(start)->setFirstMove();
	bool isBlack = getPiece(start)->getIsBlack();

	// Promotion
	if((getPiece(start)->toString() == "Pa" || getPiece(start)->toString() == "pa") && \
		(end.get_y() == getHeight() || end.get_y() == 0)){
			// By catching another piece
			if(!emptySquare(end.get_x(), end.get_y())){
				captured.push_back(getPiece(end));
				add(new Queen(isBlack), end); // By default we add a queen
			}
			bool isBlack = getPiece(start)->getIsBlack();
			if(promotion == "queen"); // That is done by default
			else if(promotion == "rook") add(new Rook(isBlack), end);
			else if(promotion == "bishop") add(new Bishop(isBlack), end);
			else if(promotion == "knight") add(new Knight(isBlack), end);
			else throw string("The given argument for promotion '" + promotion + "'is not available.");
		}

	// Basic catch
	else if(!emptySquare(end.get_x(), end.get_y())){ // In case of promotion, now the end position is no longer empty.
		board[getHeight() * end.get_y() + end.get_x()] = getPiece(start);
		captured.push_back(getPiece(end));
	}
	// 'En passant' catching
	else if((getPiece(start)->toString() == "Pa" || getPiece(start)->toString() == "pa") && \
		emptySquare(end.get_x(), end.get_y()) && (start.get_x() != end.get_x())){
		Position p = Position(end.get_x(), start.get_y()); //  Position of the piece to catch
		captured.push_back(getPiece(p));
		board[getHeight() * end.get_y() + start.get_x()] = ptr; // We remove the piece
		board[getHeight() * end.get_y() + end.get_x()] = getPiece(start);
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
	else; // Just a simple move
	}

void Chessboard::cancelLastMove(bool firstMove, bool wasEmpty, string promotion){
	/*
	Method cancelling the last movement made on the 'Chessboard'.
	*/
	Piece *ptr = nullptr;
	Position start = getLastMove().start;
	Position end = getLastMove().end;

	// Promotion
	if((getPiece(end)->toString() == "Pa" || getPiece(end)->toString() == "pa") && \
		(end.get_y() == getHeight() || end.get_y() == 0)){
			add(new Pawn(getPiece(end)->getIsBlack()), start); // We return the pawn to its original psition
			// By catching another piece
			if(!wasEmpty){
				add(captured.back(), end); // We replace the promoted piece by the one before
				captured.pop_back(); // We remove the promoted piece from the captured pieces
			}
			else board[getHeight() * end.get_y() + end.get_x()] = ptr;
		}
	// Basic catch
	else if(!wasEmpty){
		board[getHeight() * end.get_y() + end.get_x()] = captured.back(); // We put back the ctching piece
		captured.pop_back(); // We remove the piece from those that have been captured
		add(getPiece(end), start); // We put back the piece (starting position)
		board[getHeight() * end.get_y() + end.get_x()] = ptr; // We remove the piece (arrival position)
	}
	// 'En passant' catching
	else if((getPiece(end)->toString() == "Pa" || getPiece(end)->toString() == "pa") && \
		wasEmpty && (start.get_x() != end.get_x())){
		board[getHeight() * end.get_y() + start.get_x()] = captured.back(); // We add again the piece
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
		}
		else{ // On the left
			board[getHeight() * end.get_y()] = board[getHeight() * end.get_y() + end.get_x() + 1];
			board[getHeight() * end.get_y() + end.get_x() + 1] = ptr;
		}
		board[getHeight() * end.get_y()]->resetFirstMove();
	}
	else{
		add(getPiece(end), start);
		board[getHeight() * end.get_y() + end.get_x()] = ptr; // Just a simple move
	}
	if(firstMove) getPiece(start)->resetFirstMove();
}
