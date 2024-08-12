LIBS = -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-main -mwindows
# SANATIZER = -fsanitize=address 
CPPVERSION = -std=c++17
INCLUDE = -IC:\SFML-2.6.1\include

output: main.o game.o menu.o resources.o button.o engine.o level.o Entity.o EntityManager.o components.o listener.o
	g++ ${INCLUDE} -LC:\SFML-2.6.1\lib ${CPPVERSION} main.o game.o menu.o resources.o button.o engine.o level.o Entity.o EntityManager.o components.o listener.o -o output ${LIBS}

main.o: main.cpp
	g++ ${INCLUDE} ${CPPVERSION} -g -Wall -c main.cpp

game.o: src/game.cpp include/game.h
	g++ ${INCLUDE} ${CPPVERSION} -g -Wall -c src/game.cpp

menu.o: src/menu.cpp include/menu.h
	g++ ${INCLUDE} ${CPPVERSION} -g -Wall -c src/menu.cpp

resources.o: src/resources.cpp include/resources.h
	g++ ${INCLUDE} ${CPPVERSION} -g -Wall -c src/resources.cpp

button.o: src/button.cpp include/button.h
	g++ ${INCLUDE} ${CPPVERSION} -g -Wall -c src/button.cpp

engine.o: src/engine.cpp include/engine.h
	g++ ${INCLUDE} ${CPPVERSION} -g -Wall -c src/engine.cpp

level.o: src/level.cpp include/Level.h
	g++ ${INCLUDE} ${CPPVERSION} -g -Wall -c src/level.cpp

EntityManager.o: src/EntityManager.cpp include/EntityManager.h
	g++ ${INCLUDE} ${CPPVERSION} -g -Wall -c src/EntityManager.cpp

Entity.o: src/Entity.cpp include/Entity.h
	g++ ${INCLUDE} ${CPPVERSION} -g -Wall -c src/Entity.cpp

components.o: src/components.cpp include/Components.h
	g++ ${INCLUDE} ${CPPVERSION} -g -Wall -c src/components.cpp

listener.o: src/listener.cpp include/listener.h
	g++ ${INCLUDE} ${CPPVERSION} -g -Wall -c src/listener.cpp

clean:
	del *.o output *.exe


