#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include<algorithm>

#include "rules.h"
#include "board.h"
#include "initalised_tiles.h"

using namespace std;

bool Player::change(int amount){
	// int amount: positive when player receives money, negative when player loses money
	// returns true when succeed, false when fail
	money += amount;
	if (money < 0){
		cout << name << " has run out of funds."
		// TODO: add mortgage handling
	}
	return true;
}

ChanceCard DrawChanceCard(vector<ChanceCard>& chance_card) {
    int randomIndex = rand() % chance_card.size();
    return chance_card[randomIndex];
}

void apply_chance_card_effect(Player& player, const ChanceCard& card, Tile tiles[], int free_parking, vector<Player>& players) {
    switch (card.type) {
        case ChanceCardType::AdvanceToGo:
            cout << player.name << " advances to GO and collects $500." << endl;
            player.position = 0; // GO tile is always at index 0
            player.change(500);
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
            if (player.change(-200)){
	            for (auto& p : players) {
	                if (p.name != player.name) {
	                    p.change(200);
	                }
	            }
	        }
            break;

        case ChanceCardType::PayBank:
            cout << player.name << " has to pay the bank $500." << endl;
            if(player.change(-500)){

            }
            break;
    }
}

void Player::buyProperty(Tile& tile, int playerIndex) {
    if (tile.type != 4 && tile.type != 7 && tile.type != 8) {
        std::cout << "This tile is not buyable.\n";
        return;
    }
    if (tile.owner != -1) {
        std::cout << "This property is already owned by another player.\n";
        return;
    }
    if (money >= tile.price) {
        tile.owner = playerIndex;
        money -= tile.price;
    } else {
        std::cout << "Not enough money to buy this property.\n";
    }
}

void Player::sellProperty(Tile& tile) {
    if (tile.type != 4 && tile.type != 7 && tile.type != 8) {
        std::cout << "This tile is not sellable.\n";
        return;
    }
    if (tile.owner == position) {
        tile.owner = -1;
        money += tile.price / 2;
    } else {
        std::cout << "You don't own this property.\n";
    }
}

Game::Game(){
	//game initialisation for new game
	Player player;
    for (int i = 0; i < stoi(cmd); i++){
        player.name = "Player " + to_string(i);
        player.is_bot = i;  // results in is_bot = false only for the first player
        players.push_back(player);
    }
    initalised_tiles(tiles);
}

Game::Game(string filename){
	//load game from file
	// TODO
}

int Game::run(){
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
            	if (player.change(-fine)){
				    player.in_jail = false;
				    cout << player.name << " paid a fine of $" << fine << " and is released from jail." << endl;
				}
            } else {
                cout << players[i].name << " chose not to pay the fine and will remain in jail." << endl;
            }
        } else {
            // Ask the player if they want to sell any properties
            if (players[i].is_bot) {
                // Bot: sell a property if money is less than $500
                if (players[i].money < 500) {
                    for (int j = 0; j < tile_size; ++j) {
                        if (tiles[j].owner == i) {
                            players[i].sellProperty(tiles[j]);
                            break;
                        }
                    }
                }
            } else {
                std::string sell;
                std::cout << players[i].name << ", do you want to sell any properties? (yes/no)\n";
                std::cin >> sell;
                if (sell == "yes") {
                    int propertyIndex;
                    std::cout << "Enter the index of the property you want to sell:\n";
                    std::cin >> propertyIndex;
                    players[i].sellProperty(tiles[propertyIndex]);
                }
            }
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
                    // If the property is unowned, ask the player if they want to buy it
                    if (tiles[players[i].position].owner == -1) {
                        if (players[i].is_bot) {
                            // Bot: buy the property if money is more than $1000
                            if (players[i].money > 1000) {
                                players[i].buyProperty(tiles[players[i].position], i);
                            }
                        } else {
                        std::string buy;
                        std::cout << players[i].name << ", do you want to buy this property? (yes/no)\n";
                        std::cin >> buy;
                        if (buy == "yes") {
                            players[i].buyProperty(tiles[players[i].position], i);
                        }
                    }
                        // If the property is owned by another player, the current player must pay rent
                    else if (tiles[players[i].position].owner != i && tiles[players[i].position].owner != -1) {
                        // TODO: Implement rent payment
                    }
                    break;
                case 5: // go
                    cout << players[i].name << " passed or landed on Go and collected $200." << endl;
                    players[i].change(200);
                    break;
                case 6: // tax
                    cout << players[i].name << " paid $" << tiles[players[i].position].name << " tax!" << endl;
                    players[i].change(-atoi(tiles[players[i].position].name.c_str());)
                    break;
                case 7: // railroad
		    // Check if the railroad is owned by another player
		    if (tiles[players[i].position].owner != -1 && tiles[players[i].position].owner != i) {
		        // Calculate the rent based on the number of railroads owned by the owner
		        int numRailroads = 0;
		        for (int j = 0; j < tile_size; ++j) {
		            if (tiles[j].type == 7 && tiles[j].owner == tiles[players[i].position].owner) {
		                numRailroads++;
		            }
		        }
		        int rentAmount = railroad_rent[numRailroads - 1]; // Rent amount based on the number of railroads owned
		        cout << players[i].name << " paid $" << rentAmount << " as rent to " << players[tiles[players[i].position].owner].name << "." << endl;
		        players[i].change(-rentAmount);
		        players[tiles[players[i].position].owner].change(rentAmount);
		    }
		    // If the railroad is unowned, ask the player if they want to buy it
		    else if (tiles[players[i].position].owner == -1) {
		        if (players[i].is_bot) {
		            // Bot: buy the railroad if money is more than $1000
		            if (players[i].money > 1000) {
		                players[i].buyProperty(tiles[players[i].position], i);
		            }
		        } else {
		            std::string buy;
		            std::cout << players[i].name << ", do you want to buy this railroad? (yes/no)\n";
		            std::cin >> buy;
		            if (buy == "yes") {
		                players[i].buyProperty(tiles[players[i].position], i);
		            }
		        }
		    }
		    break;
		
		case 8: // utility
		    // Check if the utility is owned by another player
		    if (tiles[players[i].position].owner != -1 && tiles[players[i].position].owner != i) {
		        // Calculate the rent based on the roll of the dice
		        int diceSum = dice1 + dice2;
		        int rentAmount = (diceSum == 12) ? 10 * diceSum : 4 * diceSum; // Rent amount based on the roll of the dice
		        cout << players[i].name << " paid $" << rentAmount << " as rent to " << players[tiles[players[i].position].owner].name << "." << endl;
		        players[i].change(-rentAmount);
		        players[tiles[players[i].position].owner].change(rentAmount);
		    }
		    // If the utility is unowned, ask the player if they want to buy it
		    else if (tiles[players[i].position].owner == -1) {
		        if (players[i].is_bot) {
		            // Bot: buy the utility if money is more than $1000
		            if (players[i].money > 1000) {
		                players[i].buyProperty(tiles[players[i].position], i);
		            }
		        } else {
		            std::string buy;
		            std::cout << players[i].name << ", do you want to buy this utility? (yes/no)\n";
		            std::cin >> buy;
		            if (buy == "yes") {
		                players[i].buyProperty(tiles[players[i].position], i);
		            }
		        }
		    }
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
	            } else if (cmd == "save"){
	            	cout << "Please input the file name to be saved:" << endl;
	            	string fn;
	            	cin >> fn;
	            	save(fn);
	            }
        	}

	        i = 0;
        } else {
            i++;
        }
    }
}

bool Game::save(string filename){
	// saves the game to filename
	// TODO:
}
