#include<stdio.h>
#include<string.h>    
#include <cstdlib>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>    
#include<errno.h>
#include <iostream>
#include <vector>
#include <thread>


int hostSocketDescriptor , incomingSocketDescriptor , c;
struct sockaddr_in server , client;
char message[2000];
unsigned short availablePort = 9000;


void handleClient(unsigned short port)
{
	int newHost = socket(AF_INET , SOCK_STREAM , 0);
	std::cout<<"handling next client"<<std::endl;
	server.sin_port = htons( port );

	/*Bind*/
	if( bind(newHost,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("accept failed");
	}
	else
	{

	puts("listening for client ");

	/*Listen*/
	int newClient;
	listen( newHost, 3);

		if( newClient = accept(newHost, (struct sockaddr *)&client, (socklen_t*)&c)) 
		{
			std::cout<<"sending message to port "<<port<<std::endl;
			char* tempMsg = "xxx|||";
			for(int i=0;i<5;++i)	
			{
			write(newClient , tempMsg , strlen(tempMsg));
			}
		}
		else
		{
			std::cout<<"client was not accepted"<<std::endl;
		}
}
}

void collectClients()
{
	while (true)
	{
		if( incomingSocketDescriptor = accept(hostSocketDescriptor, (struct sockaddr *)&client, (socklen_t*)&c)) 
		{

      sprintf(message, "%d", ++availablePort);

			//std::thread (handleClient,availablePort).join();


			write(incomingSocketDescriptor , message , strlen(message));
		}

		//if(incomingSocketDescriptor<0)
		else
		{
			perror("connection refused");
			/*return -1;*/
		}
	}
}


int main(int argc , char *argv[])
{



	/*Create socket*/
	hostSocketDescriptor = socket(AF_INET , SOCK_STREAM , 0);
	if (hostSocketDescriptor == -1)
	{
		printf("an error: %s\n", strerror(errno));
		return -1;
	}

	server.sin_family = AF_INET; /*ipv4 address type*/
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( atoi(argv[1]) );

	/*Bind*/
	if( bind(hostSocketDescriptor,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("accept failed");
		return -1;
	}

	puts("bind done");

	/*Listen*/
	listen(hostSocketDescriptor , 3);

	/*Accept incoming connection*/
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	std::thread (collectClients).join();
	//std::thread t1(collectClients);
	//t1.join();


	return 0;
}
