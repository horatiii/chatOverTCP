#include "TcpServer.cpp" 
#include <thread>
#include <vector>
#include <csignal>
#include <algorithm>
//FILE* file ; 

std::string getCurrentDate()
{
	return std::string(std::to_string(time(0)));
}

//void sigPipeHandler(int signum,int descriptor)
//{
	////std::cout<<
//}

TcpServer primary; 
std::vector<int> clients;

void sendMessage(int descriptor, char* data)
{
	/*this code may look difficult to read, just ignore this function content for now*/
	signal(SIGPIPE, SIG_IGN);
	//std::signal(SIGPIPE,sigPipeHandler);

	int errorCode = 0;
	socklen_t len = sizeof (errorCode);
	int retval = getsockopt (descriptor, SOL_SOCKET, SO_ERROR, &errorCode, &len);

	//To test if the socket is up:

	if (retval != 0) {
		/* there was a problem getting the error code */
		std::cerr <<"error while getting socket error code: "<< strerror(retval) << std::endl;
		
		//return;
	}

	if (errorCode != 0) {
		/* socket has a non zero error status */
		std::cerr <<"socket error:  "<< strerror(errorCode) << std::endl;


		std::vector<int>::iterator it = std::find(clients.begin(), clients.end(), descriptor);
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
			std::cerr <<"failed to send.  "<<descriptor<<data<< strerror(errno) << std::endl;
			//printf("failed to send to descriptror: \t \t %d : %s \n",descriptor,data);
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
		int incomingConnection=primary.acceptConnection();

		if(incomingConnection>=0)
		{
			std::cout<<"client connected  "<<incomingConnection<<std::endl;
			clients.push_back(incomingConnection);
			std::thread two(receiveMessages, incomingConnection);
			two.detach(); 
		}
		else
		{
			std::cout<<"something went wrong while accepting connection \n"; 
		}

	} 
}
