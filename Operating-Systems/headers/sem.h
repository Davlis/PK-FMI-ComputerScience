class Semaphore{
	key_t key;
	int semid;
	const int amount;
	struct sembuf bsem;
	union semun argument;

	void semOp(){
		while(semop(semid, &bsem, 1)==-1){
			if(errno==EINTR||errno==EAGAIN)
				continue;
    		else{
				perror("ERROR: semop");
      			exit(errno);
			}
		}
	}

public:
	void V(int n){
		bsem.sem_num=n;
		bsem.sem_op=1;
		semOp();
	}

	void P(int n){            
		bsem.sem_num=n;
		bsem.sem_op=-1;
		semOp();
	}

	int getSemVal(int n){
		int i;
		if((i=semctl(semid, n, GETVAL, argument))==-1){
			perror("ERROR: semctl getval");
			exit(errno);
		}
		return i;
	}

	void setSemVal(int n, int val){
		argument.val=val;
		if(semctl(semid, n, SETVAL, argument)==-1){
			perror("ERROR: semctl setval");
			exit(errno);
		}
	}

	Semaphore(int _amount, int c): amount(_amount){
		bool exists=false;
		key=ftok(".", c);
		if((semid=semget(key, amount+1, IPC_CREAT | IPC_EXCL | 0600))==-1){
			if(errno==EEXIST)
				exists=true;
			else{
				perror("ERROR: semget");
				exit(errno);
			}	
		}

		if(exists){
			if((semid=semget(key, amount+1, IPC_CREAT | 0600))==-1){
				perror("ERROR: semget");
				exit(errno);
			}
		}
		else{
			argument.array = new unsigned short[amount+1];
			for(int i=0; i<=amount; i++)
				argument.array[i]=0;

			if(semctl(semid, 0, SETALL, argument)==-1){
				perror("ERROR: semctl");
				exit(errno);
			}

			delete [] argument.array;
		}

		V(amount);
	}

	~Semaphore(){
		P(amount);

		if(!getSemVal(amount)){
			if((semctl(semid, 0, IPC_RMID, argument))==-1){
				perror("ERROR: semctl");
				exit(errno);
			}
		}
	}

	key_t getKey(void) { return key; }
	int getSemId(void) { return semid; }
};