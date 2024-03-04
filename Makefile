# Makefile for Othello Game Playing HW2 - CSCI 561

BUILDDIR = build 
SRCDIR = src
INCLUDEDIR = include
CC = g++
CFLAGS = -Wall -g -I $(INCLUDEDIR) -std=c++17

all: build/main.o build/board.o build/check_board_utility.o build/flip_board_utility.o build/evaluate_board.o build/minimax.o build/minimax_ab.o | $(BUILDDIR)
	$(CC) $(CFLAGS) -o main-othello-game $^

build/main.o: $(SRCDIR)/homework.cpp | $(BUILDDIR)	
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


clean: 
	rm build/*.o

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

