CC = g++
CFLAGS = -g -Wall -std=c++17

utils_dir = ../../utils
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))
TARGET = $(current_dir)

all: $(TARGET)

$(TARGET): $(TARGET).o libutils.a
	$(CC) $(CFLAGS) -o $(TARGET).bin $(TARGET).o -L$(utils_dir) -lutils

$(TARGET).o: $(TARGET).cpp $(utils_dir)/utils.h
	$(CC) $(CFLAGS) -c $(TARGET).cpp

libutils.a:
	$(MAKE) -C $(utils_dir)

clean:
	$(RM) *.o *.bin
