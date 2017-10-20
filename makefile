all:
	#g++ -std=c++14 -pthread  server.cpp -o server
	#g++ -std=c++14  client.cpp -o client 
	g++ -std=c++14 auxServer.cpp -g -o server
	g++ -std=c++14  auxClient.cpp -g -o client
