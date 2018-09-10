CXX=g++
CXXFLAGS=-c -Wall
LDFLAGS=-lsfml-window -lsfml-graphics -lsfml-system
EXECUTABLE=game

all: $(EXECUTABLE)

$(EXECUTABLE): main.o game.o player.o bullet.o
	$(CXX) main.cpp game.cpp player.cpp bullet.cpp $(LDFLAGS) -o $(EXECUTABLE)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp 

game.o: game.cpp
	$(CXX) $(CXXFLAGS) game.cpp 

player.o: player.cpp
	$(CXX) $(CXXFLAGS) player.cpp 

bullet.o: bullet.cpp
	$(CXX) $(CXXFLAGS) bullet.cpp 

clean:
	rm -rf *.o game
