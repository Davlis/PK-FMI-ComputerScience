#include "help.h"

int main(int argc, char *argv[])
{
	if(argc!=2)
        error("ERROR: no hostname");

	cout<<"===CLIENT==="<<endl;

	Client *soc = new Client(argv[1]);

	while(1){
		if(exitable) break;
		soc->clientLoop();
	}

	delete soc;
	return 0;
}