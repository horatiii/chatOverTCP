#include "TcpClient.cpp"
#include <thread>


std::string data; 
TcpClient tcp; 


void passMessages()
{

	while(true)
	{
		std::cin>>data; 
		tcp.send(data.c_str());
	}

}

void receiveMessages()
{ 
	while(true) 
	{
		//puts("received");

		//std::cout<<"received :  "<<tcp.receive();
		//
		//puts(tcp.receive());
		if(tcp.receive())
			puts(tcp.receivedData);
	}
}

int main(int argc,char** argv)
{
	if(!tcp.setup(argv[1],atoi(argv[2]))) return -1; 

	if (!tcp.connection()) return -1;

	std::thread two(passMessages);
	two.detach();
	std::thread one(receiveMessages);
	one.detach();


	while(true);






}
