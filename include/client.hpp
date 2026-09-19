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
#include "protocol.hpp"

class Client{
private:
	int sockfd = -1, port = 8888;
	struct sockaddr_in addr;
	std::string nome;

	void threadReceive();
	void threadSend();

public:
	Client();

	int init();

	void setPort(int port);
	void setIP(const std::string& IP);
	int getStatus();
	void closeSock();
};

#endif
