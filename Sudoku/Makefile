#
# Makefile for CS 2620 Assignment 2
#
# Author: Howard Cheng
# Oct 10, 2007
#

# some settings
CXX=g++
#CXX=/opt/centos/devtoolset-1.1/root/usr/bin/g++11
CXXFLAGS=-Wall -g -std=c++11

all: Sudoku

Sudoku: sudoku.o sudokuGrid.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# default rule for compiling .o
%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $<

sudoku.o: sudoku.cc sudokuGrid.h
sudokuGrid.o: sudokuGrid.cc sudokuGrid.h

clean:
	rm -rf *.o *~

clean-all: clean
	rm -rf Sudoku
