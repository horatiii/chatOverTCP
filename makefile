all:
	g++ -std=c++14 -pthread  server.cpp -o server
	g++ -std=c++14  client.cpp -o client
