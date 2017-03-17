#include "help.h"

int main(int argc, char* argv[]){
	if(argc!=3)
    	error("ERROR: args invalid");

    int fd[2];
    if(pipe(fd)==-1)
    	error("ERROR: pipe");

    int numProd=atoi(argv[1]);
    int numCons=atoi(argv[2]);
    
    for(int i=0; i<numProd; i++){
		pid_t prod;
		switch(prod=fork()){
			case -1:
				perror("ERROR: fork");
			case 0:
				close(fd[0]);
				if(execl("./producer", "producer", &fd[1], NULL)==-1)
					error("ERROR: execl");
			default:
				cout<<"Created producer with PID "<<prod<<endl;
		}
	}
	close(fd[1]);
	for(int i=0; i<numCons; i++){
		pid_t cons;
		switch(cons=fork()){
			case -1:
				perror("ERROR: fork");
			case 0:
				if(execl("./consumer", "consumer", &fd[0], NULL)==-1)
					error("ERROR: execl");
			default:
				cout<<"Created consumer with PID "<<cons<<endl;
		}
	}
	close(fd[0]);

	pid_t PID;
	int status;
	for(int i=0; i<numProd+numCons; i++){
    	if((PID=wait(&status))==-1)
    		error("ERROR: wait");
		cout<<"PID: "<<PID<<", status code: "<<status<<endl;
    }
}