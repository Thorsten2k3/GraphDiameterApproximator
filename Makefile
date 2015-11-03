.SUFFIXES:

SHELL	= /bin/sh

# Compilers
ifeq ($(clang),1)
	CXX	= clang
	LINK	= clang
else
	CXX	= g++
	LINK	= g++
endif

# Flags
CXXFLAGS	= -Wall -ffast-math -std=c++14

# Debug/Release configuration
ifeq ($(dbg),1)
	CXXFLAGS	+= -g
	BINSUBDIR	:= debug
else
	CXXFLAGS	+= -Ofast -DNDEBUG
	BINSUBDIR	:= release
endif

main: 
	#rm -rf *.o *~ run
	$(CXX) -o run $(CXXFLAGS) Graph.cpp BFS.cpp Diameter.cpp GraphDistance.cpp ReadInput.cpp main.cpp
	
.PHONY: clean

clean:
	rm -rf *.o *~ run
