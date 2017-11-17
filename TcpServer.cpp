#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <string.h>
#define MAX_CONN_QUANTITY 3

class TcpServer
{
	public: 
		int hostDescriptor; 
		bool setup(uint16_t port);
		bool start();
		int acceptConnection();

	private:
		struct sockaddr_in server , client;
	  const int addrSize = sizeof(struct sockaddr_in);
};


bool TcpServer::setup(uint16_t port)
{
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( port );
	hostDescriptor = socket(AF_INET , SOCK_STREAM , 0); 


	/*may appropriate descriptor equal zero ?*/
	if (hostDescriptor >= 0)
	{
		return true;
	}

	else
	{ 
		std::cerr <<"descriptor creation:  "<< strerror(errno) << std::endl;
		return false;
	}
} 

bool TcpServer::start()
{

	if( bind(hostDescriptor,(struct sockaddr *)&server , sizeof(server)) == 0)
	{
		listen(hostDescriptor , MAX_CONN_QUANTITY); 
		return true;
	}

	else
	{ 
		std::cerr <<"bind failed :  "<< strerror(errno) << std::endl;
		return false;
	}
}

int TcpServer::acceptConnection()
{ 
	int temporary =accept(hostDescriptor, (struct sockaddr *)&client, (socklen_t*)&addrSize);

	/*still, can appropriate descriptor equal zero ?*/
	if(temporary<0)
	{
		std::cerr <<"connection:  "<< strerror(errno) << std::endl;
	}

	return temporary;

}
