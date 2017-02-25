.PHONY: all clean

TARGET = cstack
FLAGS = -std=c++11 -Wall -g
DEPS = $(OBJS:.o=.d)

-include $(DEPS)

all:
	g++ $(FLAGS) $(TARGET).cpp -c -o $(TARGET).o
	g++ $(FLAGS) $(TARGET).o main.c -o $(TARGET)

clean:
	rm -rf *.o $(TARGET)

