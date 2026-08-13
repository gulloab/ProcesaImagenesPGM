CC = gcc

CFLAGS = -Wall -g

TARGET = procesador


all: $(TARGET)



$(TARGET): main.o imagen.o
	$(CC) $(CFLAGS) main.o imagen.o -o $(TARGET)



main.o: main.c imagen.h
	$(CC) $(CFLAGS) -c main.c -o main.o


imagen.o: imagen.c imagen.h
	$(CC) $(CFLAGS) -c imagen.c -o imagen.o



clean:
	rm -f *.o $(TARGET) creeper_invertido.pgm


.PHONY: all clean