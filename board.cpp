#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "board.h"
#include "game.h"

using namespace std;

string o(int n, Tile tiles[]){
    if (tiles[n].owner >= 0){
        return "Owner : " + to_string(tiles[n].owner);
    } else {
        return "         ";
    }
}

string h(int n, Tile tiles[]){
    if (tiles[n].houses){
        return "Houses: " + to_string(tiles[n].houses);
    } else {
        return "         ";
    }
}

string t(int n, Tile tiles[]){
    if (tiles[n].hotels){
        return "Hotels: " + to_string(tiles[n].hotels);
    } else {
        return "         ";
    }
}

void PrintBoard(const vector<Player>& players, Tile tiles[]) {
    string boardLayout[56] = {
        "|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|",
        "|  Free Parking   |   Lei Yue Mun   |    Provincial   |  Wong Tai Sin   |  Kowloon Tong   | Kowloon station |    Kwun Tong    |    Mong Kok     |   Water Works   |  Tsim Sha Tsui  |   Go to Jail    |",
        "|                 |    "+o(21, tiles)+"    |    "+o(22, tiles)+"    |    "+o(23, tiles)+"    |    "+o(24, tiles)+"    |    "+o(25, tiles)+"    |    "+o(26, tiles)+"    |    "+o(27, tiles)+"    |    "+o(28, tiles)+"    |    "+o(29, tiles)+"    |                 |",
        "|                 |    "+h(21, tiles)+"    |                 |    "+h(23, tiles)+"    |    "+h(24, tiles)+"    |                 |    "+h(26, tiles)+"    |    "+h(27, tiles)+"    |                 |    "+h(29, tiles)+"    |                 |",
        "|                 |    "+t(21, tiles)+"    |                 |    "+t(23, tiles)+"    |    "+t(24, tiles)+"    |                 |    "+t(26, tiles)+"    |    "+t(27, tiles)+"    |                 |    "+t(29, tiles)+"    |                 |",
        "|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|",
        "|  Tseung Kwan O  |                                                                                                                                                                 |  Causeway Bay   |",
        "|    "+o(19, tiles)+"    |                                                                                                                                                                 |    "+o(31, tiles)+"    |",
        "|    "+h(19, tiles)+"    |                                                                                                                                                                 |    "+h(31, tiles)+"    |",
        "|    "+t(19, tiles)+"    |                                                                                                                                                                 |    "+t(31, tiles)+"    |",
        "|-----------------|                                                                                                                                                                 |-----------------|",
        "|    Sha Tin      |                                                                                                                                                                 |    Cyberport    |",
        "|    "+o(18, tiles)+"    |                                                                                                                                                                 |    "+o(32, tiles)+"    |",
        "|    "+h(18, tiles)+"    |                                                                                                                                                                 |    "+h(32, tiles)+"    |",
        "|    "+t(18, tiles)+"    |                                                                                                                                                                 |    "+t(32, tiles)+"    |",
        "|-----------------|                                                                                                                                                                 |-----------------|",
        "| Community Chest |                                                                                                                                                                 | Community Chest |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|-----------------|                                                                                                                                                                 |-----------------|",
        "|   Kwai Chung    |                                                                                                                                                                 |     Central     |",
        "|    "+o(16, tiles)+"    |                                                                                                                                                                 |    "+o(34, tiles)+"    |",
        "|    "+h(16, tiles)+"    |                                                                                                                                                                 |    "+h(34, tiles)+"    |",
        "|    "+t(16, tiles)+"    |                                                                                                                                                                 |    "+t(34, tiles)+"    |",
        "|-----------------|                                                                                                                                                                 |-----------------|",
        "| Tsing Yi station|                                                                                                                                                                 |Hong Kong station|",
        "|    "+o(15, tiles)+"    |                                                                                                                                                                 |    "+o(35, tiles)+"    |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|-----------------|                                                                                                                                                                 |-----------------|",
        "|   Sham Tseng    |                                                                                                                                                                 |     Chance      |",
        "|    "+o(14, tiles)+"    |                                                                                                                                                                 |                 |",
        "|    "+h(14, tiles)+"    |                                                                                                                                                                 |                 |",
        "|    "+t(14, tiles)+"    |                                                                                                                                                                 |                 |",
        "|-----------------|                                                                                                                                                                 |-----------------|",
        "|  Tin Shui Wai   |                                                                                                                                                                 |   Repulse Bay   |",
        "|    "+o(13, tiles)+"    |                                                                                                                                                                 |    "+o(37, tiles)+"    |",
        "|    "+h(13, tiles)+"    |                                                                                                                                                                 |    "+h(37, tiles)+"    |",
        "|    "+t(13, tiles)+"    |                                                                                                                                                                 |    "+t(37, tiles)+"    |",
        "|-----------------|                                                                                                                                                                 |-----------------|",
        "|Hongkong Electric|                                                                                                                                                                 |    Salary Tax   |",
        "|    "+o(12, tiles)+"    |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|                 |                                                                                                                                                                 |                 |",
        "|-----------------|                                                                                                                                                                 |-----------------|",
        "|     Lo Wu       |                                                                                                                                                                 |    The Peak     |",
        "|    "+o(11, tiles)+"    |                                                                                                                                                                 |    "+o(39, tiles)+"    |",
        "|    "+h(11, tiles)+"    |                                                                                                                                                                 |    "+h(39, tiles)+"    |",
        "|    "+t(11, tiles)+"    |                                                                                                                                                                 |    "+t(34, tiles)+"    |",
        "|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|",
        "|      Jail       |  Lamma Island   |   Cheung Chau   |     Chance      |    Ngong Ping   | Airport station |   Income Tax    |  Lantau Island  | Community Chest |  Chek Lap Kok   |       Go        |",
        "|                 |    "+ o(9, tiles)+"    |    "+ o(8, tiles)+"    |                 |    "+ o(6, tiles)+"    |    "+ o(5, tiles)+"    |                 |    "+ o(3, tiles)+"    |                 |    "+ o(1, tiles)+"    |                 |",
        "|                 |    "+ h(9, tiles)+"    |    "+ h(8, tiles)+"    |                 |    "+ h(6, tiles)+"    |                 |                 |    "+ h(3, tiles)+"    |                 |    "+ h(1, tiles)+"    |                 |",
        "|                 |    "+ t(9, tiles)+"    |    "+ t(8, tiles)+"    |                 |    "+ t(6, tiles)+"    |                 |                 |    "+ t(3, tiles)+"    |                 |    "+ t(1, tiles)+"    |                 |",
        "|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|"
    };

    // Print the board
    for (const auto& line : boardLayout) {
        cout << line << endl;
    }

    // Print the amount of money for each player
    for (const auto& player : players) {
        cout << "Player #" << player.index << ": " << player.name << " | Money: " << player.money << " | Location: " << tiles[player.position].name << endl;
    }
}