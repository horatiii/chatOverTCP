#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
class TcpClient
{
	public: 
		int descriptor;
		bool setup(const char* addr, uint16_t port);
		bool connection();
		bool send(char* data);
		char* receive();


	private:
		struct sockaddr_in server;
		char toReceive[1024];


};

bool TcpClient::setup(const char *addr, uint16_t port)
{
	server.sin_addr.s_addr = inet_addr(addr);
	server.sin_family = AF_INET;
	server.sin_port = htons( port );
	descriptor = socket(AF_INET , SOCK_STREAM , 0);

	if(descriptor<0)
	{
		std::cerr <<"descriptor creation:  "<< strerror(errno) << std::endl;
		return false;
	}
	else 
	{
		return true;
	}


}

bool TcpClient::connection()
{

	if (connect(descriptor , (struct sockaddr *)&server , sizeof(server)) < 0)

	{
		std::cerr <<"connection:  "<< strerror(errno) << std::endl;
		return false;
	}

	else
	{
		return true;
	}
}

char* TcpClient::receive()
{
  memset(toReceive, 0, sizeof(toReceive)); 
	read(descriptor,toReceive,1024);
	return toReceive;
}

bool TcpClient::send(char* data)
{
	write(descriptor , data , strlen(data));
	return true;
}
