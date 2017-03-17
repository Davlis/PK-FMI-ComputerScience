#include "help.h"

#define C_A 3

string prog[6]=
{
	"./p1", "p1",
	"./p2", "p2",
	"./p3", "p3"
};

int main()
{
	int status, which=0;
	pid_t PID, children[C_A];

	File *file = new File("spr1.txt");
	file->deleteFile();
	delete file;

	Semaphore *sem = new Semaphore(5, 'c');
	const string semid=to_string(sem->getSemId());

	for(int i=0; i<C_A; i++)
	{
		switch(children[i]=fork())
		{
			case -1:
			perror("ERROR: fork");
			exit(errno);
			continue;

			case 0:
			cout<<prog[which]<<" się teraz uruchomi, PID = "<<getpid()<<endl;
			if(execl(prog[which].c_str(), prog[which+1].c_str(), semid.c_str(), NULL)==-1)
			{
				perror("ERROR: execl");
				exit(errno);
			}
			break;

			default:
			which+=2;
		}
	}

    for(int i=0;i<C_A;++i)
    {
    	PID=wait(&status);
		cout<<"PID: "<<PID<<", status code: "<<status<<endl;
		if(status)
		{
			perror("PROCESS QUIT EARLY");
			for(i=0; i<C_A; i++)
				if(kill(children[i], SIGKILL)==0)
					cout<<"Killed child process PID = "<<children[i]<<endl;
			break;
		}
    }

	delete sem;

	return 0;
}
