// # include <iostream>
//
// using namespace std;
//
// struct movement{
// 	string start;
// 	int end;
// };
//
// int main(){
//   movement a;
//   a.start = "gg";
//   a.end = 2;
//   movement b = a;
//   a.start = "hjj";
//   cout << b.start << endl;
// }
//
//
//
//























// bool Echiquier::exposesKing(const Position &start, const Position &end, bool estNoir) const{
// 	/*
// 	Returns True if a movement exposes a king (depends on the color).
// 	In other word if the starting position is on the same line, column or diagonal
// 	as the king's and there are no pieces between them or the arrival position
// 	on the same line, column or diagonal. We do not consider as the movement is one from the king.
// 	*/
// 	Position posKing = (estNoir) ? posRoiNoir : posRoiBlanc;
// 	if(start.sameDiagonal(posKing)){
// 		// If the piece stay in the same diagonal :
// 		// - If the piece is further than other pieces, it will not change anything.
// 		// - Otherwise, it will stay between the king and a possibly opponent piece.
// 		// Note : three pieces that are sharing a diagonal with each other are necessarily in the same one.
// 		if(start.sameDiagonal(end) && end.sameDiagonal(posKing)) return false;
// 		int min_x = min(start.get_x(), posKing.get_x());
// 		int min_y = min(start.get_y(), posKing.get_y());
// 		for(int d = 1; d < start.get_distX(posKing); d++){
// 			if(!caseVide(min_x + d, min_y + d)) return false;
// 		}
// 		return true;
// 	}
// 	else if(start.get_x() == posKing.get_x()){ // same column
// 		if(start.get_x() == end.get_x()) return false;
// 		int min_y = min(start.get_y(), posKing.get_y());
// 		for(int d = 1; d < start.get_distY(posKing); d++){
// 			if(!caseVide(start.get_x(), min_y + d)) return false;
// 		}
// 		return true;
// 	}
// 	else if(start.get_y() == posKing.get_y()){ // same row
// 		if(start.get_y() == end.get_y()) return false;
// 		int min_x = min(start.get_x(), posKing.get_x());
// 		for(int d = 1; d < start.get_distX(posKing); d++){
// 			if(!caseVide(min_x + d, start.get_y())) return false;
// 		}
// 		return true;
// 	}
// 	else return false; // nor on the same diagonal, column, or row.
// }
//
//
// bool Echiquier::checksKing(const Position &start, const Position &end, bool isBlack) const{
// 	/*
// 	Returns true if the movement checks his own king.
// 	*/
// 	// Note : It is impossible that by making 'en passant' catching  a pawn checks his own king (in diagonal).
// 	// In fact, this would mean that the king was already checked before the opponent
// 	// moves his pawn two squares forward...(not possible, otherwise it should have moved).
// 	// Nevertheless it is possible that the move check his own king (in row or column).
// 	// The case in column is managed as the other one, thus we must only verify the row case.
//
// 	// The king moves
// 	if(getPiece(start)->toString() == "ro" || getPiece(start)->toString() == "Ro"){
// 		// All the positions of the pieces of the opponent.
// 		unordered_set<Position, PositionHash> positions = getPiecePosition("all", !isBlack);
// 		for(auto it = positions.begin(); it != positions.end(); it++){
// 			if(*it != end) if(getPiece(*it)->isValidMove(*it, end, this)) return true;
// 		}
// 	}
// 	else if(exposesKing(start, end, isBlack)){ // Another piece move, but it may expose the king
// 		Position posKing = (isBlack) ? posRoiNoir : posRoiBlanc;
// 		// Whatever check the queen
// 		unordered_set<Position, PositionHash> queenPosition = getPiecePosition("re", !isBlack);
// 		auto itQueen = queenPosition.begin();
// 		// Not sure is useful to check the first condition...
// 		if(*itQueen != end) if(getPiece(*itQueen)->isValidMove(*itQueen, posKing, this)) return true;
//
// 		if(start.sameDiagonal(posKing)){ // Check the fools as well (diagonal)
// 			unordered_set<Position, PositionHash> foolPositions = getPiecePosition("fo", !isBlack);
// 			for(auto it = foolPositions.begin(); it != foolPositions.end(); it++){
// 				if(*it != end) if(getPiece(*it)->isValidMove(*it, posKing, this)) return true;
// 			}
// 		}
// 		else{ // Check the rooks as well (column or row)
// 			unordered_set<Position, PositionHash> rookPositions = getPiecePosition("to", !isBlack);
// 			for(auto it = rookPositions.begin(); it != rookPositions.end(); it++){
// 				if(*it != end) if(getPiece(*it)->isValidMove(*it, posKing, this)) return true;
// 			}
// 		}
// 	}
// 	// The 'en passant' taking : in row case and the king is on the side of the catching pawn.
// 	else if((getPiece(start)->toString() == "Pi" || getPiece(start)->toString() == "pi") && \
// 	caseVide(end.get_x(), end.get_y()) && (start.get_x() != end.get_x())){
// 		// Position of the captured pawn
// 		Position captured = Position(end.get_x(), start.get_y());
// 		if(posKing.get_y() == captured.get_y()){ // There are on the same row as the king
// 			int min_x = min(captured.get_x(), posKing.get_x());
// 			// To check if there are no other pieces between them
// 			for(int d = 1; d < captured.get_distX(posKing); d++){
// 				// There is a piece
// 				if(!caseVide(min_x + d, captured.get_y())) return false;
// 			}
// 			// There are no pieces : we must check if there are rooks or queen with valid movements
// 			// We also remove the catching pawn
// 			// Queen
// 			unordered_set<Position, PositionHash> queenPosition = getPiecePosition("re", !isBlack);
// 			auto itQueen = queenPosition.begin();
// 			if(*itQueen != end) if(getPiece(*itQueen)->isValidMove(*itQueen, posKing, this)) return true;
// 			// Rooks
// 			unordered_set<Position, PositionHash> rookPositions = getPiecePosition("to", !isBlack);
// 			for(auto it = rookPositions.begin(); it != rookPositions.end(); it++){
// 				if(*it != end) if(getPiece(*it)->isValidMove(*it, posKing, this)){
// 					return true;
// 				}
// 			}
// 		}
// 		// We add again the catching pawn
// 	}
// 	return false;
// }
//
// bool Echiquier::checksOpponentKing(const Position &start, const Position &end, bool isBlack) const{
// 	/*
// 	Returns true if the movement checks the opponent king.
// 	*/
// 	Position posKing = (!isBlack) ? posRoiNoir : posRoiBlanc;
// 	// From its new position, the moving piece can check the opponent king.
// 	// No matter if the movement is a capture (i.e. the arrival square is not empty).
// 	if(getPiece(start)->isValidMove(end, posKing, this)){
// 		// Note : from its starting position it can not already checks the opponent king,
// 		// as the opponent played before.
// 		return true;
// 	}
// 	if(exposesKing(start, end, !isBlack)){ // By moving the piece it may expose the opponent king
// 		// Whatever check the queen
// 		unordered_set<Position, PositionHash> queenPosition = getPiecePosition("re", isBlack);
// 		auto itQueen = queenPosition.begin();
// 		if(getPiece(*itQueen)->isValidMove(*itQueen, posKing, this)) return true;
//
// 		if(start.sameDiagonal(posKing)){ // Check the fools as well (diagonal)
// 			unordered_set<Position, PositionHash> foolPositions = getPiecePosition("fo", isBlack);
// 			for(auto it = foolPositions.begin(); it != foolPositions.end(); it++){
// 				if(getPiece(*it)->isValidMove(*it, posKing, this)) return true;
// 			}
// 		}
// 		else{ // Check the rooks as well (column or row)
// 			unordered_set<Position, PositionHash> rookPositions = getPiecePosition("to", isBlack);
// 			for(auto it = rookPositions.begin(); it != rookPositions.end(); it++){
// 				if(getPiece(*it)->isValidMove(*it, posKing, this)) return true;
// 			}
// 		}
// 	}
// 	// That is 'en passant' catching
// 	if((getPiece(start)->toString() == "Pi" || getPiece(start)->toString() == "pi") && \
// 		caseVide(end.get_x(), end.get_y()) && (start.get_x() != end.get_x())){
// 		// Position of the captured pawn
// 		Position captured = Position(end.get_x(), start.get_y());
// 		// We must check whether the captured of this pawn checks the oponent king
//
// 	}
// 	return false;
// }
//
//
// bool Echiquier::necessaryConditions(const Position &start, const Position &end, bool isBlack) const{
// 	/*
// 	Returns true is the movement meets the necessary conditions (i.e. his own king is not checking).
// 	*/
// 	bool kingChecking = isBlack ? blackKingisChecking : whiteKingisChecking;
// 	if(checksKing(start, end, isBlack)) return false; // The move checks his own king
// 	if(kingChecking){ // The king is currently checking
// 		// The king moves, we have already checked that it is not checking yet.
// 		if(getPiece(start)->toString() == "ro" || getPiece(start)->toString() == "Ro") return true;
// 		else{ // Another piece moves, we have to check whether it protects the king
// 			// All the positions of the pieces of the opponent
// 			// Note : if two pieces are currently checking, it is not possible to protect the king
// 			// by moving a piece other than the king.
// 			unordered_set<Position, PositionHash> positions = getPiecePosition("all", !isBlack);
// 			string pawn = isBlack ? "pi" : "Pi";
// 			string knight = isBlack ? "ca" : "Ca";
// 			string rook = isBlack ? "to" : "To";
// 			string fool = isBlack ? "fo" : "Fo";
// 			string queen = isBlack ? "re" : "Re";
// 			Position posKing = isBlack ? posRoiNoir : posRoiBlanc;
// 			// The opposing king cannot check
// 			for(auto it = positions.begin(); it != positions.end(); it++){
// 				if(*it != end && getPiece(*it)->isValidMove(*it, end, this)){
// 					if(getPiece(*it)->toString() == pawn) return false;
// 					else if(getPiece(*it)->toString() == knight) return false;
// 					else if(getPiece(*it)->toString() == rook){
// 						// The piece must be between the rook and the king.
// 						if(it->get_x() == posKing.get_x()){ // same column
// 							if(end.get_y() > min(it->get_y(), posKing.get_y()) \
// 							&& end.get_y() < max(it->get_y(), posKing.get_y())) continue;
// 							else return false;
// 						}
// 						else{ // same line
// 							if(end.get_x() > min(it->get_x(), posKing.get_x()) \
// 							&& end.get_x() < max(it->get_x(), posKing.get_x())) continue;
// 							else return false;
// 						}
// 					}
// 					else if(getPiece(*it)->toString() == fool){
// 						// The piece must be between the fool and the king.
// 						if(end.sameDiagonal(posKing) && it->sameDiagonal(end)){
// 							int min_x = min(it->get_x(), posKing.get_x());
// 							int min_y = min(it->get_y(), posKing.get_y());
// 							for(int d = 1; d < it->get_distX(posKing); d++){
// 								// The piece is between each other, we wheck other pieces
// 								if(Position(min_x + d, min_y + d) == end) continue;
// 							}
// 							return false;
// 						}
// 					}
// 					else{ // The queen
// 						// The piece must be between the queen and the king.
// 						if(it->get_x() == posKing.get_x()){ // same column
// 							if(end.get_y() > min(it->get_y(), posKing.get_y()) \
// 							&& end.get_y() < max(it->get_y(), posKing.get_y())) continue;
// 							else return false;
// 						}
// 						else if(it->get_y() == posKing.get_y()){ // same line
// 							if(end.get_x() > min(it->get_x(), posKing.get_x()) \
// 							&& end.get_x() < max(it->get_x(), posKing.get_x())) continue;
// 							else return false;
// 						}
// 						else{ // same diagonal
// 							if(end.sameDiagonal(posKing) && it->sameDiagonal(end)){
// 								int min_x = min(it->get_x(), posKing.get_x());
// 								int min_y = min(it->get_y(), posKing.get_y());
// 								for(int d = 1; d < it->get_distX(posKing); d++){
// 									// The piece is between each other, we wheck other pieces
// 									if(Position(min_x + d, min_y + d) == end) continue;
// 								}
// 								return false;
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// 	return true;
// }
