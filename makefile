COMPILER=g++
FLAGS=-Wall -ggdb -std=c++0x
EXECUTABLE=test

all: Driver.o Graph.o
	$(COMPILER) $(FLAGS) -o $(EXECUTABLE) Driver.o Graph.o

Driver.o: Driver.cpp
	$(COMPILER) $(FLAGS) -c Driver.cpp

Graph.o: Graph.cpp
	$(COMPILER) $(FLAGS) -c Graph.cpp

clean:
	rm -f *.o $(EXECUTABLE)
