#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include<algorithm>

#include "rules.h"

using namespace std;

const int tile_size = 40;

struct Player {
    int money = 0; // amount of money the player has
    int position = 0; // position of the player on the board, integer between 0 and 39
    string name = ""; // name of player
    bool in_prison = false; // whether player is in prison or not
    bool is_bot;
};

struct Tile {
    int owner = -1; // int representing the i-th owner in vector<Player> players, -1 when no owner
    int houses = 0; // number of houses on the plot
    int hotel = 0; // number of hotels on the plot
    int type; // type of tile
    int price; //price
    int group; //color
    string name = "";
};

struct ChanceCard {
    ChanceCardType type;
    int amount; // amount is used for paying everyone $200 or paying the bank $500
};

string DrawChanceCard(vector<ChanceCard>& chance_card) {
    int randomIndex = rand() % chance_card.size();
    return chance_card[randomIndex];
}

enum class ChanceCardType {
    AdvanceToGo,
    GoToJail,
    GoBackThreeSpaces,
    PayEveryone,
    PayBank
};

void apply_chance_card_effect(Player& player, const ChanceCard& card, Tile tiles[], int free_parking, vector<Player>& players) {
    switch (card.type) {
        case ChanceCardType::AdvanceToGo:
            cout << player.name << " advances to GO and collects $500." << endl;
            player.position = tiles[0].index; // GO tile is always at index 0
            player.money += 500;
            break;

        case ChanceCardType::GoToJail:
            cout << player.name << " goes to jail!" << endl;
            player.position = tiles[10].index; // Jail tile is always at index 10
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

    while (true) {
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

        if (i + 1 == n) {
            // end round
            cin >> cmd;

            if (cmd == "rules") {
                rule();
            }
            i = 0;

        } else {
            i++;
        }
    }
}

