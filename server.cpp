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
			puts("redirection did not succeed ");	
		}
	
}
int main( int argc, char** argv)
{
	TcpServer s;
	if(!s.setup(atoi(argv[1]))) return -1;
	if(!s.start()) return -1;

	
	
	while(true)
	{

		if(s.acceptConnection())
		{
			s.send("9009");
			handleClient(9009);
		}
		else
		{
			puts("not ok");	
		}

	}
}
