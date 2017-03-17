#include "help.h"

int main()
{
	signal(SIGINT, SIGINT_handler);
	Server *msg = new Server('d');
	cout<<"===SERVER==="<<endl;

	while(1){
		msg->serverLoop();
		if(exitable) break;
	}
	delete msg;
	return 0;
}