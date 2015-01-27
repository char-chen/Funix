funix.out: funix.o directory.o permissions.o main.o
	g++ -ansi -Wall funix.o directory.o permissions.o main.o -o funix.out
funix.o: funix.cpp funix.h directory.h permissions.h
	g++ -ansi -Wall -c funix.cpp
directory.o: directory.cpp directory.h permissions.h
	g++ -ansi -Wall -c directory.cpp
permissions.o: permissions.cpp permissions.h
	g++ -ansi -Wall -c permissions.cpp
main.o: main.cpp funix.h
	g++ -ansi -Wall -c main.cpp
clean:
	rm -f funix.o directory.o main.o permissions.o