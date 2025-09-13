# Makefile for Menagerie Game
# Requires SFML to be installed

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
TARGET = menagerie
SOURCE = main.cpp

# Default target
all: $(TARGET)

# Build the game
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

# Clean build artifacts
clean:
	rm -f $(TARGET) *.o

# Install dependencies (Ubuntu/Debian)
install-deps:
	sudo apt-get update
	sudo apt-get install libsfml-dev

# Run the game
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean install-deps run
