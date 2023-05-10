# include "Game.hpp"

Game::Game():fileName(""), endOfGame(false){
  /*
  Class constructor 'Game'.
  */
}

Game::Game(const string &file): fileName(file), endOfGame(false){
  /*
  Class constructor 'Game' with 'fileName' attribute.
  */
}

Game::Game(Board *boardGame): fileName(""), board(boardGame), endOfGame(false){
  /*
  Class constructor 'Game' with 'board' attribute.
  */
}

void Game::setFileName(string const &file){
  /*
  Setter method to 'fileName' attribute.
  */
  fileName = file;
}

string Game::getFileName() const{
  /*
  Getter method to 'fileName' attribute.
  */
  return fileName;
}

vector<movement> Game::getMovements() const{
  /*
	Getter method to 'movements' attribute.
	*/
  return movements;
}

vector<string> Game::getPromotions() const{
  /*
	Getter method to 'movements' attribute.
	*/
  return promotions;
}

void Game::readFile(){
  /*
  Method to read the file and instanciate the 'Game' attributes.
  */
  int indexLine = 0;
  bool isMove = false;
  ifstream file("instances/" + fileName);
  try{
    if(file){
      string line; // Stored current reading line
      while(getline(file, line)){
        string info;
        string sq2;
        string promo;
        indexLine += 1;
        istringstream stream_line{line};
        stream_line >> info;
        if(isMove){
          bool end = false;
          while(!end){
            try{
              stream_line >> sq2 >> promo;
              if(info == "") throw Exception(20, "Line : " + to_string(indexLine) + " - Both first and second arguments are missing (to move).", 4);
              else if(sq2 == "") throw Exception(21, "Line : " + to_string(indexLine) + " - Second argument is missing (to move).", 4);
              else{
                Position p1 = Position(info);
                Position p2 = Position(sq2);
                movement m = {p1, p2};
                movements.push_back(m);
                promotions.push_back(promo);
                end = true;
              }
            }
            catch(Exception const &e){
              if(e.getNumber() == 20); // No squares in this line, do nothing just ignore.
              else if(e.getNumber() == 21 || e.getNumber() <= 3){ // <= 3 error for position
                cerr << "\nERROR: " << e.what() << endl;
                cout << "\nPlease propose valid positions for this movement : " << endl;
                string line2;
                string info;
                string sq2;
                getline(cin, line2);
                istringstream stream_line2{line2};
                stream_line2 >> info >> sq2 >> promo;
                if(info == "quit") throw Exception(17, "'quit' command: Quit the platform.", 4);
                else if(info == "menu") throw Exception(18, "'menu' command: Go back to the main menu.", 4);
                else if(info == "back") throw Exception(19, "'back' command: Go back to the previous menu.", 4);
                else if(info == "commands" || info == "help" || info == "info") display(info);
                else; // pass
              }
              // This should never happen
              else throw Exception(22, "The reading of the file ended line " + to_string(indexLine) + ".", 4);
            }
          }
        }
        else if(info == "#"){
          stream_line >> gameName;
          if(gameName == "Chess") board = new Chessboard();
          else if(gameName == "Draughts" || gameName == "Checkers") board = new Draughtsboard();
          else throw Exception(23, "Line : " + to_string(indexLine) + " - The game '" + gameName + "' can not be played on the platform.", 4);
        }
        else if(info == "name"){
          string pass;
          stream_line >> pass >> name;
        }
        else if(info == "moves"){
          isMove = true;
        }
        else;
      }
    }
    else throw Exception(24, "The file ''" + fileName + "' can not be opened for reading.", 4);
  }
  catch(const Exception &e2){
    if(e2.getNumber() == 24) throw e2;
    else if(e2.getNumber() >= 17 && e2.getNumber() <= 19) throw e2; // We reject the error at the higher level
    cerr << "\nERROR: " << e2.what() << endl; // Error 23 or 24 (22 should not happen).
  }
}

void Game::playFile(){
  /*
  Method to play the game associated with 'fileName'. The board will be re-initialized whatever.
  */
  string figure1;
  string figure;
  bool blackPlay = false;
  string figure2;
  string opponent;
  string player;
  unordered_set<Position, PositionHash> validMoves;
  board->initialConditions();
  cout << board->toString() << endl;
  cout << "Whites begin !\n" << endl;
  for(int i = 0; i < movements.size(); i++){
    Position start = movements[i].start;
    Position end = movements[i].end;
    try{
      board->play(start, end, blackPlay, promotions[i]);
    }
    catch(Exception const &e){
      if((e.getNumber() >= 14 && e.getNumber() <= 16) ||  e.getNumber() == 26 || e.getNumber() == 27){
        cout << "\n\n" << board->toString() << endl;
        board->message(blackPlay);
        cerr << e.what() << "\n" << endl;
        endOfGame = true;
        break;
      }
      else if(e.getNumber() >= 17 && e.getNumber() <= 19) throw e; // We reject the error at the higher level
      else{
        cerr << "\nERROR: " << e.what() << endl;
        bool moveNotValide = true;
        while(moveNotValide){
          figure1 = blackPlay ? "\u26AB" : "\u26AA";
          cout << "\n" << figure1 << " Move : " << start.toString() << " \u21D2 " << end.toString() << " not valid.\n" << endl;
          string move;
          string sq1;
          string sq2;
          string promo;
          cout << "\nPlease propose another movement : ";
          getline(cin, move);
          cout << "\n";
          istringstream stream_move{move};
          stream_move >> sq1 >> sq2 >> promo;
          if(sq1 == "quit") throw Exception(17, "'quit' command: Quit the platform.", 4);
          else if(sq1 == "menu") throw Exception(18, "'menu' command: Go back to the main menu.", 4);
          else if(sq1 == "back") throw Exception(19, "'back' command: Go back to the previous menu.", 4);
          else if(sq1 == "commands" || sq1 == "help" || sq1 == "info") display(sq1);
          else{
            promo = promo != "" ? promo : promotions[i];
            if(sq1 == "pieces"){
              // All the pieces of the current color
              unordered_set<Position, PositionHash> positions = board->getPiecePosition("all", blackPlay);
              player = blackPlay ? "Black" : "White";
              opponent = blackPlay ? "White" : "Black";
              figure = blackPlay ? "\u26AB" : "\u26AA";
              figure2 = !blackPlay ? "\u26AB" : "\u26AA";
              cout << "\n" << player << " pieces : \n" << endl;
              for(auto it = positions.begin(); it != positions.end(); it++){
                cout << figure << " " << board->getPiece(*it)->toString() << " : " << it->toString() << endl;
              }
              if(sq2 == "all"){ // All the pieces
                unordered_set<Position, PositionHash> opponentPositions = board->getPiecePosition("all", blackPlay);
                cout << "\n" << opponent << " pieces : \n" << endl;
                for(auto it = opponentPositions.begin(); it != opponentPositions.end(); it++){
              		cout << figure2 << " " << board->getPiece(*it)->toString() << " : " << it->toString() << endl;
              	}
              }
              cout << "\n";
            }
            else if(sq1 == "display") cout << "\n\n" << board->toString() << endl;
            else if(sq1 == "last"){ // Last Move
              figure2 = !blackPlay ? "\u26AB" : "\u26AA";
              cout << "\n" << figure2 << " Move : " << board->getLastMove().start.toString() << " \u21D2 " << board->getLastMove().end.toString() << "\n" << endl;
            }
            else if(sq1 == "moves"){
              if(sq2 == "all"){ // All possible VALID moves (no check about king checking after it)
                vector<movement> validMoves = board->getAllValidMoves(blackPlay);
                cout << "\n";
                figure = blackPlay ? "\u26AB" : "\u26AA";
                for(int i = 0; i < validMoves.size(); i++){
                  cout << figure << " " << board->getPiece(validMoves[i].start)->toString() << " : " << validMoves[i].start.toString() << " \u21D2 " << validMoves[i].end.toString() << endl;
                }
                cout << "\n";
              }
              else{ // With a departure position
                cout << "\n";
                try{
                  Position p = Position(sq2);
                  validMoves = board->getPiece(p)->getValidMoves(p, board);
                  figure = board->getPiece(p)->getIsBlack() ? "\u26AB" : "\u26AA";
                  for(auto it2 = validMoves.begin(); it2 != validMoves.end(); it2++){
                    cout << figure << " " << board->getPiece(p)->toString() << " : " << p.toString() << " \u21D2 " << it2->toString() << endl;
                  }
                  cout << "\n";
                }
                catch(Exception const& e){ // just come back to the main while loop of the method
                  cerr << "\nERROR: " << e.what() << endl;
                }
              }
            }
            else if(sq1 == "piece"){ // With a position
              try{
                Position p = Position(sq2);
                if(board->emptySquare(p.get_x(), p.get_y())) cout << "\nThe square is empty !\n" << endl;
                else{
                  figure = blackPlay ? "\u26AB" : "\u26AA";
                  cout << "\n" << figure << " " << board->getPiece(p)->toString() << "\n" << endl;
                }
              }
              catch(Exception const& e){
                cerr << "\nERROR: " << e.what() << endl; // just come back to the main while loop of the method
              }
            }
            else if(sq1 != "" && sq2 == ""){ // Just a position -> piece + move
              try{
                Position p = Position(sq1);
                figure = blackPlay ? "\u26AB" : "\u26AA";
                cout << "\n" << figure << " " << board->getPiece(p)->toString() << endl;
                validMoves = board->getPiece(p)->getValidMoves(p, board);
                for(auto it2 = validMoves.begin(); it2 != validMoves.end(); it2++){
                  cout << "\t\u21D2 " << it2->toString() << endl;
                }
                cout << "\n";
              }
              catch(Exception const& e){
                cerr << "\nERROR: " << e.what() << endl; // just come back to the main while loop of the method
              }
            }
            else if(sq1 != "" && sq2 != ""){ // Two positions
              try{
                start = Position(sq1);
                end = Position(sq2);
                board->play(start, end, blackPlay, promo);
                moveNotValide = false;
              }
              catch(Exception const &e2){
                if(e2.getNumber() >= 17 && e2.getNumber() <= 19) throw e2; // We reject the error at the higher level
                else cerr << e2.what() << "\n" << endl;
              }
            }
          }
        }
      }
    }
    cout << "\n\n" << board->toString() << endl;
    figure = blackPlay ? "\u26AB" : "\u26AA";
    cout << figure << " Move : " << start.toString() << " \u21D2 " << end.toString() << "\n" << endl;
    board->message(blackPlay);
    blackPlay = !blackPlay; // It's the other colour's turn to play
    if(blackPlay) cout << "It's the blacks' turn !\n" << endl;
    else cout << "It's the whites' turn !\n" << endl;
  }
}

void Game::play(bool reset){
  /*
  Method to play game.
  */
  bool blackPlay;
  if(reset){
    // the board is re-initialized
    board->initialConditions();
    cout << board->toString() << endl;
    blackPlay = false;
    cout << "Whites begin !\n" << endl;
  }
  else if(!endOfGame){
    blackPlay = board->getPiece(board->getLastMove().end)->getIsBlack() ? false : true;
    if(blackPlay) cout << "\nIt's the blacks' turn !\n" << endl;
    else cout << "\nIt's the whites' turn !\n" << endl;
  }
  // endOfGame = True
  else throw Exception(25, "It is not possible to keep on playing this game as it is over", 4);
  string figure;
  string figure2;
  string player;
  string opponent;
  unordered_set<Position, PositionHash> validMoves;
  while(!endOfGame){
    string move;
    string strStart;
    string strEnd;
    string promotion;
    cout << "Enter the move to be played : ";
    getline(cin, move);
    istringstream stream_line{move};
    stream_line >> strStart >> strEnd;
    if(strStart == "quit") throw Exception(17, "'quit' command: Quit the platform.", 4);
    else if(strStart == "menu") throw Exception(18, "'menu' command: Go back to the main menu.", 4);
    else if(strStart == "back") throw Exception(19, "'back' command: Go back to the previous menu.", 4);
    else if(strStart == "commands" || strStart == "help" || strStart == "info") display(strStart);
    else{
      try{
        if(strStart == "pieces"){
          // All the pieces of the current color
          unordered_set<Position, PositionHash> positions = board->getPiecePosition("all", blackPlay);
          player = blackPlay ? "Black" : "White";
          opponent = blackPlay ? "White" : "Black";
          figure = blackPlay ? "\u26AB" : "\u26AA";
          figure2 = !blackPlay ? "\u26AB" : "\u26AA";
          cout << "\n" << player << " pieces : \n" << endl;
          for(auto it = positions.begin(); it != positions.end(); it++){
            cout << figure << " " << board->getPiece(*it)->toString() << " : " << it->toString() << endl;
          }
          if(strEnd == "all"){ // All the pieces
            unordered_set<Position, PositionHash> opponentPositions = board->getPiecePosition("all", blackPlay);
            cout << "\n" << opponent << " pieces : \n" << endl;
            for(auto it = opponentPositions.begin(); it != opponentPositions.end(); it++){
          		cout << figure2 << " " << board->getPiece(*it)->toString() << " : " << it->toString() << endl;
          	}
          }
          cout << "\n";
        }
        else if(strStart == "display") cout << "\n\n" << board->toString() << endl;
        else if(strStart == "last"){ // Last Move
          figure2 = !blackPlay ? "\u26AB" : "\u26AA";
          cout << "\n" << figure2 << " Move : " << board->getLastMove().start.toString() << " \u21D2 " << board->getLastMove().end.toString() << "\n" << endl;
        }
        else if(strStart == "moves"){
          if(strEnd == "all"){
            vector<movement> validMoves = board->getAllValidMoves(blackPlay);
            cout << "\n";
            figure = blackPlay ? "\u26AB" : "\u26AA";
            for(int i = 0; i < validMoves.size(); i++){
              cout << figure << " " << board->getPiece(validMoves[i].start)->toString() << " : " << validMoves[i].start.toString() << " \u21D2 " << validMoves[i].end.toString() << endl;
            }
            cout << "\n";
          }
          else{ // With a departure position
            cout << "\n";
            try{
              Position p = Position(strEnd);
              validMoves = board->getPiece(p)->getValidMoves(p, board);
              figure = board->getPiece(p)->getIsBlack() ? "\u26AB" : "\u26AA";
              for(auto it2 = validMoves.begin(); it2 != validMoves.end(); it2++){
                cout << figure << " " << board->getPiece(p)->toString() << " : " << p.toString() << " \u21D2 " << it2->toString() << endl;
              }
              cout << "\n";
            }
            catch(Exception const& e){ // just come back to the main while loop of the method
              cerr << "\nERROR: " << e.what() << endl;
            }
          }
        }
        else if(strStart == "piece"){ // With a position
          try{
            Position p = Position(strEnd);
            if(board->emptySquare(p.get_x(), p.get_y())) cout << "\nThe square is empty !\n" << endl;
            else{
              figure = board->getPiece(p)->getIsBlack() ? "\u26AB" : "\u26AA";
              cout << "\n" << figure << " " << board->getPiece(p)->toString() << "\n" << endl;
            }
          }
          catch(Exception const& e){
            cerr << "\nERROR: " << e.what() << endl; // just come back to the main while loop of the method
          }
        }
        else if(strStart != "" && strEnd == ""){ // Just a position -> piece + move
          try{
            Position p = Position(strStart);
            figure = blackPlay ? "\u26AB" : "\u26AA";
            cout << "\n" << figure << " " << board->getPiece(p)->toString() << endl;
            validMoves = board->getPiece(p)->getValidMoves(p, board);
            for(auto it2 = validMoves.begin(); it2 != validMoves.end(); it2++){
              cout << "\t\u21D2 " << it2->toString() << endl;
            }
            cout << "\n";
          }
          catch(Exception const& e){
            cerr << "\nERROR: " << e.what() << endl; // just come back to the main while loop of the method
          }
        }
        else if(strStart != "" && strEnd != ""){ // Two positions
          Position start = Position(strStart);
          Position end = Position(strEnd);
          stream_line >> promotion;
          figure = blackPlay ? "\u26AB" : "\u26AA";
          board->play(start, end, blackPlay, promotion);
          cout << "\n\n" << board->toString() << endl;
          cout << figure << " Move : " << start.toString() << " \u21D2 " << end.toString() << "\n" << endl;
          board->message(blackPlay);
          blackPlay = !blackPlay; // It's the other colour's turn to play
        }
        else cout << "\nInvalid command: please enter a new valid one.\n" << endl;
      }
      catch(Exception const& e){
        if((e.getNumber() >= 14 && e.getNumber() <= 16) ||  e.getNumber() == 26 || e.getNumber() == 27){
          figure = blackPlay ? "\u26AB" : "\u26AA";
          Position start = Position(strStart);
          Position end = Position(strEnd);
          cout << "\n\n" << board->toString() << endl;
          cout << figure << " Move : " << start.toString() << " \u21D2 " << end.toString() << "\n" << endl;
          cerr << e.what() << "\n" << endl;
          endOfGame = true;
        }
        else{
          cerr << "\nERROR: " << e.what() << endl;
          cout << "\nPlease propose another movement. \n" << endl;
        }
      }
    }
    if(endOfGame); // pass
    else if(blackPlay) cout << "It's the blacks' turn !\n" << endl; // Blacks
    else cout << "It's the whites' turn !\n" << endl; // Whites
  }
}
