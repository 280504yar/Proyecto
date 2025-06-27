CC = gcc
CFLAGS = -Wall -I$(INC)
OBJ = $(SRC:.c=.o)
TARGET = main
INC = include
SRC =   # agregar aca el nombre de sus .c, formato: "src/nombre.c"

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

src/%.o: src/%.c main.c $(INC)/*.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm main src/*.o main.o

