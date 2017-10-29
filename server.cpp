#include "TcpServer.cpp" 
#include <thread>
#include <vector>
#include <mutex>
#include <queue>

TcpServer primary;

//std::queue<std::string> globalQueue;
std::vector<std::string> messagesVector;
std::mutex messagesMutex;


void broadcastMessages(int descriptor)
{
	unsigned currentMessagePosition=0;




}


void receiveMessages(int descriptor)
{
	while(true)
	{
		  char data[1024];
      read(descriptor,data,1024);   
			puts(data);

			messagesMutex.lock(); 
			messagesVector.insert(messagesVector.begin(),std::string(data));
			messagesMutex.unlock();
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
			std::thread two(receiveMessages,primary.incomingConnection);
			two.detach();


			
			
		}
		else
		{
			std::cout<<"something went wrong while accepting connection \n"; 
		}

	}


	
	
}
