#
# PROGRAM: prog2
# AUTHOR:  Noah Flores
#

CXXFLAGS = -Wall -Werror -std=c++11

labtrain: prog2.o
	g++ $(CXXFLAGS) -o prog2 prog2.o

labtrain.o: prog2.cpp
	g++ $(CXXFLAGS) -c prog2.cpp

clean:
	rm -f *.o prog2