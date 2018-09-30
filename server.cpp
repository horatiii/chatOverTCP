#include "TcpServer.cpp"
#include <thread>
#include <vector>
#include <csignal>
#include <algorithm>

TcpServer primary;
std::vector<int> clients;
char welcomeMessage[1024]="Welcome to Superior Chat";

void sendMessage(int descriptor, char* data)
{
	signal(SIGPIPE, SIG_IGN);

	int errorCode = 0;
	socklen_t len = sizeof (errorCode);
	int retval = getsockopt (descriptor, SOL_SOCKET, SO_ERROR, &errorCode, &len);

	if (retval != 0)
	{
		std::cerr <<"error while getting socket error code: "<< strerror(retval) << std::endl;
	}

	if (errorCode != 0)
	{
		std::cerr <<"socket error:  "<< strerror(errorCode) << std::endl;
		std::vector<int>::iterator it = std::find(clients.begin(), clients.end(), descriptor);
		if(it != clients.end())
		{
			clients.erase(it);
		}
	}
	else
	{
		std::size_t writtenBytes;
		if( (writtenBytes=write(descriptor , data , strlen(data)))>0)
		{
			printf("\t d: %d, %lu bytes : %s \n",descriptor,writtenBytes,data);
		}
		else
		{
			std::cerr <<"failed to send.  "<<descriptor<<data<< strerror(errno) << std::endl;
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

			usleep(10000);

			std::thread welcome(sendMessage,incomingConnection,welcomeMessage);
			welcome.detach();
		}
		else
		{
			std::cerr <<"error while accepting connection:  "<< strerror(errno) << std::endl;
		}
	}
}
