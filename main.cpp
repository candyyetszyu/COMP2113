#include<iostream>
#include<string>

#include"game.h"

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

			Player player;
			vector<Player> players;
			for (int i = 0; i < stoi(cmd); i++){
				player.name = "Player " + to_string(i);
				player.is_bot = i;  // results in is_bot = false only for the first player
				players.push_back(player);
			}
			Tile tiles[40] = {}; // TODO: add data
			vector<string> chance_card; // TODO: add data

			run_game(stoi(cmd), players, tiles, 0, chance_card);
		} else if (cmd == "load"){
			//handle loading here
		} else {
			cout << "Command \"" << cmd << "\" is invalid. Please retry." << endl;
		}
	}
}

