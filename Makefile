DEBUG=-g
CPP11=-std=c++11

all: ant

main.o: main.cpp
	g++ $(CPP11) $(DEBUG) -c -Wall main.cpp ant.cpp grid.cpp 
	
ant: main.o
	g++ main.o ant.o grid.o -o ant -pthread

clean:
	rm -rf *.gch *o ant *~; clear;clear;
