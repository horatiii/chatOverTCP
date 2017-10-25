#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <string.h>

class TcpServer
{
	public: 
		int descriptor, incomingConnection; 
		bool setup(uint16_t port);
		bool start();
		bool acceptConnection();
		bool send(const char* data);
		char* receive();

	private:
		struct sockaddr_in server , client;
		char toReceive[1024]; 
	  const int addrSize = sizeof(struct sockaddr_in);
};


bool TcpServer::setup(uint16_t port)
{
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( port );
	descriptor = socket(AF_INET , SOCK_STREAM , 0); 

	if (descriptor < 0)
	{
		std::cerr <<"descriptor creation:  "<< strerror(errno) << std::endl;
		return false;
	}

	else
	{ 
		return true;
	}
}


char* TcpServer::receive()
{
	memset(toReceive, 0, sizeof(toReceive)); 
	read(descriptor,toReceive,1024);
	return toReceive;
}

bool TcpServer::send(const char* data)
{
	if( write(incomingConnection , data , strlen(data))>=0)
		return true;

	else
	{
		//std::cerr <<"sending:  "<< strerror(errno) << std::endl;
		std::cerr<<"sending failed";
		return false;
	}
}

bool TcpServer::start()
{

	if( bind(descriptor,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		std::cerr <<"bind failed :  "<< strerror(errno) << std::endl;
		return false;
	}

	else
	{ 
		listen(descriptor , 3); 
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
		std::cerr <<"connection:  "<< strerror(errno) << std::endl;
		return false;
	}
}

//int main(){}
