#include "TcpServer.cpp" 
#include <thread>
#include <vector>
#include <csignal>
#include <algorithm>

TcpServer primary; 
std::vector<int> clients;

void sendMessage(int descriptor,const char* data)
{
	/*this code may look difficult to read, just ignore this function content for now*/
	signal(SIGPIPE, SIG_IGN);

	int error = 0;
	socklen_t len = sizeof (error);
	int retval = getsockopt (descriptor, SOL_SOCKET, SO_ERROR, &error, &len);

	//To test if the socket is up:

	if (retval != 0) {
		/* there was a problem getting the error code */
		fprintf(stderr, "error getting socket error code: %s\n", strerror(retval));
		//return;
	}

	if (error != 0) {
		/* socket has a non zero error status */
		fprintf(stderr, "socket error: %s\n", strerror(error));
		/*if connection was broken, it is recommended to remove particular descriptor*/
		clients.erase(std::remove(clients.begin(), clients.end(), 8), clients.end());

	}

	else
	{
		write(descriptor , data , strlen(data));
	}
} 


void receiveMessages(int descriptor)
{
	char data[1024];
	while(true)
	{
		memset(data, 0, strlen(data)); 
		if(read(descriptor,data,1024)>0)   
		{
			puts(data);

			for(int i:clients)
			{
				/*do not send message to a sender*/
				if(descriptor!=i)
				{
					std::thread bm(sendMessage,i,std::string(data).c_str());
					bm.detach();
				}
			}
		}
	}
} 



int main( int argc, char** argv)
{
	primary.setup(atoi(argv[1]));
	primary.start();
	std::cout<<"started\n";

	while(true)
	{ 

		if(primary.acceptConnection())
		{
			std::cout<<"client connected\n";
			clients.push_back(primary.incomingConnection);
			std::thread two(receiveMessages, primary.incomingConnection);
			two.detach(); 
		}
		else
		{
			std::cout<<"something went wrong while accepting connection \n"; 
		}

	}




}
