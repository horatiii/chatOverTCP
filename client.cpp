#include "TcpClient.cpp"

int main(int argc,char** argv)
{
	TcpClient tcp;
	if(!tcp.setup(argv[1],atoi(argv[2]))) return -1; 

	if (!tcp.connection()) return -1;


	uint16_t port=atoi(tcp.receive());
	std::cerr<<port;

	TcpClient tcp2;
	if(!tcp2.setup(argv[1],port)) return -1;

	else
	{ 
		std::cerr<<"just here";
		if (!tcp2.connection()) 
		{
		}

		else
			std::cout<<(tcp2.receive());
	}

}
