all: sum-nbo

sum-nbo: main.o
	g++ -Wall -g -o sum-nbo main.o

main.o: main.cpp
	g++ -Wall -g -c main.cpp

clean:
	rm -f sum-nbo main.o
