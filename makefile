COMPILER=g++
FLAGS=-Wall -g -std=c++0x -gdwarf-2 
EXECUTABLE=test

all: Driver.o Graph.o
	$(COMPILER) $(FLAGS) -o $(EXECUTABLE) Driver.o Graph.o

Driver.o: Driver.cpp
	$(COMPILER) $(FLAGS) -c Driver.cpp

Graph.o: Graph.cpp
	$(COMPILER) $(FLAGS) -c Graph.cpp

clean:
	rm -rf *.o $(EXECUTABLE)
