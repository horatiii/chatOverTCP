#include "TcpServer.cpp" 
bool handleClient(unsigned short port)
{
	TcpServer s;
	if(!s.setup(port)) return false;
	if(!s.start()) return false;
		if(s.acceptConnection())
		{
			s.send("redirection succeeded");
		}
		else
		{
			//puts("redirection did not succeed ");	
			return -1;
			
		}
	
}
int main( int argc, char** argv)
{
	TcpServer s;
	if(!s.setup(atoi(argv[1]))) return -1;
	if(!s.start()) return -1;
	char* designatedPort="9009";

	
	
	while(true)
	{

		
		//std::cout<<"before accept";
		if(s.acceptConnection())
		{
			puts("cout");
			s.send(designatedPort);
			handleClient(9009);
		}
		else
		{
				
		}

	}
}
