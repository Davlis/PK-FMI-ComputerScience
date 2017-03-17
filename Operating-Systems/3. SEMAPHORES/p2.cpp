#include "help.h"

pid_t PID;
Semaphore *sem;

void t21()
{
	writeMsg(21, PID);
	sem->V(0);
    sleep(1);
}

void t22()
{
	sem->P(1);
	writeMsg(22, PID);
	sem->V(2);
    sleep(1);
}

void t23()
{
	sem->P(3);
	writeMsg(23, PID);
	sem->V(4);
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

	t21();
	t22();
	t23();

	delete sem;

	return 0;
}