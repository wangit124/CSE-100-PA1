# A simple makefile for CSE 100 PA1 BST

#use g++ for everything
CC= g++  	

# include debugging symbols in object files,
# and enable all warnings
CXXFLAGS= -g -Wall -std=c++11

#include debugging symbols in executable
LDFLAGS= -g	

default: test_bst benchmark_bst

test_bst: test_BST.o 
	g++ -o test_bst test_BST.o

benchmark_bst: benchmark_BST.o
	g++ -o benchmark_bst benchmark_BST.o     

test_BST.o: BST.hpp BSTNode.hpp BSTIterator.hpp 
benchmark_bst.o: BSA.hpp BST.hpp

clean:
	$(RM) test_bst benchmark_bst *.o
