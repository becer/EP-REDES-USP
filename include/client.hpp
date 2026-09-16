#ifndef CLIENT_HPP
#define CLIENT_HPP 

#include <cstdio>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <thread>
#include "utils.hpp"
#include <iostream>

class Client{
private:
	int sockfd, status, port, IP;
	struct sockaddr_in addr;
	char receivedText[SIZE], sendedText[SIZE];
public:
	Client();

	int init();

	void setPort(int port);
	void setIP(const char* IP);
	int getStatus();
	void closeSock();
};

#endif
