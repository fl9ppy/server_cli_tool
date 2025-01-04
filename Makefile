# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Target executable
TARGET = mytool

# Source and object files
SRC = src/main.cpp src/console.cpp src/plugin_manager.cpp src/config_manager.cpp
OBJ = $(SRC:.cpp=.o)

# Build rule
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean rule
clean:
	rm -f $(OBJ) $(TARGET)
