LIBS = -lsfml-graphics -lsfml-window -lsfml-system

output: TCP.o Sockets.o UDP.o
	g++ TCP.o Sockets.o UDP.o -o output ${LIBS}

TCP.o: TCP.cpp
	g++ -g -Wall -c TCP.cpp

Sockets.o: Sockets.cpp
	g++ -g -Wall -c Sockets.cpp

UDP.o: UDP.cpp
	g++ -g -Wall -c UDP.cpp

clean:
	rm *.o output

