#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>

#include "rules.h"

using namespace std;

const int tile_size = 40;

struct Player{
    int money = 0; // amount of money the player has
    int position = 0; // position of the player on the board, integer between 0 and 39
    string name = ""; // name of player
    bool in_prison = false; // whether player is in prison or not
    bool is_bot;
};

struct Tile{
    int owner = -1; // int representing the i-th owner in vector<Player> players, -1 when no owner
    int houses = 0; // number of houses on the plot
    int hotel = 0; // number of hotels on the plot
    int type; // type of tile
    int price; //price
    int group; //color
    string name = "";
};

string DrawChanceCard(vector<string> chance_card) {
    int randomIndex = rand() % chance_card.size();
    return chance_card[randomIndex];
}

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

        // move player position
        players[i].position = (players[i].position + dice1 + dice2) % tile_size;
        cout << players[i].name << " moved to tile " << players[i].position << "." << endl;

        //handle actions with tiles
        switch (tiles[players[i].position].type) {
            case 0: // chance
                cout << players[i].name << " got a chance card!" << endl;
                // TODO: Implement chance card functionality
                break;
            case 1: // community chest
                cout << players[i].name << " got a community chest card!" << endl;
                // TODO: Implement community chest card functionality
                break;
            case 2: // go to jail
                cout << players[i].name << " went to jail!" << endl;
                players[i].position = 10; // Go to Jail tile
                players[i].in_prison = true;
                break;
            case 3: // free parking
                cout << players[i].name << " moved to free parking and received $" << free_parking << "!" << endl;
                players[i].money += free_parking;
                break;
            case 4: // property
                // TODO: Implement property tile functionality
                break;
            case 5: // go
                // TODO: Implement go tile functionality
                break;
            case 6: // tax
                cout << players[i].name << " paid $" << tiles[players[i].position].name << " tax!" << endl;
                players[i].money -= atoi(tiles[players[i].position].name.c_str());
                break;
            case 7: // railroad
                // TODO: Implement railroad tile functionality
                break;
            case 8: // utility
                // TODO: Implement utility tile functionality
                break;
        }

        if (i + 1 == n){
            // end round
            cin >> cmd;

            if (cmd == 'rules'){
               rule();
            i = 0;

        } else {
            i++;
        }
    }
}
