# Monopoly - Hong Kong Version
Welcome to our game, Monopoly - Hong Kong Version!
This is a real-estate board game.

Your goal is to remain financially solvent by buying and developing pieces of property while other opponents have to get eliminated before you lose all of your money. The last player left in that trial is the winner.

In this game, we will use different districts in Hong Kong to replace the traditional game board. They can be Mong Kok, Tsim Sha Tsui, Central, Sha Tin, etc.

On the other hand, we add several game systems to diversify the game, like free parking, jail, chance cards/ community chests, and more! They can affect players' moves in numerous ways. Therefore, players have to pay attention to the decisions of other opponents.

Monopoly - Hong Kong Version is based on C++ programming, and we used dynamic memory management, data structures, randomness, and so on to run the program so that it is fair to all players!

Get ready and hop into the game to eliminate the opponents, good luck!

-----------------------------------------------------------------------------------------------------------------------------------

# Monopoly - Hong Kong Version Rules

1. The game is played on a square board divided into 40 tiles.

2. Each player starts with a set amount of money and a token on the 'GO' space.

3. Players take turns in clockwise order.

4. Roll two six-sided dice and move your token clockwise around the board. If you roll doubles, you roll again and take another turn.

5. Depending on the space you land on, you can buy properties, pay rent, draw cards, etc.

6. If you land on an unowned property, you can choose to buy it or not.

7. If you own the property, you can build houses and hotels on them when you land on it again.

8. If you land on a property owned by another player, you must pay them rent.

9. If you land on certain spaces, you may draw a Chance card.

10. The game continues until all but one player goes bankrupt.

11. The last remaining player is declared the winner of the game.

You can always check the game rules with the command "rules" again during the trial!

-----------------------------------------------------------------------------------------------------------------------------------

# Team member list for Monopoly - Hong Kong Version

1. Chan Pui Wai Wesley (3035922702) [wesleychan2010]

2. Chuang Chun Ki (3035936882) [KimChuang]

3. Ku Chung Yiu (3036101434) [ChungTau0222]

4. Ye Tsz Yu (3036075702) [candyyetszyu]

5. Yeung Yui Sze (3035667390) [raissayeung]

-----------------------------------------------------------------------------------------------------------------------------------

# Feature List

Element 1. Generation of random game sets or events

We use random number generation (RNG) for our game such as the outcome of rolling dice, the effects from chance card/community chest card, and so on.

Element 2. Data structures for storing game status

We implement data structures into arrays in our game, such as using an array of tiles for the game board for saving the details of the properties of each tile.

Element 3. Dynamic memory management

We store players in a vector which has a dynamic length based on user input.

Element 4. File input/output

Players can save the game data during the game. The game resumes when the player loads the game.

Element 5. Program codes in multiple files

We created different header files and source files to separate the code so that we could organise and compile the game in a better way. On the other hand, we also use Makefile in our game which can connect the dependencies of the header files and source files and run the program after the player types "make main" and "./main" to start Monopoly - Hong Kong Version.

-----------------------------------------------------------------------------------------------------------------------------------

# How to start our game

Please run the following commands in this order:
1. `make main`
2. `./main`

-----------------------------------------------------------------------------------------------------------------------------------

# Demo Video Link

Link: https://drive.google.com/file/d/1Sk2QMl5XVx6WuqjQrVA2A6i_HVC31JFm/view?usp=drive_link
