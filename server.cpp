#include "TcpServer.cpp" 
#include <thread>
#include <vector>

TcpServer primary;
std::vector<TcpServer*> clients;
uint16_t currentPort=9000;

uint16_t getPortNumber()
{
	return ++currentPort;
}

void broadcastMessage()
{

}

bool redirectClient()
{
	TcpServer s;
	uint16_t port = getPortNumber();

	if(!s.setup(port)) 
		return false;

	if(!s.start()) 
		return false; 


		
	else 
	{

		primary.send((std::to_string(port)).c_str());

	}

	
		std::cerr<<"accepting connection"; 
		if(s.acceptConnection())
		{
			s.send("redirection succeeded");
			return true;
		}
		else
		{
			return false;
			
		}
	
}

void collectClients()
{
	while(true)
	{

		
		if(primary.acceptConnection())
		{
			if(redirectClient())
			{

			}
			else
			{
			}
		}
		else
		{
				
		}

	}
}

int main( int argc, char** argv)
{
	primary.setup(atoi(argv[1]));
	primary.start();
	std::cerr<<"started";

	std::thread one(collectClients);
	one.join();

	
	
}
