#include "TcpClient.cpp"

int main(int argc,char** argv)
{
	Tcp tcp;
	if(!tcp.setup(argv[1],atoi(argv[2]))) return -1; 
	
	if (!tcp.connection()) return -1;

	puts(tcp.receive());
	//std::cout<<tcp.receive();
	//usleep(1e6); //one second
	
	//Tcp tcp2;
	//if(!tcp2.setup(argv[1],atoi(tcp.receive()))) return -1;
	//if (!tcp.connection()) return -1;
	//std::cout<<(tcp2.receive());
			
}
