LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-main -mwindows
INCLUDE = -IC:\SFML-2.6.1\include

output: main.o game.o menu.o resources.o button.o engine.o level.o Entity.o EntityManager.o components.o
	g++ -LC:\SFML-2.6.1\lib main.o game.o menu.o resources.o button.o engine.o level.o Entity.o EntityManager.o components.o -o output ${LIBS}

main.o: main.cpp
	g++ -g -Wall ${INCLUDE} -c main.cpp

game.o: src/game.cpp include/game.h
	g++ -g -Wall ${INCLUDE} -c src/game.cpp

menu.o: src/menu.cpp include/menu.h
	g++ -g -Wall ${INCLUDE} -c src/menu.cpp

resources.o: src/resources.cpp include/resources.h
	g++ -g -Wall ${INCLUDE} -c src/resources.cpp

button.o: src/button.cpp include/button.h
	g++ -g -Wall ${INCLUDE} -c src/button.cpp

engine.o: src/engine.cpp include/engine.h
	g++ -g -Wall ${INCLUDE} -c src/engine.cpp

level.o: src/level.cpp include/Level.h
	g++ -g -Wall ${INCLUDE} -c src/level.cpp

EntityManager.o: src/EntityManager.cpp include/EntityManager.h
	g++ -g -Wall ${INCLUDE} -c src/EntityManager.cpp

Entity.o: src/Entity.cpp include/Entity.h
	g++ -g -Wall ${INCLUDE} -c src/Entity.cpp

components.o: src/components.cpp include/Components.h
	g++ -g -Wall ${INCLUDE} -c src/components.cpp

clean:
	rm *.o output


