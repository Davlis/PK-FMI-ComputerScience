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

#define SIZE_OF_DATA 10

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

class Pipe{
protected:
	int fd;
	int val;
	pid_t PID;
	char c;
	File* file;

public:
	Pipe(int _fd): fd(_fd), val(0), PID(getpid()){
		srand(time(NULL));
	}
	~Pipe(){
		close(fd);
		delete file;
	}
};

class Producer: public Pipe{
public:
	Producer(int _fd): Pipe(_fd){
		string filename;
		filename="ALA";//"producer_"+to_string(PID);

		file = new File(filename, "w");
	}

	void function(){
		for(int i=0; i<SIZE_OF_DATA; i++){
			c='a'+rand()%26;
			if((val=write(fd, (char*) &c, sizeof(c)))==-1)
				error("ERROR: write");
			file->write(c);
			cout<<"Producer ID "<<PID<<" wrote to pipe: "<<c<<endl;
		}
	}
};

class Consumer: public Pipe{
public:
	Consumer(int _fd): Pipe(_fd){
		string filename;
		filename="ALA";//"consumer_"+to_string(PID);

		file = new File(filename, "w");
	}

	void function(){
		while(1){
			if((val=read(fd, (char*) &c, sizeof(c)))==-1)
				error("ERROR: read");
			else if(val==0)
				break;
			file->write(c);
			cout<<"Consumer ID "<<PID<<" read from pipe: "<<c<<endl;
		}
	}
};