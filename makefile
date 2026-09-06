CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -g
CPPFLAGS = -Iinclude

TARGET = axis

SRC = src/main.c src/parser.c src/tokenizer.c src/openfile.c
OBJ = $(SRC:src/%.c=build/%.o)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

build/%.o: src/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
