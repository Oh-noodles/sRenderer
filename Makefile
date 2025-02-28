DESTDIR = ./
TARGET  = main
OBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all:
	c++ -Wall -std=c++11 -g -I inc src/*.cpp -o ${TARGET}

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)