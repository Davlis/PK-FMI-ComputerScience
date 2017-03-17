#include "help.h"

pid_t PID;
Semaphore *sem;

void t31()
{
	sem->P(0);
	writeMsg(31, PID);
	sleep(1);
}

void t32()
{
	writeMsg(32, PID);
	sem->V(1);
	sleep(1);
}

void t33()
{
	sem->P(4);
	writeMsg(33, PID);
	sleep(1);
}

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		perror("ERROR: argc invalid");
		exit(errno);
	}

	const int semid=atoi(argv[1]);
	PID=getpid();

	sem = new Semaphore(5, 'c');

	t31();
	t32();
	t33();

	delete sem;

	return 0;
}