#include "help.h"

pid_t PID;
Semaphore *sem;

void t11()
{
	sem->P(2);
	writeMsg(11, PID);
	sleep(1);
}

void t12()
{
	writeMsg(12, PID);
	sem->V(3);
	sleep(1);
}

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		perror("ERROR: argc invalid");
		exit(EXIT_FAILURE);
	}

	const int semid=atoi(argv[1]);
	PID=getpid();

	sem = new Semaphore(5, 'c');

	t11();
	t12();
	
	delete sem;

	return 0;
}