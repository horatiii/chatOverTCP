#include<stdio.h>
#include<errno.h>
#include<string.h>   
#include<sys/socket.h>
#include<arpa/inet.h> 
#include <iostream>
#include <unistd.h>

int main(int argc , char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;
	char server_reply[2000];

	/*Create socket*/
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		perror("error with socket creation");
		return -1;
	}

	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_family = AF_INET;
	server.sin_port = htons( atoi(argv[2]) );

	/*Connect to remote server*/
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connection failure");
		return -1;
	}

	puts("connected to server\n");

	unsigned short size; 
	unsigned short i;
	size=read(socket_desc,server_reply,2000);
	if(size!=-1){
		for(i=0;i<size;i++){
			if(server_reply[i]>=33&&server_reply[i]<=126)
				putchar(server_reply[i]);
		}
	}
	else{
		perror("reading did not succeed");
		return -1;
	}
	puts("\n");

	return 0;
}
