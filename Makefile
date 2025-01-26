# Nazwa aplikacji
TARGET = saper

# Kompilator
CC = gcc

# Flagi kompilatora
CFLAGS = -Wall -g

# Pliki źródłowe (wszystkie pliki .c w bieżącym katalogu)
SRC = $(wildcard *.c)

# Pliki nagłówkowe (wszystkie pliki .h w bieżącym katalogu)
HDR = $(wildcard *.h)

# Pliki obiektowe
OBJ = $(SRC:.c=.o)

# Reguła główna
all: $(TARGET)

# Tworzenie aplikacji
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Kompilacja plików źródłowych na pliki obiektowe
%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

# Czyszczenie plików obiektowych i aplikacji
clean:
	del -f $(OBJ) $(TARGET)
