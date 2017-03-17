all: main consumer producer clean

main: main.cpp
	g++ main.cpp -std=c++11 -o main

consumer: consumer.cpp
	g++ consumer.cpp -std=c++11 -o consumer

producer: producer.cpp
	g++ producer.cpp -std=c++11 -o producer

clean:
	rm *.o