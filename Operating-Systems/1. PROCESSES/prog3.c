#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
	int i, pid, ID, returnStatus;
	const int first_pid=getpid();
	for(i=0; i<3; i++)
	{
		switch(fork())
		{
		case -1:
			perror("Błąd forkowania\n");
			exit(-1);
		case 0:
			execl("prog1", "prog1", NULL);
			sleep(1);
		}
	}

	if(getpid()==first_pid)
	{
		char maketree[20];
		sprintf(maketree, "pstree -hp %d", first_pid);
		system(maketree);
	}
	else sleep(1);

	for(i=0; i<3; ++i)
	{
		returnStatus=wait(&ID);
		if(returnStatus==-1)
		{
			perror("Błąd czekania");
			exit(1);
		}
		printf("Identyfikator procesu: %d, kod powrotu: %d\n", returnStatus, ID);
	}

	return 0;
}