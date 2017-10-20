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

		bool setup(uint16_t port);
		bool start();
		bool acceptConnection();
		bool send(char* data);
		char* receive();
	  const int addrSize = sizeof(struct sockaddr_in);
		struct sockaddr_in server , client;
		char toReceive[1024];


	private:


};

bool TcpServer::setup(uint16_t port)
{
	descriptor = socket(AF_INET , SOCK_STREAM , 0); 

	if (descriptor < 0)
	{
		//perror("setup");
		std::cerr<<"setup failed";
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
	char aux[1024];
	memset(aux, 0, sizeof(aux));

	read(descriptor,toReceive,1024);
	return aux;
}

bool TcpServer::send(char* data)
{
	if( write(incomingConnection , data , strlen(data))>=0)
		return true;

	else
	{
		std::cerr<<"sending failed";
		return false;
	}
}

bool TcpServer::start()
{

	if( bind(descriptor,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//perror("bind");
		std::cout<<"bind failed";
		std::cerr<<"bind failed";
		return false;
	}
	
	else
	{
		//puts("bind ok");
		

	listen(descriptor , 3);
	//puts("listen ok");


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
		//perror("connection refused");
		std::cerr<<"connection failed";
		return false;
	}
}

//int main(){}
