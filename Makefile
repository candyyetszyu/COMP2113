FLAGS = -pedantic-errors -std=c++11

game.o: game.cpp game.h
	g++ $(FLAGS) -c $<

main.o: main.cpp game.h
	g++ $(FLAGS) -c $<

main: main.o game.o
	g++ $(FLAGS) $^ -o $@