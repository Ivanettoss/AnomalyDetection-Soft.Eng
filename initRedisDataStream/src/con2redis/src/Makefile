IDIR = .
ODIR = ../obj

CC = g++
CFLAGS = -std=c++20 -g -ggdb -fpermissive -L/usr/local/lib -Wall -I. -lm -lhiredis

DEPS = $(wildcard $(IDIR)/*.h)
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, $(ODIR)/%.o, $(SRC))

all: $(OBJ)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Pulizia dei file intermedi
clean:
	rm -f $(ODIR)/*.o

