CXX=g++
CXXFLAGS=-c -g -Wall
LDFLAGS=-lsfml-window -lsfml-graphics -lsfml-system
EXECUTABLE=game
OBJECTS=Objects/

all: $(EXECUTABLE)

$(EXECUTABLE): main.o game.o player.o bullet.o
	$(CXX) main.cpp game.cpp player.cpp bullet.cpp $(LDFLAGS) -o $(EXECUTABLE)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(OBJECTS)main.o

game.o: game.cpp
	$(CXX) $(CXXFLAGS) game.cpp -o $(OBJECTS)game.o

player.o: player.cpp
	$(CXX) $(CXXFLAGS) player.cpp -o $(OBJECTS)player.o

bullet.o: bullet.cpp
	$(CXX) $(CXXFLAGS) bullet.cpp -o $(OBJECTS)bullet.o

clean:
	rm -rf *.o game

run:
	./$(EXECUTABLE)
