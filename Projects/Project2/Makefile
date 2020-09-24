CXX = g++
CXXFLAGS = -g -Wall -std=c++17

CXX_FILES = $(wildcard *.cc)

OFILES = $(CXX_FILES:cc=o)

all:		clean klayman_p2

klayman_p2:	$(OFILES)
	$(CXX) $(CXXFLAGS) klayman_p2.o -o $@

clean:
	rm -f *~ *.o klayman_p2
