# Chess_project
Code of the chess project for OOP (Object Oriented Programming) and SE (software engineering).
---
The code is writing in C++ language. It could be launch in any terminal by typing `make -all`, then `./Chess`.
> Note that the interface was designed to be launched in *Windows* **terminale** using *Windows Power shell*, *Campbell*  color scheme and *Lucida Console* font face.
---
The code allows to play **chess** and **draughts/checkers** games on a terminal interface. In addition, the user(s) can get some information to help him/them while playing.
---
## Class management :
- Game
- Position
- Board (*abstract*)
  - Chessboard
  - Draughtsboard
- Piece (*abstract*)
  - Pawn
  - Rook
  - Knight
  - Bishop
  - Queen
  - King
  - DraughtsPawn
  - DraughtsQueen

## Additional files :
- Utils (*display*)
- main (*code launcher*)
---
## Impovements :
- Adding the save current game possibility.
- Developped the automatic playing (e.g. *Min/Max* algorithm).
- Adding the possibility to play file manually.
- Adding the possibility to cancel a move (for *user*).
- Add a parser of *PGN* file.
- Add the possibility to start a game in a given *Position*.
- Include suggestion of moves to play directly on the board on the interface.
- Only propose truly valid moves in chess, no those who put in check his own king.
---
Feel free to use this code.
