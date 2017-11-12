#include "TcpClient.cpp"
#include <thread> 

std::string dataToSend; 
TcpClient tcp; 

void passMessages()
{ 
	while(getline(std::cin,dataToSend))
	{

		tcp.send(dataToSend.c_str());
	} 

}

void receiveMessages()
{ 
	while(tcp.receive()) 
	{
		puts(tcp.receivedData); 
	}
}

int main(int argc,char** argv)
{
	if(!tcp.setup(argv[1],atoi(argv[2]))) return -1; 
	if (!tcp.connection()) return -1;

	std::thread one(passMessages);
	one.detach();
	//std::thread two(receiveMessages);
	//two.detach(); 
	//
	//thread is replaced with with while loop below

	while(true) 
	{
		if(tcp.receive())
			puts(tcp.receivedData); 
	}




}
