#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <cctype>
#include <cstring>
#include <string>
#include <thread>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/stat.h> 
#include <fcntl.h>

#define SIZE_OF_DATA 100

using namespace std;

void error(const string error){
    perror(error.data());
    exit(errno);
}

class File{
	FILE *file;
	string name;
	string accessType;
public:
	File(string _name, string _accessType): name(_name), accessType(_accessType){
		if((file=fopen(name.data(), accessType.data()))==NULL)
 			error("ERROR: fopen");
	}
	~File(){
		if(fclose(file)==EOF)
			error("ERROR: fclose");
	}

	void write(char c){
		putc(c, file);
	}

	char read(){
		return getc(file);
	}	
};

class Fifo{
protected:
	int fd;
	int val;
	pid_t PID;
	char c;
	File* file;

public:
	Fifo(): val(0), PID(getpid()){
		srand(time(NULL));
	}
	~Fifo(){
		if(close(fd)==-1)
			error("ERROR: close");
		delete file;
	}
};

class Producer: public Fifo{
public:
	Producer(): Fifo(){
		if((fd=open("./fifo", O_WRONLY | O_NONBLOCK))==-1)
			error("ERROR: producer - open");

		string filename;
		filename="producer_"+to_string(PID);

		file = new File(filename, "w");
	}

	void function(){
		for(int i=0; i<SIZE_OF_DATA; i++){
			c='a'+rand()%26;
			if((val=write(fd, (char*) &c, sizeof(c)))==-1)
				error("ERROR: write");
			file->write(c);
			cout<<"Producer ID "<<PID<<" wrote to fifo: "<<c<<endl;
		}
	}
};

class Consumer: public Fifo{
public:
	Consumer(): Fifo(){
		if((fd=open("./fifo", O_RDONLY))==-1)
			error("ERROR: consumer - open");

		string filename;
		filename="consumer_"+to_string(PID);

		file = new File(filename, "w");
	}

	void function(){
		while(1){
			if((val=read(fd, (char*) &c, sizeof(c)))==-1)
				error("ERROR: read");
			else if(val==0)
				break;
			file->write(c);
			usleep(50);
			cout<<"Consumer ID "<<PID<<" read from fifo: "<<c<<endl;
		}
	}
};