# include "Position.hpp"
# include "Piece.hpp"
# include "Board.hpp"
# include "Chessboard.hpp"
# include "Pawn.hpp"
# include "Queen.hpp"
# include "Bishop.hpp"
# include "Knight.hpp"
# include "Rook.hpp"

using namespace std;

int main(){
	Chessboard c = Chessboard();
	c.initialConditions();
	cout << c.toString() << endl;
}
