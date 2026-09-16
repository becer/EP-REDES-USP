#include "server.hpp"
#include <netinet/in.h>
#include "protocol.hpp"


Server::Server(const std::string& palavra) : jogo(palavra){}

int Server::init(){
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if(sockfd < 0){
			perror("socket");
			return sockfd;
		}
		
		setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = INADDR_ANY;
		addr.sin_port = htons(this->port);

		status = bind(sockfd, (struct sockaddr*) &addr, sizeof(addr));
		if(status){
			perror("bind");
			close(sockfd);
			return this->status;
		}

		if(listen(sockfd,1) < 0){
			perror("listen");
			close(sockfd);
		}
		listeningState = 1; 
	
		std::thread listen(listenToClient, this->sockfd, &this->listeningState, &this->client_addr, this->addr_len);
		listen.detach();
		
		return 0;
}

void Server::setPort(int port){this->port = port;}
int Server::getStatus(){return this->status;}
void Server::closeSock(){
	listeningState = 0;
	close(clientfd);
	close(sockfd);
}


