#include <vector>
#include <string>
#ifndef GAME_H

#define GAME_H

const int tile_size = 40;

struct Tile {
    int owner = -1; // int representing the i-th owner in vector<Player> players, -1 when no owner
    int houses = 0; // number of houses on the plot
    int hotels = 0; // number of hotels on the plot
    int type; // type of tile
    int price; //price
    int group; //color
    bool isMortgaged = false; // check whether a property is mortgaged, false by default
    std::string name = "";
    void set(int a, int b, int c, int d, int e, int f, std::string g){
    	owner = a; houses = b; hotels = c; type = d; price = e; group = f; name = g;
    };
};

struct Player {
    int money = 0; // amount of money the player has
    int position = 0; // position of the player on the board, integer between 0 and 39
    int index; // index of player in vector
    std::string name = ""; // name of player
    bool in_jail = false; // whether player is in jail or not
    bool is_bot;
    void buyProperty(Tile& tile);
    void sellProperty(Tile& tile);
    void mortgageProperty(Tile& tile);
    void unmortgageProperty(Tile& tile);
};

// Define the Chance card codes
enum class ChanceCardType {
    AdvanceToGo,
    GoToJail,
    GoBackThreeSpaces,
    PayEveryone,
    PayBank
};

struct ChanceCard {
    ChanceCardType type;
    std::string message;
};

// Define the Community Chest card codes
enum class CommunityChestCardType {
    AdvanceToGo,
    FoundMoney,
    GoToJail,
    PayHospitalFees,
    ConsumptionVoucher,
    ChineseNewYear
};

struct CommunityChestCard {
    CommunityChestCardType type;
    std::string message;
};

struct Game{
    int n;
    std::vector<Player> players;
    Tile tiles[40];
    int run();
    Game(int n);
    Game(std::string filename);
    void save(std::string filename);
    bool change_amount(int amount, Player& player);
    void Bankrupt(Player& player);
    void payRent(Player& player, Tile& tile);
    void apply_chance_card_effect(Player& player, const ChanceCard& card);
    void apply_community_chest_card_effect(Player& player, const CommunityChestCard& card);
    bool bad_load = false; // used when error in loading save game
    void buyHouse(Tile& tile, Player& player);
    void buyHotel(Tile& tile, Player& player);
    void sellHouse(Tile& tile, Player& player);
    void sellHotel(Tile& tile, Player& player);
};

#endif
