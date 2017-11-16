#include "TcpClient.cpp"
#include <thread> 

std::string dataToSend;
TcpClient tcp; 

void passMessages()
{ 
	while(true)
	{
		//memset(dataToSend, 0, sizeof(dataToSend)); 

		//if(scanf("%s",dataToSend)>0) 
		if(getline(std::cin,dataToSend))
			tcp.send(dataToSend.c_str());
		else
		{
			perror("server must have terminated");
			return;
		}
	} 

} 


int main(int argc,char** argv)
{
	if(!tcp.setup(argv[1],atoi(argv[2]))) return -1; 
	if (!tcp.connection()) return -1;

	std::thread one(passMessages);
	one.detach();

	while(true) 
	{
		if(tcp.receive())
			puts(tcp.receivedData); 
		else
		{
			perror("server must have terminated");
			return -1;
		}
	} 
}
