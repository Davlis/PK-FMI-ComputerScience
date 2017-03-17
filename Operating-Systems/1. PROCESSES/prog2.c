#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	int i, pid;
	const int first_pid=getpid();

	for(i=0; i<3; i++)
	{
		switch(fork())
		{
		case -1:
			exit(-1);
		case 0:
			printf("Identyfikator procesu: %d\n", getpid());
			printf("Identyfikator procesu macierzystego: %d\n", getppid());
			printf("Identyfikator użytkownika: %d\n", getuid());
			printf("Identyfikator grupy: %d\n", getgid());
			printf("\n");
		}
	}

	if(getpid()==first_pid)
	{
		char maketree[20];
		sprintf(maketree, "pstree -hp %d", first_pid);
		system(maketree);
	}
	else sleep(1);

	return 0;
}