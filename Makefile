# Makefile for Othello Game Playing HW2 - CSCI 561

BUILDDIR = build 
SRCDIR = src
INCLUDEDIR = include
CC = g++
CFLAGS = -Wall -g -I $(INCLUDEDIR) -std=c++17

all: build/main.o build/board.o build/check_board_utility.o build/flip_board_utility.o build/evaluate_board.o build/minimax.o build/minimax_ab.o build/game_partition.o | $(BUILDDIR)
	$(CC) $(CFLAGS) -o main-othello-game $^

build/main.o: homework.cpp | $(BUILDDIR)	
	$(CC) $(CFLAGS) -c $< -o $@

build/board.o: $(SRCDIR)/board.cpp $(INCLUDEDIR)/board.h $(INCLUDEDIR)/tile.h $(INCLUDEDIR)/move.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

build/check_board_utility.o: $(SRCDIR)/check_board_utility.cpp $(INCLUDEDIR)/check_board_utility.h
	$(CC) $(CFLAGS) -c $< -o $@

build/flip_board_utility.o: $(SRCDIR)/flip_board_utility.cpp $(INCLUDEDIR)/flip_board_utility.h
	$(CC) $(CFLAGS) -c $< -o $@

build/evaluate_board.o: $(SRCDIR)/evaluate_board.cpp $(INCLUDEDIR)/eval_board.h 
	$(CC) $(CFLAGS) -c $< -o $@

build/minimax.o: $(SRCDIR)/minimax.cpp $(INCLUDEDIR)/eval_board.h 
	$(CC) $(CFLAGS) -c $< -o $@

build/minimax_ab.o: $(SRCDIR)/minimax_ab.cpp $(INCLUDEDIR)/eval_board.h  
	$(CC) $(CFLAGS) -c $< -o $@

# SIMULATION 

simulation: build/simulation_main.o build/board.o build/check_board_utility.o build/flip_board_utility.o build/play_game_sim.o build/player.o build/serialize.o build/game_partition.o build/evaluate_board.o build/minimax.o
	$(CC) $(CFLAGS) -o main-othello-simulation $^ -lcurl

build/simulation_main.o: $(SRCDIR)/simulation/simulation_main.cpp 
	$(CC) $(CFLAGS) -c $< -o $@ 

build/play_game_sim.o: $(SRCDIR)/simulation/play_game.cpp $(INCLUDEDIR)/simulation/simulation.h
	$(CC) $(CFLAGS) -c $< -o $@ 

build/game_partition.o: $(SRCDIR)/game_partition.cpp $(INCLUDEDIR)/evaluate/game_partition.h
	$(CC) $(CFLAGS) -c $< -o $@ 


build/player.o: $(SRCDIR)/simulation/player.cpp $(INCLUDEDIR)/simulation/player.h
	$(CC) $(CFLAGS) -c $< -o $@ 

build/serialize.o: $(SRCDIR)/simulation/serialize.cpp $(INCLUDEDIR)/simulation/simulation.h
	$(CC) $(CFLAGS) -c $< -o $@ 

# TEST SIMULATION 
test_simulation: build/test_simulation.o build/board.o build/check_board_utility.o build/flip_board_utility.o build/play_game_sim.o build/player.o build/serialize.o build/game_partition.o
	$(CC) $(CFLAGS) -o main-othello-test-simulation $^ -lcurl

build/test_simulation.o: $(SRCDIR)/simulation/test_sim.cpp
	$(CC) $(CFLAGS) -c $< -o $@ 



clean: 
	rm build/*.o

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

