FLAGS = -pedantic-errors -std=c++11

game.o: game.cpp game.h rules.h
	g++ $(FLAGS) -c $<

main.o: main.cpp game.h rules.h
	g++ $(FLAGS) -c $<

rules.o: rules.cpp rules.h
	g++ $(FLAGS) -c $<

initalised_tiles.o: initalised_tiles.cpp initalised_tiles.h game.h
	g++ $(FLAGS) -c $<

main: main.o game.o rules.o initalised_tiles.o
	g++ $(FLAGS) $^ -o $@