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
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

#ifndef help_h
#define help_h

#define MAX_CHAR 16
#define MAX_CLI 16
#define PORT 20453

void error(const string error){
    perror(error.data());
    exit(errno);
}

const string exitString= "\n\t\n\t\n\t";
static bool exitable=false;

void serverHandler(int signum);
void clientHandler(int signum);

struct Msg{
    int packetsLeft;
    char str[MAX_CHAR+1];
};

class Socket{
protected:
    int socketfd;
    struct sockaddr_in server;
    
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
    
    void _send(const string& message, const int& socket){
        struct Msg msg;
        int length=message.length();
        int packetsAmount=length/MAX_CHAR;
        if(length%MAX_CHAR!=0) packetsAmount++;
        
        for(int i=0, pointer=0; i<packetsAmount; i++){
            bzero(msg.str, MAX_CHAR+1);
            for(int j=0; j<MAX_CHAR&&pointer<length; j++, pointer++)
                msg.str[j]=message[pointer];
            msg.packetsLeft=packetsAmount-i-1;
            if(send(socket, (void*)&msg, sizeof(struct Msg), 0)==-1)
                error("ERROR: send");
        }
    }
    
    void _receive(string& message, const int& socket){
        struct Msg msg;
        message="";
        do{
            if(recv(socket, (void*)&msg, sizeof(struct Msg), 0)==-1){
                if(errno==EINTR)
                    break;
                error("ERROR: recv");
            }
            message+=msg.str;
        }while(msg.packetsLeft);
    }
};

class Client: public Socket{
    string buffer;
public:
    Client(const char* _server): Socket(){
        server.sin_addr.s_addr=inet_addr(_server);
        if(connect(socketfd, (struct sockaddr*) &server, sizeof(server))==-1)
            error("Cannot find server. Quitting...");
        //_receive(buffer, socketfd);
        //if(buffer.compare(0, 1, "\1"))
          //  error("Server refused connection. Quitting...");
        cout<<"Connected to server."<<endl;
        
        signal(SIGINT, clientHandler);
    }
    
    void clientLoop(){
        cout<<"To server: ";
        getline(cin, buffer);
        if(exitable) buffer=exitString;
        _send(buffer, socketfd);
        if(exitable) return;
        _receive(buffer, socketfd);
        cout<<"From server: "<<buffer<<endl;
    }
};

class Server: public Socket{
    friend void serverHandler(int);
    struct sockaddr_in client;
    socklen_t client_size;
    int socketfd_client;
    
    static int currentThreads;
    thread **t;
    
    void toUpper(string& message){;
        for(int i=0; i<message.length(); i++)
            if(message.at(i)>='a'&&message.at(i)<='z')
                message.at(i)-=32;
    }
    
    bool exitClient(const string& message){
        if(message.compare(0, 6, exitString)) return false;
        else return true;
    }
    
    void display(const string& message, const int& socket){
        cout<<"Communication from client, ID: "<<socket<<", message: "<<message<<endl;
    }
    
    void serverLoop(const int sfd, const int i){
        string buffer;
        while(1){
            _receive(buffer, sfd);
            if(exitClient(buffer)||exitable){
                cout<<"Disconnected client with ID: "<<sfd<<endl;
                Server::currentThreads--;
                t[i]=NULL;
                return;
            }
            display(buffer, sfd);
            toUpper(buffer);
            _send(buffer, sfd);
        }
    }
    
public:
    Server(): Socket(){
        server.sin_addr.s_addr = INADDR_ANY;
        if(::bind(socketfd, (struct sockaddr*) &server, sizeof(server))==-1)
            error("ERROR: bind");
        
        client_size=sizeof(client);
        
        if(listen(socketfd, MAX_CLI)==-1)
            error("ERROR: listen");
        
        t=new thread*[MAX_CLI];
        for(int i=0; i<MAX_CLI; i++)
            t[i]=NULL;
        
        signal(SIGINT, serverHandler);
    }
    ~Server(){
        for(int i=0; i<MAX_CLI; i++)
            if(t[i]!=NULL)
                delete t[i];
        delete [] t;
    }
    
    void waitForClient(){
        string buffer;
        
        if(exitable) return;
        
        if((socketfd_client=accept(socketfd, (struct sockaddr*) &client, &client_size))==-1){
            if(errno==EINTR)
                return;
            error("ERROR: accept");
        }

        if(exitable) return;
        
        /*if(Server::currentThreads==MAX_CLI){
            cout<<"Client (ID: "<<socketfd_client<<") connection failed: too many clients already connected"<<endl;
            buffer="\1";
            _send(buffer, socketfd_client);
            return;
        }
        else{
            buffer="\255";
            _send(buffer, socketfd_client);
        }*/
        
        int i;
        for(i=0; t[i]!=NULL; i++);
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
        cout<<" SERVER EXIT FAILURE: there are clients still connected to server"<<endl;
    else
        exitable=true;
}

#endif

int main(int argc, char *argv[])
{
    if(argc!=1)
        error("ERROR: args invalid");

	cout<<"===SERVER==="<<endl;

    Server *soc = new Server();

	while(1){
		soc->waitForClient();
		if(exitable) break;
	}

	delete soc;
	return 0;
}
