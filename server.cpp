#include "TcpServer.cpp" 
#include <thread>
#include <vector>
#include <mutex>

TcpServer primary; 
std::vector<int> clients;

void sendMessage(int descriptor,const char* data)
{
	write(descriptor , data , strlen(data));
}



void broadcastMessages()
{ 
	for(int i: clients)
	{
		std::thread bm(sendMessage,i,"what ever");
		bm.detach();
	} 
}


void receiveMessages(int descriptor)
{
	char data[1024];
	while(true)
	{
		memset(data, 0, sizeof(data)); 
		read(descriptor,data,1024);   
		puts(data);
		//std::cout<<data;

		for(int i:clients)
		{
			sendMessage(i,std::string(data).c_str()); 
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
			std::thread two(receiveMessages,primary.incomingConnection);
			two.detach();




		}
		else
		{
			std::cout<<"something went wrong while accepting connection \n"; 
		}

	}




}
