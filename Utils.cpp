# include "utils.hpp"

void display(const string &entry){
  /*
  Method to display message associated with command 'entry' given.
  */
  if(entry == "commands"){
    cout << "\n\t\t\t MAIN COMMANDS\n";
    cout << "\n\t\t\t \u21FE quit     : Quit the platfrom.";
    cout << "\n\t\t\t \u21FE commands : Get the list of the commands.";
    cout << "\n\t\t\t \u21FE help     : Get help about using the platform.";
    cout << "\n\t\t\t \u21FE back     : Go back to the previous menu.";
    cout << "\n\t\t\t \u21FE menu     : Go back to the main menu.";
    cout << "\n\t\t\t \u21FE info     : Get information about the platform.\n" << endl;
    cout << "\n\t\t\t LAUNCH FILE / NEWGAME COMMANDS\n";
    cout << "\n\t\t\t \u21FE launch 'filename' : Load the file 'filename' and launch it.";
    cout << "\n\t\t\t \u21FE launch            : Launch a new game.\n" << endl;
    cout << "\n\t\t\t LOADING FILE COMMANDS\n";
    cout << "\n\t\t\t \u21FE new  : Launch a new game.";
    cout << "\n\t\t\t \u21FE play : Pick up the game where it left off.\n" << endl;
    cout << "\n\t\t\t CHOICE GAME COMMANDS\n";
    cout << "\n\t\t\t \u21FE chess        : Launch a new chess game.";
    cout << "\n\t\t\t \u21FE draughts     : Launch a new draughts game.\n" << endl;
    cout << "\n\t\t\t GAME COMMANDS\n";
    cout << "\n\t\t\t \u21FE 'pos1' 'pos2' 'promo' : Move piece in 'pos1' to 'pos2' with eventually promotion in 'promo'.";
    cout << "\n\t\t\t \u21FE last                  : Get the last move.";
    cout << "\n\t\t\t \u21FE moves 'position'      : Get the valid moves from 'position'.";
    cout << "\n\t\t\t \u21FE moves all             : Get all the valid moves.";
    cout << "\n\t\t\t \u21FE piece 'position'      : Get the piece name in 'position'.";
    cout << "\n\t\t\t \u21FE 'position'            : Get the piece name in 'position' and its valid moves.";
    cout << "\n\t\t\t \u21FE pieces                : Get all the pieces (of the current player) and their position.";
    cout << "\n\t\t\t \u21FE pieces all            : Get all the pieces and their position.";
    cout << "\n\t\t\t \u21FE display               : Display the board.\n" << endl;
  }
  else if(entry == "help"){
    cout << "\n\t HELP \n";
    cout << "\n\t The platform allows you to play chess or draughts as well as loading";
    cout << " a file and see the associated game.";
    cout << "\n\t You can also continue this game.";
    cout << "\n\t About playing, you can either play against another person or computer (forthcoming).";
    cout << "\n\t The position must always be given in format 'Letter' + 'Number', such that: 'E4' or 'b6'.";
    cout << "\n\t You can get all the available commands by entering the following command \u25B8 commands \u25C2 .\n" << endl;
  }
  else{ //enter == "info"
    cout << "\n\t INFORMATION\n";
    cout << "\n\t The platform was developed in May 2023 for an object-oriented programming and software engineering project.";
    cout << "\n\t You can find the whole project code on GitHub : 'https://github.com/hmarcaur/Chess_project'.";
    cout << "\n\t Feel free to use it and to report any error or glitch.\n" << endl;
  }
}
