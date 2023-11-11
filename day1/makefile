TARGET = day1

CC = g++
CFLAGS = -g -Wall

all: $(TARGET)

$(TARGET): $(TARGET).o utils.o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o ../utils/utils.o

$(TARGET).o: $(TARGET).cpp ../utils/utils.h
	$(CC) $(CFLAGS) -c $(TARGET).cpp 

utils.o:
	+$(MAKE) -C ../utils

clean:
	$(RM) $(TARGET).o $(TARGET)
