#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "board.h"

using namespace std;

void PrintBoard(vector<player> x){
    cout << "|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|" << endl;
    cout << "|    Free    |   Lei Yue  |            |    Wong    |   Kowloon  |  Kowloon   |    Kwun    |            |   Water    |  Tsim Sha  |            |" << endl;
    cout << "|  Parking   |     Mun    | Provincial |  Tai Sin   |    Tong    |  station   |    Tong    |  Mong Kok  |   Works    |    Tsui    | Go to Jail |" << endl;
    cout << "|            |            |            |            |            |            |            |            |            |            |            |" << endl;
    cout << "|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|" << endl;
    cout << "|   Tseung   |                                                                                                                    |  Causeway  |" << endl;
    cout << "|   Kwan O   |                                                                                                                    |     Bay    |" << endl;
    cout << "|            |                                                                                                                    |            |" << endl;
    cout << "|------------|                                                                                                                    |------------|" << endl;
    cout << "|            |                                                                                                                    |            |" << endl;
    cout << "|  Sha Tin   |                                                                                                                    | Cyberport  |" << endl;
    cout << "|            |                                                                                                                    |            |" << endl;
    cout << "|------------|                                                                                                                    |------------|" << endl;
    cout << "|            |                                                                                                                    |            |" << endl;
    cout << "| Community  |                                                                                                                    |  Community |" << endl;
    cout << "|   Chest    |                                                                                                                    |    Chest   |" << endl;
    cout << "|------------|                                                                                                                    |------------|" << endl;
    cout << "|            |                                                                                                                    |            |" << endl;
    cout << "|    Kwai    |                                                                                                                    |   Central  |" << endl;
    cout << "|   Chung    |                                                                                                                    |            |" << endl;
    cout << "|------------|                                                                                                                    |------------|" << endl;
    cout << "|            |                                                                                                                    |            |" << endl;
    cout << "|  Tsing Yi  |                                                                                                                    |  Hong Kong |" << endl;
    cout << "|  station   |                                                                                                                    |   statoin  |" << endl;
    cout << "|------------|                                                                                                                    |------------|" << endl;
    cout << "|            |                                                                                                                    |            |" << endl;
    cout << "|   Sham     |                                                                                                                    |   Chance   |" << endl;
    cout << "|   Tseng    |                                                                                                                    |            |" << endl;
    cout << "|------------|                                                                                                                    |------------|" << endl;
    cout << "|            |                                                                                                                    |            |" << endl;
    cout << "|  Tin Shui  |                                                                                                                    |   Repulse  |" << endl;
    cout << "|    Wai     |                                                                                                                    |     Bay    |" << endl;
    cout << "|------------|                                                                                                                    |------------|" << endl;
    cout << "|            |                                                                                                                    |            |" << endl;
    cout << "|  Hongkong  |                                                                                                                    | Salary Tax |" << endl;
    cout << "|  Electric  |                                                                                                                    |            |" << endl;
    cout << "|------------|                                                                                                                    |------------|" << endl;
    cout << "|            |                                                                                                                    |            |" << endl;
    cout << "|   Lo Wu    |                                                                                                                    |  The Peak  |" << endl;
    cout << "|            |                                                                                                                    |            |" << endl;
    cout << "|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|" << endl;
    cout << "|            |            |            |            |            |            |            |            |            |            |            |" << endl;
    cout << "|    Jail    |    Lamma   |   Cheung   |   Chance   |    Ngong   |  Airport   |   Income   |   Lantau   |  Community |  Chek Lap  |     Go     |" << endl;
    cout << "|            |   Island   |    Chau    |            |    Ping    |  station   |    Tax     |   Island   |    Chest   |     Kok    |            |" << endl;
    cout << "|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|" << endl;
}
