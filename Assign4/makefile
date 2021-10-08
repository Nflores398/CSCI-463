#
# PROGRAM: prog2
# AUTHOR:  Noah Flores
#

CXXFLAGS = -Wall -std=c++11 -Wextra -g -pedantic -std=c++14

labtrain: main.cpp
	g++ $(CXXFLAGS) -c -o main.o main.cpp
	g++ $(CXXFLAGS) -c -o rv32i_decode.o rv32i_decode.cpp
	g++ $(CXXFLAGS) -c -o memory.o memory.cpp
	g++ $(CXXFLAGS) -c -o hex.o hex.cpp
	g++ $(CXXFLAGS) -o rv32i main.o rv32i_decode.o memory.o hex.o
clean:
	rm -f *.o prog2