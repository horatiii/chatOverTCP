#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
class Tcp
{
	public: 
		int descriptor;
		bool setup(const char* addr, uint16_t port);
		bool connection();
		bool send(char* data);
		char* receive();


	private:
		struct sockaddr_in server;
		char toSend[1024]; 
		char toReceive[1024];


};

bool Tcp::setup(const char *addr, uint16_t port)
{

	server.sin_addr.s_addr = inet_addr(addr);
	server.sin_family = AF_INET;
	server.sin_port = htons( port );

	descriptor = socket(AF_INET , SOCK_STREAM , 0);

	if(descriptor<0)
	{
		return false;
	}
	else return true;
}

bool Tcp::connection()
{

	if (connect(descriptor , (struct sockaddr *)&server , sizeof(server)) < 0)

	{
		//perror("connection failure");
		std::cerr<<"s";
		return false;
	}

	else
	{
		//puts("connected to server");
		
		return true;
	}
}

char* Tcp::receive()
{
  memset(toReceive, 0, sizeof(toReceive)); 
	read(descriptor,toReceive,1024);
	return toReceive;
}

bool Tcp::send(char* data)
{
	write(descriptor , data , strlen(data));
	return true;
}
