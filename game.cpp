#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
#include <algorithm>
#include <random>

#include "rules.h"
#include "board.h"
#include "initialise_tiles.h"

using namespace std;

void Player::mortgageProperty(Tile& tile) {
    if (tile.owner != index) {
        std::cout << "";
        return;
    }
    if (tile.isMortgaged) {
        std::cout << "This property is already mortgaged.\n";
        return;
    }
    tile.isMortgaged = true;
    money += tile.price / 2; // The mortgage amount is half the property price
    std::cout << name << " mortgaged " << tile.name << " for $" << tile.price / 2 << ".\n";
}

void Player::unmortgageProperty(Tile& tile) {
    // Check if the tile is a property
    if (tile.type != 4) {
        std::cout << "This tile is not a property.\n";
        return;
    }

    // Check if the property is owned by the current player
    if (tile.owner != index) {
        std::cout << "You do not own this property.\n";
        return;
    }

    // Check if the property is currently mortgaged
    if (!tile.isMortgaged) {
        std::cout << "This property is not currently mortgaged.\n";
        return;
    }

    // Calculate the mortgage amount (mortgage is 50% of the property price)
    int mortgageAmount = tile.price / 2;

    // Check if the player has enough money to pay the mortgage
    if (money < mortgageAmount) {
        std::cout << "You don't have enough money to unmortgage this property.\n";
        return;
    }

    // Deduct the mortgage amount from the player's money
    money -= mortgageAmount;

    // Change the property's status to unmortgaged
    tile.isMortgaged = false;

    // Print a message indicating the property has been unmortgaged
    std::cout << name << " unmortgaged " << tile.name << " for $" << mortgageAmount << ".\n";
}

void Game::Bankrupt(Player& player) {
    if (!player.is_bot) {
        std::cout << "You've lost. Game over.\n";
        exit(0); // Exit the program
        return;
    } else {
        std::cout << "The game is over for " << player.name << ".\n";
    }

    // Transfer all of the player's properties to the bank and unmortgage them
    for (Tile& tile : tiles) {
        if (players[tile.owner].name == player.name) {
            tile.owner = -1;
            tile.isMortgaged = false;
            std::cout << "The property " << tile.name << " has been returned to the bank.\n";
        }
    }

    // Count remaining players
    int playersRemaining = 0;
    for (Player& player : players) {
        if (player.money > 0) {
            playersRemaining++;
        }
    }

    // If there's only human player left, they win
    if (playersRemaining == 1) {
        for (Player& player : players) {
            if (player.money > 0) {
                std::cout << "Congratulations, " << player.name << "! You are the winner!\n";
            }
        }
    } else {
        // If there are more than one players left, the game continues
        std::cout << "There are " << playersRemaining << " players remaining. The game continues.\n";
    }

    // Remove this player from the game
    player.money = 0;
    std::cout << player.name << " has been removed from the game.\n";
}

bool Game::change_amount(int amount, Player& player){
	// int amount: positive when player receives money, negative when player loses money
	// returns true when succeed, false when fail
	player.money += amount;
	if (player.money < 0){
		cout << player.name << " has run out of funds.";
        // Sell the player's hotels one by one until they have enough money
        for (Tile& tile : tiles) {
            if (players[tile.owner].name == player.name && tile.hotels > 0) {
                sellHotel(tile, player);
                if (player.money >= 0) {
                    break;
                }
            }
        }
        // Sell the player's houses one by one until they have enough money
        for (Tile& tile : tiles) {
            if (players[tile.owner].name == player.name && tile.houses > 0) {
                sellHouse(tile, player);
                if (player.money >= 0) {
                    break;
                }
            }
        }
        // Mortgage the player's properties one by one until they have enough money
        for (Tile& tile : tiles) {
            if (players[tile.owner].name == player.name && !tile.isMortgaged) {
                player.mortgageProperty(tile);
                if (player.money >= 0) {
                    break;
                }
            }
        }
        if (player.money < 0) {
            cout << player.name << " is still out of funds after mortgaging all properties. Game over for " << player.name << ".\n";
            Bankrupt(player);
            return false;
        }
    }
	return true;
}

void Game::payRent(Player& player, Tile& tile) {
    // Check if the tile is a property
    if (tile.type != 4 && tile.type != 7 && tile.type != 8) {
        std::cout << "This tile is not a property.\n";
        return;
    }

    // Check if the property is owned by another player
    if (tile.owner == -1 || tile.owner == player.index) {
        std::cout << "This property is not owned by another player.\n";
        return;
    }

    // Calculate the base rent amount
    int rentAmount = tile.price / 10; // Base rent is 10% of the property price

    // Increase the rent amount based on the number of houses and hotels
    rentAmount += tile.houses * 50; // Each house increases the rent by $500
    rentAmount += tile.hotels * 100; // Each hotel increases the rent by $1000

    // Deduct the rent amount from the player's money
    if (!change_amount(-rentAmount, player)) {
        std::cout << player.name << " doesn't have enough money to pay the rent.\n";
        return;
    }

    // Add the rent amount to the owner's money
    change_amount(rentAmount, players[tile.owner]);

    std::cout << player.name << " paid " << rentAmount << " to " << players[tile.owner].name << ".\n";
}

// Define the Chance cards
vector<ChanceCard> chanceCards = {
    { ChanceCardType::AdvanceToGo, "Advance to Go" },
    { ChanceCardType::GoBackThreeSpaces, "Go back three spaces" },
    { ChanceCardType::GoToJail, "Go to jail" },
    { ChanceCardType::PayEveryone, "Pay everyone" },
    { ChanceCardType::PayBank, "Pay the bank" }
};

ChanceCard DrawChanceCard(vector<ChanceCard>& chanceCards) {
    int randomIndex = rand() % chanceCards.size();
    return chanceCards[randomIndex];
}


void Game::apply_chance_card_effect(Player& player, const ChanceCard& card) {
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
            cout << player.name << " has to pay everyone $2000." << endl;
            if (change_amount(-200, player)){
	            for (auto& p : players) {
	                if (p.name != player.name) {
	                    p.money += 200;
	                }
	            }
	        }
            break;

        case ChanceCardType::PayBank:
            cout << player.name << " has to pay the bank $500." << endl;
            if(change_amount(-500, player)){

            }
            break;
    }
}

// Function to draw a Community Chest card randomly
CommunityChestCard DrawCommunityChestCard(vector<CommunityChestCard>& communityChestCards) {
    int randomIndex = rand() % communityChestCards.size();
    return communityChestCards[randomIndex];
}

// Apply the effect of the Community Chest card
void Game::apply_community_chest_card_effect(Player& player, const CommunityChestCard& card) {
    switch (card.type) {
        case CommunityChestCardType::AdvanceToGo:
            cout << player.name << " advanced to Go." << endl;
            player.position = 0; // Move player to Go space
            break;

        case CommunityChestCardType::FoundMoney:
            player.money += 100;
            cout << player.name << " found money on the floor and received $100." << endl;
            break;

        case CommunityChestCardType::GoToJail:
            cout << player.name << " went directly to Jail." << endl;
            player.position = 10; // Move player to Jail space
            player.in_jail = true; // Set player in_jail flag to true
            break;

        case CommunityChestCardType::PayHospitalFees:
            player.money -= 100;
            cout << player.name << " paid $100 as hospital fees." << endl;
            break;

        case CommunityChestCardType::ConsumptionVoucher:
            player.money += 100;
            cout << player.name << " received $100 as a consumption voucher." << endl;
            break;

        case CommunityChestCardType::ChineseNewYear:
            for (auto& p : players) {
                if (p.name != player.name) {
                    p.money -= 20;
                    player.money += 20;
                }
            }
            cout << player.name << " collected $20 from each player as Chinese New Year red pocket money." << endl;
            break;
    }
}

// Define the Community Chest card stack
vector<CommunityChestCard> communityChestCards = {
    { CommunityChestCardType::AdvanceToGo, "Advance to Go" },
    { CommunityChestCardType::FoundMoney, "Found money on the floor - Collect $100" },
    { CommunityChestCardType::GoToJail, "Go directly to Jail" },
    { CommunityChestCardType::PayHospitalFees, "Pay hospital fees of $100" },
    { CommunityChestCardType::ConsumptionVoucher, "Consumption Voucher - Collect $100" },
    { CommunityChestCardType::ChineseNewYear, "It's Chinese New Year - Collect $20 from each player" }
};

void Player::buyProperty(Tile& tile) {
    if (tile.type != 4 && tile.type != 7 && tile.type != 8) {
        std::cout << "This tile is not buyable.\n";
        return;
    }
    if (tile.owner != -1) {
        std::cout << "This property is already owned by another player.\n";
        return;
    }
    if (money >= tile.price) {
        tile.owner = index;
        money -= tile.price;
        cout << name << " bought " << tile.name << endl;
    } else {
        std::cout << "Not enough money to buy this property.\n";
    }
}

void Player::sellProperty(Tile& tile) {
    if (tile.type != 4 && tile.type != 7 && tile.type != 8) {
        std::cout << "This tile is not sellable.\n";
        return;
    }
    if (tile.owner == index) {
        tile.owner = -1;
        money += tile.price / 2;
        cout << name << " sold " << tile.name << endl;
    } else {
        std::cout << "You don't own this property.\n";
    }
}

void Game::buyHouse(Tile& tile, Player& player) {
	if (tile.type != 4||tile.owner != player.index) {
        if (!player.is_bot){
		  std::cout << "You cannot buy houses here.\n";
        }
		return;
	}
	if (tile.owner == player.index) {
		int color_sum=0, houses_num_of_same_color=0, num_of_tiles = (tile.group == 1 ||tile.group == 8) ? 2 : 3;

		for (int i=0; i<39; i++){
			if (tiles[i].owner == tile.owner && tiles[i].group==tile.group){
				color_sum+=1; //detect whether players hv all property of the group
                houses_num_of_same_color += tiles[i].houses;
			}
		}
        if (color_sum != num_of_tiles){
            if (!player.is_bot){
                cout << "You cannot buy houses here until you own all property with the same colour" << endl;
            }
            return;
        }
        if (houses_num_of_same_color < tile.houses * num_of_tiles){
            // number of houses is not saturated
            if (!player.is_bot){
                cout << "You cannot buy houses here until all properties have " << tile.houses << "house" << ((tile.houses == 1) ? "": "s") << "each" << endl;
            }
            return;
		}

        if (tile.houses>=4){
            if (!player.is_bot){
                std::cout << "You can't build more than 4 houses on the same property, please consider upgrade houses to hotel.\n";
            }
            return;
        }
        if (player.money>(tile.houses+1)*50){
            player.money -= (tile.houses+1)*50;
            tile.houses += 1;
        }
	}
}

void Game::buyHotel(Tile& tile, Player& player) {
	if (tile.type != 4||tile.owner != player.index) {
        if (!player.is_bot){
            std::cout << "You cannot buy hotels here.\n";
        }
		return;
	}
	if (tile.owner == player.index) {
		int color_sum=0, four_houses_of_each=0, num_of_tiles = (tile.group == 1 ||tile.group == 8) ? 2 : 3;
		for (int i=0; i<39; i++){
			if (tiles[i].owner == tile.owner && tiles[i].group==tile.group){
				color_sum+=1; //implement: check whether players hv houses at the property of the group
			}
			if (tiles[i].owner == tile.owner && tiles[i].houses==4){
				//check whether players have built four houses on each property
				four_houses_of_each+=1;
			}
		}
        if (color_sum != num_of_tiles){
            if (!player.is_bot){
                cout << "You cannot buy houses here until you own all property with the same colour." << endl;
            }
            return;
        }
        if (four_houses_of_each != num_of_tiles){
            if (!player.is_bot){
			    std::cout << "You cannot buy hotel here until you have built four houses on every property of the group.\n";
            }
			return;
		}
		if (tile.hotels==1){
            if (!player.is_bot){
			    std::cout << "You cannot buy more than one hotel on every property of the group.\n";
            }
			return;
		}
		if (player.money>=50){
			tile.hotels = 1;
			tile.houses = 0;
			player.money -= 50;
		}
	}
}

void Game::sellHouse(Tile& tile, Player& player) {
    if (tile.type != 4 || tile.owner != player.index) {
        if (!player.is_bot){
            std::cout << "You cannot sell houses here.\n";
        }
        return;
    }
    if (tile.owner == player.index && tile.houses > 0) {
        int houseCost = 0;
        switch (tile.houses) {
            case 1: houseCost = 50; break;
            case 2: houseCost = 100; break;
            case 3: houseCost = 150; break;
            case 4: houseCost = 200; break;
        }
        tile.houses -= 1;
        player.money += houseCost / 2;  // Player gets half the cost back
        std::cout << player.name << "sells house on " <<  tile.name << ".\n";
    } else {
        std::cout << "No houses to sell on this property.\n";
    }
}

void Game::sellHotel(Tile& tile, Player& player) {
    if (tile.type != 4 || tile.owner != player.index) {
        if (!player.is_bot){
            std::cout << "You cannot sell hotels here.\n";
        }
        return;
    }
    if (tile.owner == player.index && tile.hotels > 0) {
        int hotelCost = 50;
        tile.hotels -= 1;
        player.money += hotelCost / 2;  // Player gets half the cost back
        std::cout << player.name << "sells hotel on " <<  tile.name << ".\n";
    } else {
        if (!player.is_bot){
            std::cout << "No hotels to sell on this property.\n";
        }
    }
}

Game::Game(int number_of_players){
	//game initialisation for new game
	bad_load = false;

	Player player;
    for (int i = 0; i < number_of_players; i++){
    	if (i){
        	player.name = "Player " + to_string(i);
        } else {
        	string cmd;
	        cout << "What is your name?" << endl;
	        cin >> cmd;
	        player.name = cmd;
        }
        player.money = 1500;
        player.index = i;
        player.is_bot = i;  // results in is_bot = false only for the first player
        players.push_back(player);
    }

    initialise_tiles(tiles);
    n = number_of_players;
}

Game::Game(string filename){
	// load game from file
	ifstream fin;
	fin.open(filename);
	bad_load = false;

	try{
		string word, w;
		getline(fin, word); n = stoi(word);
		Player player;
		for (int i=0; i<n; i++){
			getline(fin, word);
			istringstream iss(word);
			iss >> w; player.money = stoi(w);
			iss >> w; player.position = stoi(w);
			iss >> w; player.in_jail = stoi(w);
			iss >> w; player.is_bot = stoi(w);
			getline(iss, w); player.name = w;
            player.index = i;
			players.push_back(player);
		}

		for (int i=0; i<40; i++){
			getline(fin, word);
			istringstream iss(word);
			iss >> w; tiles[i].owner = stoi(w);
			iss >> w; tiles[i].houses = stoi(w);
			iss >> w; tiles[i].hotels = stoi(w);
			iss >> w; tiles[i].type = stoi(w);
			iss >> w; tiles[i].price = stoi(w);
			iss >> w; tiles[i].group = stoi(w);
			getline(iss, w); tiles[i].name = w;
		}
	} catch (...){
		cout << "Error in loading game." << endl;
		bad_load = true;
	}
}

int Game::run(){
	if (bad_load){
		return 0;
	}

    int i = 0;
    string cmd = "";

    // shuffle the chance card stack and community chest card stack before starting the game
    std::shuffle(chanceCards.begin(), chanceCards.end(), std::default_random_engine(std::random_device()()));

    // shuffle the commmunity chest card stack and community chest card stack before starting the game
    std::shuffle(communityChestCards.begin(), communityChestCards.end(), std::default_random_engine(std::random_device()()));


    PrintBoard(players, tiles);

    while (true) {
        if (players[i].in_jail) {
            string choice;
            // Player is in jail
            cout << players[i].name << " is in jail and must wait for their next turn." << endl;
            if (!players[i].is_bot){
                cout << "Do you want to pay the $100 fine to be released immediately? (yes/no)" << endl;
                cin >> choice;
            } else {
                choice = (players[i].money > 500)? "yes": "no" ;
            }
            if (choice == "yes") {
            	if (change_amount(-100, players[i])){
				    players[i].in_jail = false;
				    cout << players[i].name << " paid a fine of $100 and is released from jail." << endl;
				}
            } else {
                cout << players[i].name << " chose not to pay the fine and will remain in jail." << endl;
            }
        } else {
            // roll dice
            int dice1 = rand() % 6 + 1;
            int dice2 = rand() % 6 + 1;
            cout << players[i].name << " rolled " << dice1 << " and " << dice2 << " on the dice." << endl;

            // move player position
            players[i].position = (players[i].position + dice1 + dice2);
            if (players[i].position >= tile_size){
            	players[i].position -= tile_size;
            	cout << players[i].name << " passed or landed on Go and collected $200." << endl;
                players[i].money += 200;
            }
            cout << players[i].name << " moved to " << tiles[players[i].position].name << "." << endl;

            // handle actions with tiles
            switch (tiles[players[i].position].type) {
                case 0: // chance
                    cout << players[i].name << " got a chance card!" << endl;

                    // apply chance card effect if available
            	    if (!chanceCards.empty()) {
        			    ChanceCard card = DrawChanceCard(chanceCards);
        			    apply_chance_card_effect(players[i], card);}
        			else {
        			    cout << "No more Chance cards left." << endl;
        			}
                    break;
                case 1: // community chest
        		    cout << players[i].name << " drew a Community Chest card." << endl;
        		    
                    // apply community chest card effect if available
                    if (!communityChestCards.empty()) {
                        CommunityChestCard card = DrawCommunityChestCard(communityChestCards);
                        apply_community_chest_card_effect(players[i], card);}
                    else {
                        cout << "No more Community Chest cards left." << endl;
                    }
        		    break;
                case 2: // go to jail
                    cout << players[i].name << " went to jail!" << endl;
                    players[i].position = 10; // Go to Jail tile
                    players[i].in_jail = true; // Set the player in jail
                    break;
                case 3: // free parking
                    // Nothing happens, player's turn ends.
                    break;
                case 4: // property
                    // If the property is unowned, ask the player if they want to buy it
                    if (tiles[players[i].position].owner == -1) {
                        if (players[i].is_bot) {
                            // Bot: buy the property if money is more than $1000
                            if (players[i].money > 1000) {
                                players[i].buyProperty(tiles[players[i].position]);
                            }
                        } else {
	                        std::string buy;
	                        std::cout << players[i].name << ", do you want to buy this property? (yes/no)\n";
	                        std::cin >> buy;
	                        if (buy == "yes") {
	                            players[i].buyProperty(tiles[players[i].position]);
	                        }
	                    }
                    }
                        // If the property is owned by another player, the current player must pay rent
                    else if (tiles[players[i].position].owner != i && tiles[players[i].position].owner != -1) {
                        payRent(players[i], tiles[players[i].position]);
                    }
                    break;
                case 5: // go
                    break;
                case 6: // tax
                    cout << players[i].name << " paid $" << tiles[players[i].position].price << " tax!" << endl;
                    change_amount(-tiles[players[i].position].price, players[i]);
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
                        int rentAmount = 50 * numRailroads ; // Rent amount based on the number of railroads owned
        		        cout << players[i].name << " paid $" << rentAmount << " as rent to " << players[tiles[players[i].position].owner].name << "." << endl;
        		        change_amount(-rentAmount, players[i]);
        		        change_amount(rentAmount, players[tiles[players[i].position].owner]);
        		    }
        		    // If the railroad is unowned, ask the player if they want to buy it
        		    else if (tiles[players[i].position].owner == -1) {
        		        if (players[i].is_bot) {
        		            // Bot: buy the railroad if money is more than $1000
        		            if (players[i].money > 1000) {
        		                players[i].buyProperty(tiles[players[i].position]);
        		            }
        		        } else {
        		            std::string buy;
        		            std::cout << players[i].name << ", do you want to buy this railroad? (yes/no)\n";
        		            std::cin >> buy;
        		            if (buy == "yes") {
        		                players[i].buyProperty(tiles[players[i].position]);
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
		        change_amount(-rentAmount, players[i]);
		        change_amount(rentAmount, players[tiles[players[i].position].owner]);
		    }
		    // If the utility is unowned, ask the player if they want to buy it
		    else if (tiles[players[i].position].owner == -1) {
		        if (players[i].is_bot) {
		            // Bot: buy the utility if money is more than $1000
		            if (players[i].money > 1000) {
		                players[i].buyProperty(tiles[players[i].position]);
		            }
		        } else {
		            std::string buy;
		            std::cout << players[i].name << ", do you want to buy this utility? (yes/no)\n";
		            std::cin >> buy;
		            if (buy == "yes") {
		                players[i].buyProperty(tiles[players[i].position]);
		            }
		        }
		    }
		    break;
            }
        }

        PrintBoard(players, tiles);
        // Ask the player if they want to unmortgage any properties
        if (players[i].is_bot) {
            // Bot: unmortgage a property if money is more than $1000
            if (players[i].money > 1000) {
                for (int j = 0; j < tile_size; ++j) {
                    if (tiles[j].owner == i && tiles[j].isMortgaged) {
                        players[i].unmortgageProperty(tiles[j]);
                        break;
                    }
                }
            }
        } else {
            std::string unmortgage;
            std::cout << players[i].name << ", do you want to unmortgage any properties? (yes/no)\n";
            std::cin >> unmortgage;
            if (unmortgage == "yes") {
                int propertyIndex;
                std::cout << "Enter the index of the property you want to unmortgage:\n";
                std::cin >> propertyIndex;
                players[i].unmortgageProperty(tiles[propertyIndex]);
            }
        }
        // Ask the player if they want to sell any properties or buy/sell houses/hotels
        if (players[i].is_bot) {
            if (players[i].money < 500) {
                // Bot: sell a property or a house/hotel if it owns any
                for (int j = 0; j < tile_size; ++j) {
                    if (tiles[j].owner == i) {
                        if (tiles[j].houses > 0) {
                            sellHouse(tiles[j], players[i]);
                            break;
                        } else if (tiles[j].hotels > 0) {
                            sellHotel(tiles[j], players[i]);
                            break;
                        } else {
                            players[i].sellProperty(tiles[j]);
                            break;
                        }
                    }
                }
            } else if (players[i].money > 1000) {
                // Bot: buy a house/hotel on a property it owns
                for (int j = 0; j < tile_size; ++j) {
                    if (tiles[j].owner == i) {
                        if (tiles[j].houses < 4) {
                            buyHouse(tiles[j], players[i]);
                            break;
                        } else if (tiles[j].houses == 4 && tiles[j].hotels == 0) {
                            buyHotel(tiles[j], players[i]);
                            break;
                        }
                    }
                }
            }
        } else {
            std::string action;
            std::cout << players[i].name << ", do you want to sell any properties, or buy/sell houses or hotels? (yes/no)\n";
            std::cin >> action;
            if (action == "yes") {
                std::cout << "Please enter your action: (sell_property/buy_house/buy_hotel/sell_house/sell_hotel)\n";
                std::cin >> action;
                int propertyIndex;
                std::cout << "Enter the index of the property: (Go is 0, Jail is 10, Free Parking is 20, Go to Jail is 30)\n";
                std::cin >> propertyIndex;
                if (action == "sell_property") {
                    players[i].sellProperty(tiles[propertyIndex]);
                } else if (action == "buy_house") {
                    buyHouse(tiles[propertyIndex], players[i]);
                } else if (action == "buy_hotel") {
                    buyHotel(tiles[propertyIndex], players[i]);
                } else if (action == "sell_house") {
                    sellHouse(tiles[propertyIndex], players[i]);
                } else if (action == "sell_hotel") {
                    sellHotel(tiles[propertyIndex], players[i]);
                }
            }
        }

        if (i + 1 == n) {
            // end round
            while (true){
            	cout << "Enter command: quit/next/rules/save:" << endl;
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

void Game::save(string filename){
	// saves the game to filename
	ofstream fout;
	fout.open(filename);

	if (fout.fail()){
		cout << "error in saving game" << endl;
	}

	fout << n << endl;

	// save data of players
	vector<Player>::iterator ip;
	for (ip = players.begin(); ip != players.end(); ip++){
		fout << ip->money << " " << ip->position << " " << int(ip->in_jail) << " " << int(ip->is_bot) << " " << ip->name << endl;
	}

	// save data of tiles
	for (int i=0; i < tile_size; i++){
		fout << tiles[i].owner << " " << tiles[i].houses << " " << tiles[i].hotels << " " << tiles[i].type << " " << tiles[i].price << " " << tiles[i].group << " " << tiles[i].name << endl;
	}
	fout.close();
}
