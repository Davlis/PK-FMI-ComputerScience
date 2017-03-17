all: prod kons clean

prod: prod.o
	g++ prod.o -std=c++11 -o prod
prod.o: prod.cpp
	g++ prod.cpp -std=c++11 -c -o prod.o

kons: kons.o
	g++ kons.o -std=c++11 -o kons
kons.o: kons.cpp
	g++ kons.cpp -std=c++11 -c -o kons.o

clean:
	rm *.o