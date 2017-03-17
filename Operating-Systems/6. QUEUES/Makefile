all: server client clean

server: server.o
	g++ server.o -std=c++11 -o server
	chmod 777 server
server.o: server.cpp
	g++ server.cpp -std=c++11 -c -o server.o

client: client.o
	g++ client.o -std=c++11 -lpthread -o client
	chmod 777 client
client.o: client.cpp
	g++ client.cpp -std=c++11 -c -o client.o

clean:
	rm *.o