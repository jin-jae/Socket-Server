CC=gcc
CFLAGS=-g -Wall
TARGET=server
OBJS=exception.o library.o server.o main.o request.o

all : $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm $(OBJS)
	rm $(TARGET)