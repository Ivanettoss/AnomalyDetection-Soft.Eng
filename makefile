# Definizione delle variabili
CXX = g++
CXXFLAGS = -Wall -Wextra -g -lm -I. -I/usr/include/postgresql -lpq
SRC = init.cpp main.cpp lineUtils.cpp exclusion.cpp QueryGenerator.cpp con2db/pgsql.cpp
OBJ = $(SRC:.cpp=.o)
EXECUTABLE = main

# Regole di compilazione
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^
	$(MAKE) -C "$(CURDIR)/con2db"
	$(MAKE) -C "$(CURDIR)/con2redis/src"

%.o: %.cpp main.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Pulizia dei file intermedi e dell'eseguibile
clean:
	rm -f $(OBJ) $(EXECUTABLE)
	$(MAKE) -C "$(CURDIR)/con2db" clean
	$(MAKE) -C "$(CURDIR)/con2redis/src" clean
