#include "TcpClient.cpp"
#include <ncurses.h>
#include <thread> 
#define BEG_X 30
#define BEG_Y 1
#define HEIGHT 10
#define WIDTH 30

TcpClient tcp; 

void passMessages()
{ 
	char x[1024]={0};
	while(true)
	{
		memset(x, 0, sizeof(x)); 

		if(getstr(x)==0)
		{
			if(x[0]!='\0')
			{
				if(!tcp.send(x))
				{
					std::cerr <<"server must have terminated:  "<< strerror(errno) << std::endl;
				} 
			}
		}
		else
		{
			//getting from stdin failed	
		}
	} 
} 

int main(int argc,char** argv)
{
	if(!tcp.setup(argv[1],atoi(argv[2]))) return -1; 
	if (!tcp.connection()) return -1;

	//newterm(NULL,stdout,stderr);
	initscr();
	WINDOW* mw = newwin(HEIGHT,WIDTH,BEG_Y,BEG_X);
	wrefresh(mw);
	scrollok(mw, TRUE); 

	std::thread one(passMessages);
	one.detach();

	while(true) 
	{
		if(tcp.receive())
		{
			waddstr(mw,tcp.receivedData);
			waddstr(mw,"\n");

			wrefresh(mw);
		}
		else
		{
			std::cerr <<"server must have terminated:  "<< strerror(errno) << std::endl;
			return -1;
		}
	} 
	delwin(mw);
	return 0;
}
