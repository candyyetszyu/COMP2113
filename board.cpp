#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "board.h"

using namespace std;

void PrintBoard(const vector<Player>& players, Tile tiles[]) {
    string boardLayout[45] = {
        "|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|",
        "|    Free    |   Lei Yue  |            |    Wong    |   Kowloon  |  Kowloon   |    Kwun    |            |   Water    |  Tsim Sha  |            |",
        "|  Parking   |     Mun    | Provincial |  Tai Sin   |    Tong    |  station   |    Tong    |  Mong Kok  |   Works    |    Tsui    | Go to Jail |",
        "|            |            |            |            |            |            |            |            |            |            |            |",
        "|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|",
        "|   Tseung   |                                                                                                                    |  Causeway  |",
        "|   Kwan O   |                                                                                                                    |     Bay    |",
        "|            |                                                                                                                    |            |",
        "|------------|                                                                                                                    |------------|",
        "|            |                                                                                                                    |            |",
        "|  Sha Tin   |                                                                                                                    | Cyberport  |",
        "|            |                                                                                                                    |            |",
        "|------------|                                                                                                                    |------------|",
        "|            |                                                                                                                    |            |",
        "|  Community |                                                                                                                    | Community  |",
        "|   Chest    |                                                                                                                    |   Chest    |",
        "|------------|                                                                                                                    |------------|",
        "|            |                                                                                                                    |            |",
        "|    Kwai    |                                                                                                                    |   Central  |",
        "|   Chung    |                                                                                                                    |            |",
        "|------------|                                                                                                                    |------------|",
        "|            |                                                                                                                    |            |",
        "|  Tsing Yi  |                                                                                                                    |  Hong Kong |",
        "|  station   |                                                                                                                    |   statoin  |",
        "|------------|                                                                                                                    |------------|",
        "|            |                                                                                                                    |            |",
        "|   Sham     |                                                                                                                    |   Chance   |",
        "|   Tseng    |                                                                                                                    |            |",
        "|------------|                                                                                                                    |------------|",
        "|            |                                                                                                                    |            |",
        "|  Tin Shui  |                                                                                                                    |   Repulse  |",
        "|    Wai     |                                                                                                                    |     Bay    |",
        "|------------|                                                                                                                    |------------|",
        "|            |                                                                                                                    |            |",
        "|  Hongkong  |                                                                                                                    | Salary Tax |",
        "|  Electric  |                                                                                                                    |            |",
        "|------------|                                                                                                                    |------------|",
        "|            |                                                                                                                    |            |",
        "|   Lo Wu    |                                                                                                                    |  The Peak  |",
        "|            |                                                                                                                    |            |",
        "|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|",
        "|            |            |            |            |            |            |            |            |            |            |            |",
        "|    Jail    |    Lamma   |   Cheung   |   Chance   |    Ngong   |  Airport   |   Income   |   Lantau   |  Community |  Chek Lap  |     Go     |",
        "|            |   Island   |    Chau    |            |    Ping    |  station   |    Tax     |   Island   |    Chest   |     Kok    |            |",
        "|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|"
    };

    /*
    // Clear player positions
    for (int i = 0; i < 40; ++i) {
        tiles[i].players.clear();
    }

    // Update the board layout with player positions
    for (const auto& player : players) {
        tiles[player.position].players.push_back(player.name);
    }
    */

    // Print the board
    for (const auto& line : boardLayout) {
        cout << line << endl;
    }

    for (int i = 0; i < tile_size; i++) {
        cout << tiles[i].name;

        // Check if the tile is a property and a player owns it
        if (tiles[i].type == 4 && tiles[i].owner != -1) {
            int ownerIndex = tiles[i].owner;
            const Player& owner = players[ownerIndex];

            // Print the number of houses and hotels
            cout << " (Owner: " << owner.name;
            cout << ", Houses: " << tiles[i].houses;
            cout << ", Hotels: " << tiles[i].hotels;
            cout << ")";
        }
        cout << endl;
    }
}