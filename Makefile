# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)

ifeq ($(type),opt)
    CPPFLAGS += -O3
    LDFLAGS += -O3
else
    CPPFLAGS += -g
    LDFLAGS += -g
endif


#Make everything exept for test
all: pathfinder actorconnections extension 


#Make the test file:
test: test.cpp  ActorGraph.o Circle.o Square.o BipartiteGraph.o


#Make the Pathfinder:
pathfinder: pathfinder.cpp ActorGraph.o Circle.o Square.o BipartiteGraph.o

ActorGraph.o: ActorGraph.h BipartiteGraph.h Circle.o Square.o Actor.hpp Movie.hpp

BipartiteGraph.o: BipartiteGraph.h Circle.o Square.o Actor.hpp Movie.hpp

Circle.o: Circle.h

Square.o: Square.h


#Make the actorconnections:
actorconnections: actorconnections.o BipartiteGraph.o Circle.o Square.o

actorconnections.o: actorconnections.cpp Movie.hpp UnionFind.hpp


#Make the Extension:
extension: extension.o  Protein.o Trait.o

extension.o: extension.cpp Protein.o Trait.o

Protein.o: Protein.h

Trait.o: Trait.h

clean:
	rm -f pathfinder test actorconnections *.o core*
