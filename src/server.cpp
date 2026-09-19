#include "server.hpp"
#include "utils.hpp"
#include "protocol.hpp"


Server::Server(const std::string& palavra) : jogo(palavra){}

int Server::init(){
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if(sockfd < 0){
			perror("socket");
			return -1;
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
		

		std::cout << "SERVER::LISTENING_ON_PORT: " << this->port << std::endl;
		std::cout << "SERVER::ACTUAL_WORD: " << jogo.getPalavra() << std::endl;

		while(true){
			struct sockaddr_in caddr;
			socklen_t clen = sizeof(caddr);
			int fd = accept(sockfd, (struct sockaddr*)&caddr, &clen);

			if(fd < 0){
				perror("accept");
				continue;
			}
			std::cout << "SERVER::NEW_CLIENT: " << fd << std::endl;
			std::cout << "SERVER::CLIENT_IP: " << inet_ntoa(caddr.sin_addr) << std::endl;

			std::lock_guard<std::mutex> lock(mtx);
			clients.push_back(fd);
			names.push_back("");
			
			std::thread(&Server::acceptClient, this, fd).detach();
		}
		return 0;
}

int Server::getIndiceOf(int fd){
	for(size_t i = 0; i < clients.size(); i++){
		if(clients[i] == fd) return static_cast<int>(i);
	}

	return -1;
}

std::string Server::actualState(){
	std::string s = jogo.getEstado();
	s += "\nE a vez do(a): ";
	if(names.empty() || actualPlayer >= (int)names.size()){
		s += "ninguem...";
	}
	else {
		s += names[actualPlayer];
	}
	return s;
}

void Server::broadcast(TipoMsg tipo, const std::string& payload){
	std::lock_guard<std::mutex> lock(mtx);
	for(int fd : clients){
		enviarPacote(fd, tipo, payload);
	}
}

void Server::removeClient(int fd){
	std::lock_guard<std::mutex> lock(mtx);
	int i = getIndiceOf(fd);
	if(i < 0) return;
	close(fd);

	clients.erase(clients.begin() + i);
	names.erase(names.begin() + i);

	if(actualPlayer >= (int)clients.size()){
		actualPlayer = 0;	
	}
	std::cout << "SERVER::DISCONNECT_CLIENT: " << fd << std::endl;
}

void Server::acceptClient(int fd){
	TipoMsg tipo;
	std::string payload;

	while(receberPacote(fd, tipo, payload)){
		switch(tipo){
			case LOGIN:{ 
				std::string estado;

				{
				std::lock_guard<std::mutex> lock(mtx);
				int ID = getIndiceOf(fd);
				if(ID < 0) break;
				names[ID] = payload;
				estado = actualState();
				}

				std::cout << "SERVER::RECEIVED_LOGIN: " << payload << std::endl;
				enviarPacote(fd, STATE, estado);
				break;

			}case GUESS:{
				TipoMsg tipoResp = STATE;
				std::string resp;

				{
				std::lock_guard<std::mutex> lock(mtx);
				int ID = getIndiceOf(fd);
				if(ID < 0) break;
				if(ID != actualPlayer) break;
				if(payload.empty()) break;
				}

				jogo.input(payload[0]);
				if(jogo.acabou()){
					tipoResp = END_GAME;
					if(jogo.venceu()){
						resp = "O " + names[actualPlayer] + " ganhou!";
					}
					else{
						resp = "Acabaram as tentativas restantes...";
					}
					resp += jogo.getEstado();
				}
				else{
					if(!clients.empty()){
						actualPlayer = (actualPlayer + 1) % clients.size();
					}
					resp = actualState();
				}
				broadcast(tipoResp, resp);
				break;
			
			}case LOGOUT:
				removeClient(fd);
				return;

			default:
				break;
		}
	}
	removeClient(fd);
}


void Server::setPort(int port){this->port = port;}
int Server::getStatus(){return this->status;}
void Server::closeSock(){close(sockfd);}


