#include<stdio.h>
#include<string.h>    
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>    
#include<errno.h>
#include <iostream>
#include <vector>



int main(int argc , char *argv[])
{
	int hostSocketDescriptor , incomingSocketDescriptor , c;
	struct sockaddr_in server , client;
	char *message;

	

	/*Create socket*/
	hostSocketDescriptor = socket(AF_INET , SOCK_STREAM , 0);
	if (hostSocketDescriptor == -1)
	{
		printf("an error: %s\n", strerror(errno));
		return -1;
	}

	server.sin_family = AF_INET;
	/*server.sin_addr.s_addr = INADDR_ANY;*/
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
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

	/*Accept and incoming connection*/
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	while( (incomingSocketDescriptor = accept(hostSocketDescriptor, (struct sockaddr *)&client, (socklen_t*)&c)) )
	{
		puts("connection accepted");
		message = "Hello World\r\n";

		write(incomingSocketDescriptor , message , strlen(message));
	}

	if (incomingSocketDescriptor<0)
	{
		perror("connection refused");
		/*return -1;*/
	}

	return 0;
}
