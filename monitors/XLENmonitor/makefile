# Definizione dei comandi di compilazione e pulizia
CC = g++
CFLAGS = -Wall -Wextra -std=c++11
LDFLAGS =
RM = rm -f

# Nome dell'eseguibile
TARGET = XLENmonitor

# Elenco dei file sorgente
SRCS = $(wildcard *.cpp) con2redis/src/readreply.cpp con2redis/src/redisfun.cpp 

# Elenco dei file oggetto generati
OBJS = $(SRCS:.cpp=.o)

# Regola per la creazione dell'eseguibile
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ -lhiredis

# Regola per la compilazione dei file oggetto
%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -lhiredis

# Comando per la pulizia dei file generati
clean:
	$(RM) $(TARGET) $(OBJS)
