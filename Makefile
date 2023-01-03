CC=gcc
CFLAGS=-g -Wall
TARGET=main
OBJS=exception.o library.o server.o main.o

all : $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm $(OBJS)
	rm $(TARGET)