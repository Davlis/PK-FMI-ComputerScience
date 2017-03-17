#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <csignal>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

using namespace std;

#ifndef help_h
#define help_h

class File
{
	fstream f;
	const string name;
public:
	File(string _name): name(_name) { f.open(name, fstream::app); }
	~File() { f.close(); }
	void write(string buffer) { f<<buffer<<endl; }
	void deleteFile() 
	{
		f.close();
		f.open(name, fstream::out);
	}
};

void writeMsg(int taskNr, pid_t PID)
{
	string buffer;
	buffer="Sekcja t";
    buffer+=to_string(taskNr);
	buffer+=" procesu o PID = ";
    buffer+=to_string(PID);
	File *file = new File("spr1.txt");
	file->write(buffer);
	delete file;
}

#include "../headers/sem.h"

#endif
