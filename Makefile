CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
TARGET = udeabook
SRC = src/main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
