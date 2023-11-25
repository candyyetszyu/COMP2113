#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include<algorithm>

#include "rules.h"
#include "board.h"
#include "initalised_tiles.h"

using namespace std;

ChanceCard DrawChanceCard(vector<ChanceCard>& chance_card) {
    int randomIndex = rand() % chance_card.size();
    return chance_card[randomIndex];
}

void apply_chance_card_effect(Player& player, const ChanceCard& card, Tile tiles[], int free_parking, vector<Player>& players) {
    switch (card.type) {
        case ChanceCardType::AdvanceToGo:
            cout << player.name << " advances to GO and collects $500." << endl;
            player.position = 0; // GO tile is always at index 0
            player.money += 500;
            break;

        case ChanceCardType::GoToJail:
            cout << player.name << " goes to jail!" << endl;
            player.position = 10; // Jail tile is always at index 10
            player.in_jail = true; // Set the player in jail
            break;

        case ChanceCardType::GoBackThreeSpaces:
            cout << player.name << " goes back 3 spaces." << endl;
            player.position = (player.position - 3 + tile_size) % tile_size;
            break;

        case ChanceCardType::PayEveryone:
            cout << player.name << " has to pay everyone $200." << endl;
            player.money -= 200;
            for (auto& p : players) {
                if (p.name != player.name) {
                    p.money += 200;
                }
            }
            break;

        case ChanceCardType::PayBank:
            cout << player.name << " has to pay the bank $500." << endl;
            player.money -= 500;
            break;
    }
}

void pay_fine(Player& player, int fine) {
    player.money -= fine;
    player.in_jail = false;
    cout << player.name << " paid a fine of $" << fine << " and is released from jail." << endl;
}

void PrintBoard(const vector<Player>& players, Tile tiles[]);

int run_game(
        int n,
        vector<Player> players,
        Tile tiles[],
        int free_parking,
        vector<ChanceCard> chance_card
        ) {
    int i = 0;
    string cmd = "";

    // shuffle the chance card stack before starting the game
    random_shuffle(chance_card.begin(), chance_card.end());

    PrintBoard(players, tiles);

    while (true) {
        if (players[i].in_jail) {
            // Player is in jail
            cout << players[i].name << " is in jail and must wait for their next turn." << endl;
            cout << "Do you want to pay the $100 fine to be released immediately? (yes/no)" << endl;
            string choice;
            cin >> choice;
            
            if (choice == "yes") {
                pay_fine(players[i], 100);
            } else {
                cout << players[i].name << " chose not to pay the fine and will remain in jail." << endl;
            }
        } else {
            // roll dice
            int dice1 = rand() % 6 + 1;
            int dice2 = rand() % 6 + 1;
            cout << players[i].name << " rolled " << dice1 << " and " << dice2 << " on the dice." << endl;

            // move player position
            players[i].position = (players[i].position + dice1 + dice2) % tile_size;
            cout << players[i].name << " moved to tile " << players[i].position << "." << endl;

            // handle actions with tiles
            switch (tiles[players[i].position].type) {
                case 0: // chance
                    cout << players[i].name << " got a chance card!" << endl;

                    // apply chance card effect if available
                    if (!chance_card.empty()) {
                        apply_chance_card_effect(players[i], chance_card.back(), tiles, free_parking, players);
                        chance_card.pop_back(); // remove the last chance card
                    }

                    break;
                case 1: // community chest
                    cout << players[i].name << " got a community chest card!" << endl;
                    // TODO: Implement community chest card functionality
                    break;
                case 2: // go to jail
                    cout << players[i].name << " went to jail!" << endl;
                    players[i].position = 10; // Go to Jail tile
                    players[i].in_jail = true; // Set the player in jail
                    break;
                case 3: // free parking
                    cout << players[i].name << " moved to free parking." << endl;
                    // Nothing happens, player's turn ends.
                    break;
                case 4: // property
                    // TODO: Implement property tile functionality
                    break;
                case 5: // go
                    cout << players[i].name << " passed or landed on Go and collected $200." << endl;
                    players[i].money += 200;
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
        }

        PrintBoard(players, tiles);

        if (i + 1 == n) {
            // end round
            while (true){
            	cout << "Enter command: quit/next/rules/save/load:" << endl;
            	cin >> cmd;
	            if (cmd == "rules") {
	                rule();
	            } else if (cmd == "quit"){
	            	return 0;
	            } else if (cmd == "next"){
	            	break;
	            }
        	}

	        i = 0;
        } else {
            i++;
        }
    }
}
