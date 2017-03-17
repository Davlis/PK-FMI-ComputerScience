#include "help.h"

int main(int argc, char* argv[]){
	if(argc!=2)
		error("ERROR: args invalid");

	Consumer cons(*argv[1]);
	cons.function();
	return 0;
}