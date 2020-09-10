CC = gcc
CFLAGS = -Wall -g
LINK = gcc


# Source Files

PROGRAM = grace

SOURCES = $(SRC)/main.c $(SRC)/string.c $(SRC)/token.c $(SRC)/scanner.c

SRC = src
BUILD = build


OBJECTS = $(SOURCES:.c=.o)


all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJECTS)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS)
