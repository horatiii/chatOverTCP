#include<stdio.h>
#include<errno.h>
#include<string.h>   
#include<sys/socket.h>
#include<arpa/inet.h> 
#include <iostream>
#include <unistd.h>

#define MAX_REPLY_SIZE 2000

int hostSocket;
unsigned short size; 
struct sockaddr_in server;
char serverReply[MAX_REPLY_SIZE];

int main(int argc , char *argv[])
{

	/*Create socket*/
	hostSocket = socket(AF_INET , SOCK_STREAM , 0);
	if (hostSocket == -1)
	{
		perror("error with socket creation");
		return -1;
	}

	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_family = AF_INET;
	server.sin_port = htons( atoi(argv[2]) );

	/*Connect to remote server*/
	if (connect(hostSocket , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connection failure");
		return -1;
	}

	else
	{
		puts("connected to server\n");
	}




		size=read(hostSocket,serverReply,MAX_REPLY_SIZE);
		short port = atoi(serverReply);
		

		if(size!=-1)
		{
			std::cout<<"port = "<<port<<std::endl;
		}
		else
		{
			perror("reading did not succeed");
			return -1;
		}


	//server.sin_port = port;
	//int socketForMsg = socket(AF_INET , SOCK_STREAM , 0);

	//usleep(1e2);
	//std::cout<<"after a sec"<<std::endl;
	//if (connect(socketForMsg , (struct sockaddr *)&server , sizeof(server)) < 0)
	//{
		//perror("connection failure");
		//return -1;
		
	//}
	
	//else
	//{
		//size=read(socketForMsg,serverReply,MAX_REPLY_SIZE);
		//std::cout<<serverReply<<std::endl;
	//}





	return 0;
}
