# include "Game.hpp"

using namespace std;

int main(){
	/*
	Main program to play chess or draughts.
	*/
  cout << "\n\n" << endl;
  cout << "\t\t\t\u250C\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2510";
	cout << "\n\t\t\t\u2502\t\tWelcome to the board game platform \u2757\t\t\u2502" << endl;
  cout << "\t\t\t\u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2518\n\n";
  cout << "\t\t  \u25C8 Please note that you can quit the platform at any moment by enter \u25B8 quit \u25C2 \u25C8\n" << endl;
  cout << "\t\u25C8 Feel free to use commands : 'menu', 'back', 'commands', 'help' and 'information' whenever you want. \u25C8\n" << endl;

  bool end = false;
  bool end2;
  bool end3;
  bool end4;
  bool endFlag;
  while(!end){
    string enter;
		cout << "\n\n\t\t\t     \u21AA Press \u25B8 enter \u25C2 if you want to start a new game \u21A9\n" << endl;
    cout << "\t\t\t\t\t\t       ";
    getline(cin, enter);
    if(enter == "quit") return 0;
    else if(enter == "commands" || enter == "help" || enter == "info") display(enter);
    else if(enter == ""){
      end2 = false;
      endFlag = false;
      while(!end2){
        string launcher;
        string filename;
        string pass;
        cout << "\nWould you want to load a file and launch it [launch filename] or [l]aunch a new game ? ";
        getline(cin, launcher);
        istringstream stream_launcher{launcher};
        stream_launcher >> pass;
        stream_launcher >> filename;
        if(pass == "quit") return 0;
        else if(pass == "menu" || pass == "back") end2 = true;
        else if(pass == "commands" || pass == "help" || pass == "info") display(pass);
        else if(pass == "launch" && filename != ""){
          Game game = Game(filename);
          try{
            game.readFile();
            game.playFile();
            endFlag = false;
          }
          catch(const Exception &e){
            if(e.getNumber() == 17) return 0;
            else if(e.getNumber() == 18){
              endFlag = true;
              end2 = true;
            }
            else if(e.getNumber() == 19) endFlag = true; // back : pass to stay in the same menu
            else if(e.getNumber() == 24){
              cerr << "\nERROR: " << e.what() << endl;
              cout << "\nPlease propose another file or [l]aunch a new file." << endl;
              endFlag = true;
            }
            else{
              cerr << "\nERROR: " << e.what() << endl;
              endFlag = true;
            }
          }
          end3 = endFlag;
          while(!end3){
            string load;
            string g;
            cout << "\nWould you like to [play] on the current board or on a [new] one ? ";
            getline(cin, load);
            istringstream stream_load{load};
            stream_load >> g;
            if(g == "quit") return 0;
            else if(g == "menu"){
              end2 = true;
              end3 = true;
            }
            else if(g == "back") end3 = true;
            else if(g == "commands" || g == "help" || g == "info") display(g);// Add try and catch
            else if(g == "play" || g == "new"){
              try{
                bool b = g == "new";
                game.play(b);
              }
              catch(const Exception &e){
                if(e.getNumber() == 17) return 0;
                else if(e.getNumber() == 18){ // menu
                  end2 = true;
                  end3 = true;
                }
                else if(e.getNumber() == 19); // back : pass to stay in the same menu
                else; // Ignore
              }
            }
            else cout << "\nInvalid command: please enter a new valid one.\n" << endl;
          }
        }
        else if(pass == "launch" || pass == "l"){ // i.e. launch a new game
          end4 = false;
          while(!end4){
            string g3;
          	cout << "\nWould you like to play [c]hess or [d]raughts ? ";
          	getline(cin, g3);
            if(g3 == "quit") return 0;
            else if(g3 == "menu"){
              end2 = true;
              end4 = true;
            }
            else if(g3 == "back") end4 = true;
            else if(g3 == "commands" || g3 == "help" || g3 == "info") display(g3);
          	else if(g3 == "chess" || g3 == "c"){
              Chessboard *c = new Chessboard();
              Game game = Game(c);
              try{
                game.play(true);
              }
              catch(Exception const& e){
                if(e.getNumber() == 17) return 0;
                else if(e.getNumber() == 18){
                  delete c;
                  end2 = true;
                  end4 = true;
                }
                else if(e.getNumber() == 19) delete c; // back : pass to stay in the same menu
                else; // Ignore
              }
          	}
          	else if(g3 == "draughts" || g3 == "d"){
              Draughtsboard *d = new Draughtsboard();
              Game game = Game(d);
              try{
                game.play(true);
              }
              catch(Exception const& e){
                if(e.getNumber() == 17) return 0;
                else if(e.getNumber() == 18){
                  delete d;
                  end2 = true;
                  end4 = true;
                }
                else if(e.getNumber() == 19) delete d; // back : pass to stay in the same menu
                else; // Ignore
              }
          	}
            else cout << "\nInvalid command: please enter a new valid one.\n" << endl;
          }
        }
        else cout << "\nInvalid command: please enter a new valid one.\n" << endl;
      }
    }
    else cout << "\nInvalid command: please enter a new valid one.\n" << endl;
	}
}
