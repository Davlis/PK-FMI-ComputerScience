#include "help.h"

void* loopFn(Client *msg, int i){
	switch(i){
	case 0: msg->sendLoop(); break;
	case 1: msg->receiveLoop(); break;
	}
}

int main()
{
	signal(SIGINT, SIGINT_handler);

	Client *msg = new Client('d');
	cout<<"===CLIENT==="<<endl;

	thread **t = new thread*[2];
	if(makeClientThreads){
		for(int i=0; i<2; i++){
        	t[i] = new thread(&loopFn, msg, i);
        	t[i]->detach();
   		}
	}

    while(!exitable){
    	sleep(1);
    }

    if(makeClientThreads){
		for(int i=0; i<2; i++)
        	delete t[i];
    }
	delete [] t;
	delete msg;
	return 0;
}