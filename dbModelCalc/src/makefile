CXX = g++
CXXFLAGS = -Wall -Wextra -g -lm -I. -I/usr/include/postgresql -lpq 
SRC = $(wildcard *.cpp) con2db/pgsql.cpp 
OBJ = $(addprefix ../obj/, $(notdir $(SRC:.cpp=.o)))

EXECUTABLE = ../bin/main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lpq 

../obj/%.o: %.cpp main.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

../obj/pgsql.o: con2db/pgsql.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ -lpq $<

clean:
	rm -f $(OBJ) $(EXECUTABLE)