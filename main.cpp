#include<iostream>
#include<string>
#include<vector>

#include"game.h"
#include "rules.h"

using namespace std;

int main(){
	string cmd = "";
	bool bad_input = false;

	while (true){
		cout << "Enter command: quit/play/load:" <<endl;
		cin >> cmd;
		if (cmd == "quit"){
			return 0;
		} else if (cmd == "play"){
			while (true){
				cout << "Please input number of players: (integer between 2-6)" << endl;
				cin >> cmd;
				for(int i=0; i<cmd.size(); i++){
					if (!isdigit(cmd[i])){
						bad_input = true;
					}
				}
				if (bad_input==false && stoi(cmd) >=2 && stoi(cmd) <=6){
					break;
				}
				bad_input = false;
			}

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

