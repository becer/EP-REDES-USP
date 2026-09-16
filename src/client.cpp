#include "client.hpp"
#include "protocol.hpp"

Client::Client(){std::cout << "============INICIALIZING CLIENT | ID:" << this->sockfd << "==============" << std::endl;}

int Client::init(){
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		perror("socket");
		return sockfd;
	}
			
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	
	status = connect(sockfd, (struct sockaddr*) &addr, sizeof(addr));
	if(status){
		perror("connect");
		close(sockfd);
		return status;
	}
	std::thread receiveM(receiveMSG, this->receivedText, sockfd);
	std::thread sendM(sendMSG, this->sendedText, sockfd);
		
	receiveM.join();
	sendM.join();

	return 0;
}

void Client::setPort(int port){this->port = port;}
void Client::setIP(const char* IP){inet_aton(IP, &addr.sin_addr);}
int Client::getStatus(){return this->status;}
void Client::closeSock(){close(sockfd);}
