#ifndef SERVER_HPP
#define SERVER_HPP

#include <asm-generic/socket.h>
#include <cstdio>
#include <string>
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
#include <mutex>
#include "protocol.hpp"

class Server{
private:
	int sockfd = -1, status = 0, port = 8888, opt = 1;
	struct sockaddr_in addr;

	Forca jogo;

	std::vector<int> clients;
	std::vector<std::string> names;
	std::mutex mtx;
	int actualPlayer = 0;

	void acceptClient(int fd);
	void broadcast(TipoMsg tipo, const std::string& payload);
	void removeClient(int fd);
	int getIndiceOf(int fd);
	std::string actualState();
	void waitNewWord();

public:
	Server(const std::string& palavra);
	int init();
	void setPort(int port);
	int getStatus();
	void closeSock();
};

#endif
