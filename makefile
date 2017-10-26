all:
	g++ -std=c++14 -pthread server.cpp -o server -g
	g++ -std=c++14 -pthread client.cpp -o client -g
