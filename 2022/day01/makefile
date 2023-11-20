CC = g++
CFLAGS = -g -Wall -std=c++17

TARGET = day01

all: $(TARGET)

$(TARGET): $(TARGET).o libutils.a
	$(CC) $(CFLAGS) -o $(TARGET).bin $(TARGET).o -L../../utils -lutils

$(TARGET).o: $(TARGET).cpp ../../utils/string_list.h
	$(CC) $(CFLAGS) -c $(TARGET).cpp

libutils.a:
	$(MAKE) -C ../../utils

clean:
	$(RM) *.o *.bin
