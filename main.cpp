#include<iostream>
#include<string>
#include<vector>

#include"game.h"
#include "rules.h"
#include "initalised_tiles.h"

using namespace std;

int main(){
	string cmd = "";

	while (true){
		cout << "Enter command: quit/play/load:" <<endl;
		cin >> cmd;
		if (cmd == "quit"){
			return 0;
		} else if (cmd == "play"){
			cout << "Please input number of players:" << endl;
			cin >> cmd;

			Game game(stoi(cmd));
			game.run();
		} else if (cmd == "load"){
			cout << "Please input the file name to be loaded:" << endl;
			string fn;
			cin >> fn;
			Game game(fn);
			game.run();
		} else {
			cout << "Command \"" << cmd << "\" is invalid. Please retry." << endl;
		}
	}
}

