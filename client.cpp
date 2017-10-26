#include "TcpClient.cpp"
#include <thread>


std::string data; 
TcpClient tcp; 


void passMessages()
{

	//std::cin>>data; 
	//write(tcp.descriptor,data.c_str(),strlen(data.c_str()));
	for(;;){
	write(tcp.descriptor,"x",strlen("x"));
	sleep(2);
	}

}

void receiveMessages()
{ 
	while(true) 
	{

		//std::cout<<"received :  "<<tcp.receive();
		//
		puts(tcp.receive());
	}
}

int main(int argc,char** argv)
{
	if(!tcp.setup(argv[1],atoi(argv[2]))) return -1; 

	if (!tcp.connection()) return -1;

	std::thread one(receiveMessages);
	std::thread two(passMessages);
	one.join();
	two.join();






}
