CC = gcc
CFLAGS = -Wall -I$(INC)
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11  # Flags para Raylib
OBJ = $(SRC:.c=.o)
TARGET = gato_9x9  #nombre del archivo que se generara
INC = include
SRC = main.c scr/visual.c scr/logica.c  # agregar aca el nombre de sus .c, formato: "src/nombre.c"

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

src/%.o: src/%.c $(wildcard $(INC)/*.h)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)
.PHONY: all clean
