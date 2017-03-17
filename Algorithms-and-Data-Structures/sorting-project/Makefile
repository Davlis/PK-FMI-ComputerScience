all: sort clean
sort: projekt.o algorytmy.o pomoc.o
	gcc -o sort projekt.o algorytmy.o pomoc.o -ansi -lm
projekt.o: projekt.c projekt.h
	gcc -c projekt.c
algorytmy.o: algorytmy.c projekt.h
	gcc -c algorytmy.c
pomoc.o: pomoc.c projekt.h
	gcc -c pomoc.c
clean:
	rm *.o