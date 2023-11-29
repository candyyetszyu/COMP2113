FLAGS = -pedantic-errors -std=c++11

game.o: game.cpp game.h rules.h initialise_tiles.h
	g++ $(FLAGS) -c $<

main.o: main.cpp game.h
	g++ $(FLAGS) -c $<

rules.o: rules.cpp rules.h
	g++ $(FLAGS) -c $<

initialise_tiles.o: initialise_tiles.cpp initialise_tiles.h game.h
	g++ $(FLAGS) -c $<

board.o: board.cpp board.h
	g++ $(FLAGS) -c $<

main: main.o game.o initialise_tiles.o board.o rules.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f *.o main

.PHONY:
	clean