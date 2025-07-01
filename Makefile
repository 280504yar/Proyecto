CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude/ -I/usr/include/ -Isrc/
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
TARGET = gato_9x9

# Directorios y archivos fuente
SRC_DIR = src
SRC = main.c $(SRC_DIR)/visual.c $(SRC_DIR)/logica.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean
