#include "TcpClient.cpp"
#include <ncurses.h>
#include <thread> 
#define BEG_X 30
#define BEG_Y 1


//std::string dataToSend;
TcpClient tcp; 

void passMessages()
{ 
	char x[1024]={0};
	while(true)
	{
		memset(x, 0, sizeof(x)); 

		//if(scanf("%s",dataToSend)>0) 
		//if(getline(std::cin,dataToSend))
		//tcp.send(dataToSend.c_str());
		if(getstr(x)>=0)
		{
			tcp.send(x);
		}
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
	newterm(NULL,stdout,stderr);
	//initscr();
	WINDOW* mw = newwin(25,50,BEG_Y,BEG_X);
	//WINDOW* myBox = newwin(5,5,BEG_Y,BEG_X);
	//box(myBox,0,0);
	//wrefresh(myBox);
	
	mvwprintw(mw, 1,1,"hello on chat!\n");
	wrefresh(mw);
	box(mw, 0, 0);  // added for easy viewing
	scrollok(mw, TRUE);



	std::thread one(passMessages);
	one.detach();

	while(true) 
	{
		if(tcp.receive())
		{
			//box(myBox,0,0);
			//mvwprintw(mw, 1,1,tcp.receivedData);
			waddstr(mw,tcp.receivedData);
			//box(mw, 0, 0);  // added for easy viewing
			waddstr(mw,"\n");

			wrefresh(mw);
			//wrefresh(myBox);
		}
		else
		{
			perror("server must have terminated");
			return -1;
		}
	} 
	delwin(mw);
	return 0;
}
