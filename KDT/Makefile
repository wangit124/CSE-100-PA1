# A simple makefile for CSE 100 PA1 KDT

#use g++ for everything
CC= g++  	

# include debugging symbols in object files,
# and enable all warnings
CXXFLAGS= -g -Wall -std=c++11

#include debugging symbols in executable
LDFLAGS= -g	

default: test_kdt KNNClassifier runtime

test_kdt: test_KDT.o
	g++ -o test_kdt test_KDT.o 

KNNClassifier: KNNClassifier.o
	g++ -o KNNClassifier KNNClassifier.o

runtime: runtime.o
	g++ -o runtime runtime.o

test_KDT.o: KDT.hpp 
KNNClassifier.o: KNNClassifier.cpp KDT.hpp
runtime.o: runtime.cpp KDT.hpp BruteForceKNN.hpp

clean:
	$(RM) test_kdt KNNClassifier runtime *.o
