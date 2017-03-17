#include "help.h"

int main(int argc, char *argv[])
{
    if(argc!=1)
        error("ERROR: args invalid");

	cout<<"===SERVER==="<<endl;

    Server *soc = new Server();

	while(1){
		soc->waitForClient();
		if(exitable) break;
	}

	delete soc;
	return 0;
}