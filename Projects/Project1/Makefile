CXX = g++
CXXFLAGS = -g -Wall -std=c++17

CXX_FILES = $(wildcard *.cc)

OFILES = $(CXX_FILES:cc=o)

all:		clean klayman_p1

klayman_p1:	$(OFILES)
	$(CXX) $(CXXFLAGS) main.o -o $@

clean:
	rm -f *~ *.o klayman_p1
