CC = g++
CFLAGS = -g -Wall
TARGET = utils

all: $(TARGET).o


$(TARGET).o: $(TARGET).cpp ../utils/utils.h
	$(CC) $(CFLAGS) -c $(TARGET).cpp 

clean:
	$(RM) $(TARGET).o $(TARGET)

