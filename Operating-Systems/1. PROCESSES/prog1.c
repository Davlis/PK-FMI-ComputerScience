#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	printf("Identyfikator procesu: %d\n", getpid());
	printf("Identyfikator procesu macierzystego: %d\n", getppid());
	printf("Identyfikator użytkownika: %d\n", getuid());
	printf("Identyfikator grupy: %d\n", getgid());
	printf("\n");
	return 0;
}