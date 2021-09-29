#
# PROGRAM: prog2
# AUTHOR:  Noah Flores
#

CXXFLAGS = -Wall -Werror -std=c++11 -Wextra -g -pedantic 

labtrain: main.cpp
	g++ $(CXXFLAGS) -c -o main.o main.cpp
	g++ $(CXXFLAGS) -c -o memory.o memory.cpp
	g++ $(CXXFLAGS) -c -o hex.o hex.cpp
	g++ $(CXXFLAGS) -o memsim main.o memory.o hex.o
clean:
	rm -f *.o prog2