# File: Makefile
# Author: Dylan George
# Date Modified: 1st September 2025
# Description: Makefile for building the logic circuit simulator project.

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Werror
TARGET = A4
SRC = main.cpp logic_gates.cpp circuits.cpp 
HDR = logic_gates.hpp circuits.hpp

$(TARGET): $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
