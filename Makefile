LIBS = -lm
CC = gcc
CFLAGS = -g -pthread 
SOURCES = zeroevenodd.c

TARGET = zeroevenodd

default: all

all: clean $(TARGET) 

$(TARGET):
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LIBS)

clean:
	rm -rf $(TARGET)
	
