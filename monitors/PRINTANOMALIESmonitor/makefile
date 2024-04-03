# Definizione dei comandi di compilazione e pulizia
CC = g++
CFLAGS = -Wall -Wextra -g -lm -I. -I/usr/include/postgresql -lpq 
LDFLAGS =
RM = rm -f

# Nome dell'eseguibile
TARGET = PRINTANOMALIESmonitor

# Elenco dei file sorgente
SRCS = $(wildcard *.cpp) con2db/pgsql.cpp

# Elenco dei file oggetto generati
OBJS = $(SRCS:.cpp=.o)

# Regola per la creazione dell'eseguibile
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ -lpq

# Regola per la compilazione dei file oggetto
%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -lpq

# Comando per la pulizia dei file generati
clean:
	$(RM) $(TARGET) $(OBJS)
