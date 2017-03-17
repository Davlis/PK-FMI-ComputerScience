#include "help.h"

int main(int argc, char* argv[]){
	if(argc!=2)
		error("ERROR: args invalid");

	Producer prod(*argv[1]);
	prod.function();
	return 0;
}