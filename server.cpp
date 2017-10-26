#include "TcpServer.cpp" 
#include <thread>
#include <vector>
#include <mutex>

TcpServer primary;
std::vector<int> clients;
std::mutex simpleLock;
char data[1024];

void receiveMessages()
{
	while(true)
	{
	simpleLock.lock();
		for(int i:clients)
		{
      read(i,data,1024);   
			puts(data);
		}
		simpleLock.unlock();
	}
}


void broadcastMessage()
{
	while(true)
	{
		sleep(4);
	std::cout<<"w\n";
	simpleLock.lock();
	for(int i: clients)
	{

		write(i,"whatever data",strlen("whatever data"));
	}
	simpleLock.unlock();
	}



}


void collectClients()
{
	while(true)
	{

		
		if(primary.acceptConnection())
		{
			std::cout<<"client connected\n";
			simpleLock.lock();
			
			clients.push_back(primary.incomingConnection);
			simpleLock.unlock();


		}
		else
		{
			std::cout<<"something went wrong while accepting connection \n"; 
		}

	}
}

int main( int argc, char** argv)
{
	primary.setup(atoi(argv[1]));
	primary.start();
	std::cout<<"started\n";

	std::thread one(collectClients);
	std::thread two(broadcastMessage);
	std::thread three(receiveMessages);
	one.join();
	two.join();
	three.join();

	
	
}
