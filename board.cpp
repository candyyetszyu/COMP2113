#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "board.h"
#include "game.h"

using namespace std;

void PrintBoard(const vector<Player>& players, Tile tiles[]) {
    string boardLayout[67] = {
        "|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|",
        "|  Free Parking   |   Lei Yue Mun   |    Provincial   |  Wong Tai Sin   |  Kowloon Tong   | Kowloon station |    Kwun Tong    |    Mong Kok     |   Water Works   |  Tsim Sha Tsui  |   Go to Jail    |",
        "|                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |",
        "|                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |",
        "|                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |",
        "|                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |",
        "|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|",
        "|  Tseung Kwan O  |                                                                                                                                                                 |  Causeway Bay   |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|-----------------|                                                                                                                                                                 |-----------------|",
        "|    Sha Tin      |                                                                                                                                                                 |    Cyberport    |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|-----------------|                                                                                                                                                                 |-----------------|",
        "| Community Chest |                                                                                                                                                                 | Community Chest |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|-----------------|                                                                                                                                                                 |-----------------|",
        "|   Kwai Chung    |                                                                                                                                                                 |     Central     |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|-----------------|                                                                                                                                                                 |-----------------|",
        "| Tsing Yi station|                                                                                                                                                                 |Hong Kong station|",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|-----------------|                                                                                                                                                                 |-----------------|",
        "|   Sham Tseng    |                                                                                                                                                                 |     Chance      |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|-----------------|                                                                                                                                                                 |-----------------|",
        "|  Tin Shui Wai   |                                                                                                                                                                 |   Repulse Bay   |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|-----------------|                                                                                                                                                                 |-----------------|",
        "|Hongkong Electric|                                                                                                                                                                 |    Salary Tax   |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|-----------------|                                                                                                                                                                 |-----------------|",
        "|     Lo Wu       |                                                                                                                                                                 |    The Peak     |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|",
        "|      Jail       |  Lamma Island   |   Cheung Chau   |     Chance      |    Ngong Ping   | Airport station |   Income Tax    |  Lantau Island  | Community Chest |  Chek Lap Kok   |       Go        |",
        "|                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |",
        "|                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |",
        "|                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |",
        "|                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |",
        "|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|"
    };

    // Update the board layout with property details
    for (const auto& player : players) {
        if (tiles[player.position].type == 4 && tiles[player.position].owner != -1) {
            int ownerIndex = tiles[player.position].owner;
            const Player& owner = players[ownerIndex];
            string propertyDetails = "Owner: " + owner.name + ", Houses: " + to_string(tiles[player.position].houses) + ", Hotels: " + to_string(tiles[player.position].hotels);
            string& tile = boardLayout[player.position / 11 + 5];
        
            int insertPosition = (player.position % 11) * 12 + 1;
        
            if (tile.size() < insertPosition + propertyDetails.size()) {
                tile.resize(insertPosition + propertyDetails.size(), ' ');
            }
        
            tile.replace(insertPosition, propertyDetails.size(), propertyDetails);
        }
    }

    // Print the board
    for (const auto& line : boardLayout) {
        cout << line << endl;
    }

    // Print the amount of money for each player
    for (const auto& player : players) {
        cout << "Player: " << player.name << " | Money: " << player.money << " | Location: " << tiles[player.position].name << endl;
    }
}