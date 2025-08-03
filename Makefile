CXXFLAGS = -g3 -std=c++17 -Wall -Wextra -Werror -O2
CXX = g++
RB_SOURCES = ringbuffer.cpp main.cpp
RB_HEADERS = ringbuffer.hpp

.PHONY: clean all

all: ringbuffer	

ringbuffer: 
	$(CXX) $(CXXFLAGS) $(RB_SOURCES) -o $@

clean:
	rm -f ringbuffer
