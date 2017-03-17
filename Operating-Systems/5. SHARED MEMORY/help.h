#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <csignal>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/shm.h>

using namespace std;

#ifndef help_h
#define help_h

#include "../headers/file.h"
#include "../headers/sem.h"
#include "../headers/sharedmemory.h"

#endif

