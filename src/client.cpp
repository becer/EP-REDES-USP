#include "client.hpp"
#include "protocol.hpp"

Client::Client(){
	std::cout << "============INICIALIZING CLIENT | ID:" << this->sockfd << "==============" << std::endl;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
}

int Client::init(){
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		perror("socket");
		return -1;
	}
			
	addr.sin_port = htons(port);
	
	if(connect(sockfd, (struct sockaddr*) &addr, sizeof(addr)) < 0){
		perror("connect");
		close(sockfd);
		return -1;
	}
	
	std::cout << "Digite o nome a ser chamado: " << std::endl;
	std::cin >> nome;

	enviarPacote(sockfd, LOGIN, nome);
	
	std::thread tRecv(&Client::threadReceive, this);
	std::thread tSend(&Client::threadSend, this);
	tRecv.join();
	tSend.join();

	return 0;
}

void Client::threadReceive(){
	TipoMsg tipo;
	std::string payload;

	while(receberPacote(sockfd, tipo, payload)){
		switch(tipo){
			case STATE:
				std::cout << "\n====STATE====\n" << payload << std::endl;
				break;
			case END_GAME:
				std::cout << "\n====GAME OVER====\n" << payload << std::endl;
				break;
			default:
				break;
		}
	}
	std::cout << "CLIENT::END_CONECTION" << std::endl;
}

void Client::threadSend(){
	std::string line;
	
	while(std::getline(std::cin, line)){
		if(line.empty()) continue;
		if(line == "sair") {
			enviarPacote(sockfd, LOGOUT, "");
			break;
		}
		enviarPacote(sockfd, GUESS, line.substr(0, 1));
	}
}



void Client::setPort(int port){this->port = port;}
void Client::setIP(const std::string& IP){inet_aton(IP.c_str(), &addr.sin_addr);}
void Client::closeSock(){close(sockfd);}
