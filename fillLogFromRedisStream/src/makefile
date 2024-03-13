CXX = g++
CXXFLAGS = -Wall -Wextra -g -lm -I. -I/usr/include/postgresql -lpq -lhiredis
SRC = $(wildcard *.cpp) con2db/pgsql.cpp con2redis/src/readreply.cpp con2redis/src/redisfun.cpp 
OBJ = $(addprefix ../obj/, $(notdir $(SRC:.cpp=.o)))

EXECUTABLE = ../bin/main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lpq -lhiredis

../obj/%.o: %.cpp main.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

../obj/pgsql.o: con2db/pgsql.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ -lpq $<

../obj/readreply.o: con2redis/src/readreply.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ -lpq -lhiredis $<

../obj/redisfun.o: con2redis/src/redisfun.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ -lpq -lhiredis $<

clean:
	rm -f $(OBJ) $(EXECUTABLE)
