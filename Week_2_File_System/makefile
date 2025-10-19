CC := gcc
CFLAGS := -O2 -Wall -std=c11

SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
TARGET := file_checking

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
