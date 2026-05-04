CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = programa
SRC = main.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o
