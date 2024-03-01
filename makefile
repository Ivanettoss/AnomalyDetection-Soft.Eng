CXX = g++
CXXFLAGS = -Wall -Wextra -g -lm -I. -I/usr/include/postgresql -lpq -lhiredis
SRC = $(wildcard *.cpp) con2db/pgsql.cpp con2redis/src/readreply.cpp con2redis/src/redisfun.cpp
OBJ = $(SRC:.cpp=.o)
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lpq -lhiredis
	$(MAKE) -C "$(CURDIR)/con2db"
	$(MAKE) -C "$(CURDIR)/con2redis/src"


%.o: %.cpp main.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

con2db/pgsql.o: con2db/pgsql.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< -lpq

clean:
	rm -f $(OBJ) $(EXECUTABLE)
	$(MAKE) -C "$(CURDIR)/con2db" clean
	$(MAKE) -C "$(CURDIR)/con2redis/src" clean
