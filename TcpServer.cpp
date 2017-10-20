#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <string.h>

class TcpServer
{
	public: 
		int descriptor, incomingConnection;

		bool setup(unsigned short port);
		bool start();
		bool acceptConnection();
		bool send(char* data);
		char* receive();
	  const int addrSize = sizeof(struct sockaddr_in);
		struct sockaddr_in server , client;
		char toReceive[1024];


	private:


};

bool TcpServer::setup(unsigned short port)
{
	descriptor = socket(AF_INET , SOCK_STREAM , 0); 

	if (descriptor == -1)
	{
		printf("an error: %s\n", strerror(errno));
		return false;
	}

	else
	{ 
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons( port );
		return true;
	}
}


char* TcpServer::receive()
{
	memset(toReceive, 0, sizeof(toReceive));

	//unsigned short size=read(descriptor,toReceive,1024);
	read(descriptor,toReceive,1024);
	return toReceive;
}

bool TcpServer::send(char* data)
{
	write(incomingConnection , "9001" , strlen("9001"));
	return true;
}

bool TcpServer::start()
{

	if( bind(descriptor,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("bind");
		return false;
	}
	
	else
	{
		puts("bind ok");

	listen(descriptor , 3);
	puts("listen ok");


	return true;
	}
}

bool TcpServer::acceptConnection()
{


	incomingConnection = accept(descriptor, (struct sockaddr *)&client, (socklen_t*)&addrSize); 
	if(incomingConnection)
	{
		return true;
	}

	else
	{
		perror("connection refused");
		return false;
	}
}

//int main(){}
