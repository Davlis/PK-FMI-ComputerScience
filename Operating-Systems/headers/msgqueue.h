#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
//#include "sem.h"

#define MAX_CHAR 2000

static bool exitable=false;
static bool makeClientThreads=true;

//class Server;
//static Server* instance;

void SIGINT_handler(int signum){
	exitable=true;
}

static void SIGUSR1_handler(int);

void SIGUSR2_handler(int signum){
	makeClientThreads=false;
	exitable=true;
}

class MsgQueue{
protected:
	key_t key;
	int msgid;
	size_t size;
	long int receiveType;
	//char* buffer;
	struct Msg{
		long int clientId;
		long int responceId;
		int packetsLeft;
		char str[MAX_CHAR+1];
	} msg;
	struct msqid_ds msg_ds;
	//Semaphore* sem;
	int packetsReceived;
	bool isServer;

	bool checkQueue(){
		if(msgctl(msgid, IPC_STAT, &msg_ds)==-1){
			perror("ERROR: msgctl");
			exit(errno);
		}
		if(msg_ds.msg_cbytes>(msg_ds.msg_qbytes*(0.8))) return true;
		else return false;
	}		

	void _send(const string& message){
		char buffer[MAX_CHAR+1];
		int length=message.length();
		int packetsAmount=length/MAX_CHAR;
		if(length%MAX_CHAR!=0) packetsAmount++;

		for(int i=0, pointer=0; i<packetsAmount; i++){
			for(int j=0; j<=MAX_CHAR; j++)
				msg.str[j]='\0';
			for(int j=0; j<MAX_CHAR&&pointer<length; j++, pointer++)
				msg.str[j]=message[pointer];
			msg.packetsLeft=packetsAmount-i-1;
			//while(checkQueue());
			if(msgsnd(msgid, (void*) &msg, size, 0)==-1){
				perror("ERROR: msgsnd");
				exit(errno);
			}
		}
	}

	void _receive(string& buffer){
		buffer="";
		packetsReceived=0;
		do{
			if((msgrcv(msgid, (void*) &msg, size, receiveType, 0))==-1){
				if(errno==EINTR){
					break;
				}
				perror("ERROR: msgrcv");
				exit(errno);
			}
			packetsReceived++;
			buffer+=msg.str;
		}while(msg.packetsLeft);
	}

	MsgQueue(char c){
		//sem = new Semaphore(3, c);
		//sem->V(0);
		//sem->V(1);
		//cout<<sem->getSemVal(0)<<endl;

		size=sizeof(struct Msg)-sizeof(long int);
		key=ftok(".", c);
		if((msgid=msgget(key, IPC_CREAT | 0600))==-1){
			perror("ERROR: msgget");
			exit(errno);
		}
	}
	~MsgQueue(){
		//sem->P(0);
		//cout<<sem->getSemVal(0)<<endl;
		if(isServer==true){
			if((msgctl(msgid, IPC_RMID, 0))==-1){
				perror("ERROR: msgctl");
				exit(errno);
			}
		}
		//delete sem;
	}

	//virtual void send(char*) = 0;
	//virtual void receive(char*) = 0;

public:
	key_t getKey(void) { return key; }
	int getMsgId(void) { return msgid; }
};

class Server: public MsgQueue
{
	string buffer;
	/*void updateReceiveType(){
		receiveType=-(sem->getSemVal(1));
	}*/

	void toUpper(){
		for(int i=0; buffer[i]!='\0'; i++)
			if(buffer[i]>='a'&&buffer[i]<='z')
				buffer[i]-=32;
	}

	void display(){
		cout<<"Communication from client, ID: "<<msg.clientId<<", message: "<<buffer<<endl;
	}

public:
	Server(char c): MsgQueue(c){
		isServer=true;
		//instance=this;
		receiveType=1;
		//updateReceiveType();
		//sem->setSemVal(2, getpid());
		//signal(SIGUSR1, SIGUSR1_handler);
	}	
	~Server(){
		//sem->setSemVal(2, 0);
	}

	/*void handler(int signum){
		updateReceiveType();
	}*/

	void serverLoop(){
		_receive(buffer);
		if(exitable||packetsReceived==0) return;
		display();
		toUpper();
		msg.clientId=msg.responceId;
		_send(buffer);
	}
};

class Client: public MsgQueue
{
	long int sendType;
	int serverId;

	/*
	void checkIfServerPresent(){
		if((serverId=sem->getSemVal(2))==0){
			cout<<endl<<"There is no server present. Closing..."<<endl;
			kill(receiveType, SIGINT);
		}	
	}

	void checkIfServerPresentConst(){
		if((serverId=sem->getSemVal(2))==0){
			cout<<endl<<"There is no server present. Closing..."<<endl;
			kill(receiveType, SIGUSR2);
		}	
	}*/

public:
	Client(char c): MsgQueue(c){
		isServer=false;
		signal(SIGUSR2, SIGUSR2_handler);
		receiveType=getpid();
		sendType=1;
		//checkIfServerPresentConst();
		//if(serverId) kill((pid_t)serverId, SIGUSR1);
	}

	~Client(){
	}

	void sendLoop(){
		string message;
		while(1){
			cout<<"To server: ";
			getline(cin, message);
			//checkIfServerPresent();
			msg.clientId=sendType;
			msg.responceId=receiveType;
			_send(message);	
		}
	}

	void receiveLoop(){
		string message;
		while(1){
			_receive(message);
			if(!packetsReceived) continue;
			cout<<"From server: "<<message<<endl<<endl;
		}
	}
};

//static void SIGUSR1_handler(int signum){
	//instance->handler(signum);
//}
