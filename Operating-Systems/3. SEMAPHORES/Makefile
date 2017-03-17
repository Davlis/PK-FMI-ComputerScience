all: main p1 p2 p3 clean

main: main.o
	g++ main.o -std=c++11 -o main
main.o: main.cpp
	g++ main.cpp -std=c++11 -c -o main.o

p1: p1.o
	g++ p1.o -std=c++11 -o p1
p1.o: p1.cpp
	g++ p1.cpp -std=c++11 -c -o p1.o

p2: p2.o
	g++ p2.o -std=c++11 -o p2
p2.o: p2.cpp
	g++ p2.cpp -std=c++11 -c -o p2.o

p3: p3.o
	g++ p3.o -std=c++11 -o p3
p3.o: p3.cpp
	g++ p3.cpp -std=c++11 -c -o p3.o

clean:
	rm *.o