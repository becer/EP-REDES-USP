#ifndef SERVER_HPP
#define SERVER_HPP

#include <asm-generic/socket.h>
#include <cstdio>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <string.h>
#include <thread>
#include "utils.hpp"
#include <iostream>
#include "forca.hpp"

class Server{
private:
	int sockfd, clientfd, status, listeningState, port, opt = 1;
	struct sockaddr_in addr, client_addr;
	char receivedText[SIZE], sendedText[SIZE];
	socklen_t addr_len = sizeof(client_addr);
	Forca jogo;

public:
	Server(const std::string &palavra);
	int init();
	void setPort(int port);
	int getStatus();
	void closeSock();
};

#endif
