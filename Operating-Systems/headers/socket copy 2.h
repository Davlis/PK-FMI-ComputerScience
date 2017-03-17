#define MAX_CHAR 8
#define MAX_CLI 2
#define PORT 9021

const char* exitString= "\n\t\n\t\n\t";
static bool exitable=false;

void serverHandler(int signum);
void clientHandler(int signum);

struct Msg{
	int packetsLeft;
	char message[MAX_CHAR+1];
};

class Socket{
protected:
	struct sockaddr_in server;
	int socketfd;
	char* mainBuffer;

	Socket(){
		if((socketfd=socket(AF_INET, SOCK_STREAM, 0))==-1)
			error("ERROR: socket");
		bzero((char*) &server, sizeof(server));
		server.sin_family=AF_INET;
		server.sin_port=htons(PORT);
	}
	~Socket(){
		close(socketfd);
	}

	void _send(const int& socket, const char* buffer){
		int length=strlen(buffer);
		int packetsAmount=length/MAX_CHAR;
		if(length%MAX_CHAR!=0) packetsAmount++;
		
		struct Msg msg;

		for(int i=0, pointer=0; i<packetsAmount; i++){
			bzero(msg.message, MAX_CHAR+1);
			for(int j=0; j<MAX_CHAR&&pointer<length; j++, pointer++)
				msg.message[j]=buffer[pointer];
			msg.packetsLeft=packetsAmount-i-1;
			if(send(socket, (void*)&msg, sizeof(struct Msg), 0)==-1)
				error("ERROR: send");
		}
	}

	void _receive(const int& socket, char* buffer){
		struct Msg msg;
		strncpy(buffer, "\0", 1);
		do{
			if(recv(socket, (void*)&msg, sizeof(struct Msg), 0)==-1){
				if(errno==EINTR)
					break;
				error("ERROR: recv");
			}
			strcat(buffer, msg.message);
		}while(msg.packetsLeft);
	}
};

class Client: public Socket{
	string line;
public:
	Client(const char* _server): Socket(){
		server.sin_addr.s_addr=inet_addr(_server);
		if(connect(socketfd, (struct sockaddr*) &server, sizeof(server))==-1)
			error("Cannot find server. Quitting...");
		cout<<"hehe"<<endl;
		_receive(socketfd, mainBuffer);
		cout<<"Received data package"<<endl;
		if(!strncmp(mainBuffer, "\1", 1))
			error("Server refused connection. Quitting...");
		cout<<"Connected to server."<<endl;

		signal(SIGINT, clientHandler);
	}

	void clientLoop(){
		cout<<"To server: ";
		getline(cin, line);
    	if(exitable) strcpy(mainBuffer, exitString);
    	else strcpy(mainBuffer, line.data());
		_send(socketfd, mainBuffer);
		if(exitable) return;
		_receive(socketfd, mainBuffer);
		cout<<"From server: "<<mainBuffer<<endl;
	}
};

class Server: public Socket{
	friend void serverHandler(int);
    struct sockaddr_in client;
    socklen_t client_size;
	int socketfd_client;

    static int currentThreads;
    thread **t;

    void toUpper(char* buffer){
		for(int i=0; buffer[i]!='\0'; i++){
			if(buffer[i]>='a'&&buffer[i]<='z')
				buffer[i]-=32;
		}	
	}

	bool exitClient(const char* buffer){
		if(strncmp(exitString, buffer, 6)) return false;
		else return true;
	}

	void display(const int& socket, const char* buffer){
		cout<<"Communication from client, ID: "<<socket<<", message: "<<buffer<<endl;
	}

	void serverLoop(int sfd, int i){
		char *threadBuffer;
		while(1){
			_receive(sfd, threadBuffer);
			if(exitClient(threadBuffer)||exitable){
				cout<<"Disconnected client with ID: "<<sfd<<endl;
				Server::currentThreads--;
				t[i]=nullptr;
				return;
			}
			display(sfd, threadBuffer);
			toUpper(threadBuffer);
			_send(sfd, threadBuffer);
		}	
	}

public:
	Server(): Socket(){
		server.sin_addr.s_addr = INADDR_ANY;
		if(::bind(socketfd, (struct sockaddr*) &server, sizeof(server))==-1)
			error("ERROR: bind");

		t=new thread*[MAX_CLI];
		for(int i=0; i<MAX_CLI; i++)
			t[i]=nullptr;

		signal(SIGINT, serverHandler);
	}
	~Server(){
		for(int i=0; i<MAX_CLI; i++)
			if(t[i]!=nullptr)
				delete t[i];
		delete [] t;
	}

	void waitForClient(){
		if(listen(socketfd, 0)==-1)
			error("ERROR: listen");

		if(exitable) return;

		client_size=sizeof(client);
		if((socketfd_client=accept(socketfd, (struct sockaddr*) &client, &client_size))==-1)
			error("ERROR: accept");

		if(Server::currentThreads==MAX_CLI){
			cout<<"Client (ID: "<<socketfd_client<<") connection failed: too many clients already connected"<<endl;
			strncpy(mainBuffer, "\1", 1);
			_send(socketfd_client, mainBuffer);
			return;
		}
		else{
			strncpy(mainBuffer, "\255", 1);
			_send(socketfd_client, mainBuffer);
		}

		int i;
		for(i=0; t[i]!=nullptr; i++);
		t[i] = new thread(&Server::serverLoop, this, socketfd_client, i);
		t[i]->detach();
		Server::currentThreads++;
		cout<<"Connected client with ID: "<<socketfd_client<<endl;
    }
};

int Server::currentThreads=0;

void clientHandler(int signum){
	exitable=true;
}

void serverHandler(int signum){
	if(Server::currentThreads)
		cout<<"SERVER EXIT FAILURE: there are clients still connected to server"<<endl;
	else
		exitable=true;
}