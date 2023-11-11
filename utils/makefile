CC = g++
CFLAGS = -g -Wall -std=c++17
TARGET = libutils

all: $(TARGET).a

utils.o: utils.cpp 
	$(CC) $(CFLAGS) -c utils.cpp 

$(TARGET).a: utils.o
	ar rcs $(TARGET).a utils.o

clean:
	$(RM) *.o *.a

