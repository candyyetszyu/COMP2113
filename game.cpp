#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>

using namespace std;

const int tile_size = 40;

struct Player{
	int money = 0;
	int position = 0;
	string name = "";
	bool in_prison = false;
	bool is_bot;
};

struct Tile{
	int owner = -1;
	int houses = 0;
	int hotel = 0;
	int type = 0;
	string name = "";
};

int run_game(
		int n, // number of players
		vector<Player> players,
		Tile tiles[],
		int free_parking,
		vector<string> chance_card
	){	
	int i = 0;
	string cmd = "";
	while (true){
		// roll dice
		int dice1 = rand() % 6 + 1;
		int dice2 = rand() % 6 + 1;
		cout << players[i].name << " rolled " << dice1 << " and " << dice2 << " on the dice." << endl;

		// move
		players[i].position = (players[i].position + dice1 + dice2) % tile_size;
		cout << players[i].name << " moved to tile" <<  players[i].position << "." << endl;

		//handle actions with tiles


		if (i + 1 == n){
			// end round
			cin >> cmd;

			//handle commands
			i = 0;

		} else {
			i++;
		}
	}
}

