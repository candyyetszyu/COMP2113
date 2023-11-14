#ifndef GAME_H

#define GAME_H

const int tile_size = 40;

struct Player{int money, position; std::string name; bool in_prison, is_bot;};

struct Tile{int owner, houses, hotel, type; std::string name;};

int run_game(int, std::vector<Player>, Tile[], int, std::vector<std::string>);

#endif