COMPILIER=g++
FLAGS=-c -Wall -std=c++0x
LDFLAGS=-g
SOURCES=Driver.cpp Graph.cpp Graph.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=a.out

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(COMPILIER) $(LDFLAGS) $(FLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(COMPILIER) $(CFLAGS) $< -o $@
