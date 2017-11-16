#include "TcpServer.cpp" 
#include <thread>
#include <vector>
#include <csignal>
#include <algorithm>

std::string getCurrentDate()
{
	return std::string(std::to_string(time(0)));
}

//FILE* file ; 
TcpServer primary; 
std::vector<int> clients;

void sendMessage(int descriptor, char* data)
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

		auto it = std::find(clients.begin(), clients.end(), descriptor);
		if(it != clients.end())
			clients.erase(it);

	}

	else
	{
		int writtenBytes;
		if( (writtenBytes=write(descriptor , data , strlen(data)))>0)
			printf("\t d: %d, %d bytes : %s \n",descriptor,writtenBytes,data);
		else
		{
			perror("");
			printf("f: \t \t %d : %s \n",descriptor,data);
		}

	}
} 


void receiveMessages(int descriptor)
{
	char data[1024];
	while(true)
	{
		memset(data, 0, sizeof(data)); 
		if(read(descriptor,data,1024)>0)   
		{
			puts(data);


			for(int i:clients)
			{
				/*do not send message to a sender*/
				if(descriptor!=i)
				{
					char newData[1024];
					strcpy(newData,data);
					std::thread bm(sendMessage,i,newData);
					bm.detach();
				}
			}
		}
		else
			return;
	}
} 



int main( int argc, char** argv)
{
	//if((file=fopen(getCurrentDate().c_str(),"w"))==NULL) return -1;
	if(!primary.setup(atoi(argv[1]))) return -1;
	if(!primary.start()) return -1;

	std::cout<<"started\n";

	while(true)
	{ 

		if(primary.acceptConnection())
		{
			std::cout<<"client connected  "<<primary.incomingConnection<<std::endl;
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
