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
    std::string name = "";
    void set(int a, int b, int c, int d, int e, int f, std::string g){
    	owner = a; houses = b; hotels = c; type = d; price = e; group = f; name = g;
    };
};

struct Player {
    int money = 0; // amount of money the player has
    int position = 0; // position of the player on the board, integer between 0 and 39
    std::string name = ""; // name of player
    bool in_jail = false; // whether player is in jail or not
    bool is_bot;
    bool change(int amount);
    void buyProperty(Tile& tile, int playerIndex);
    void sellProperty(Tile& tile);
};

enum class ChanceCardType {
    AdvanceToGo,
    GoToJail,
    GoBackThreeSpaces,
    PayEveryone,
    PayBank
};

struct ChanceCard {
    ChanceCardType type;
    int amount; // amount is used for paying everyone $200 or paying the bank $500
};

struct Game{
    int n;
    int free_parking;
    std::vector<Player> players;
    Tile tiles[40];
    std::vector<ChanceCard> chance_card;
    int run();
    Game(int n);
    Game(std::string filename);
    void save(std::string filename);
    bool bad_load = false; // used when error in loading save game
};

#endif
