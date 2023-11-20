CC = g++
CFLAGS = -g -Wall -std=c++17
TARGET = libutils
HEADERS = string_list.h string_utils.h
OBJS = string_list.o string_utils.o

all: $(TARGET).a

$(TARGET).a: $(OBJS)
	ar rcs $(TARGET).a $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $< 

.PHONY: clean

clean:
	$(RM) *.o *.a

