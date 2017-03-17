class SharedMemory
{
	key_t key;
	int shmid;
	char* adress;
	Semaphore* sem;

public:
	SharedMemory(){
		sem = new Semaphore(1, 'S');
		sem->V(0);
		
		key=ftok(".", 'A');
		if((shmid=shmget(key, sizeof(char), IPC_CREAT | 0600))==-1){
			perror("ERROR: shmget");
			exit(errno);
		}
		
		if((adress=(char*)shmat(shmid, 0, 0))==(char*)-1){
			perror("ERROR: shmat");
			exit(errno);
		}	
	}

	~SharedMemory(){	
		if((shmdt(adress))==-1){
			perror("ERROR: shmdt");
			exit(errno);
		}

		sem->P(0);
		if(!(sem->getSemVal(0))){
			if((shmctl(shmid, IPC_RMID, 0))==-1){
				perror("ERROR: shmctl");
				exit(errno);
			}
			delete sem;
		}
	}

	char read(){
		return *adress;
	}

	void write(char c){
		*adress=c;
	}

	key_t getKey(void) { return key; }
	int getShmId(void) { return shmid; }
};