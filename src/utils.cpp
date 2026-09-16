#include "utils.hpp"


void receiveMSG(char* receivedText, int sockfd){
	while(true){	
		memset(receivedText, 0, SIZE);
		int n = recv(sockfd, receivedText, SIZE-1, 0);
		if(n > 0){
			printf("\t\tID: %d|%s\n", sockfd, receivedText);
		}
		if(strncmp(receivedText, "sair", 4) == 0){break;}
	}
	close(sockfd);
}

void sendMSG(char* sendedText, int sockfd){
	while(true){
		memset(sendedText, 0, SIZE);
		scanf("%s", sendedText);
		send(sockfd, sendedText, strlen(sendedText), 0);
		if(strncmp(sendedText, "sair", 4) == 0){break;}
	}
}

void listenToClient(int	sockfd, int* listeningState, struct sockaddr_in *client_addr, socklen_t addr_len){
	while(*(listeningState)){
		int clientfd = accept(sockfd, (struct sockaddr*) client_addr, &addr_len);
		if(clientfd < 0){
			perror("accept");
			if(errno == EBADF) break;
			continue;
		}

		/*adicionar tratamento de cliente(criar thread so para ele)*/
		char receivedText[SIZE] = {0};
		char sendedText[SIZE] = {0};
		std::thread receiveM(receiveMSG, receivedText,clientfd);
		std::thread sendM(sendMSG, sendedText, clientfd);
		receiveM.detach();
		sendM.detach();
	}
}

std::vector<int> compare(const std::string &palavra, char input, bool *acertou){
	std::vector<int> indices;
	for(size_t i = 0; i < palavra.size(); i++){
		if(palavra[i] == input){indices.push_back(i);}
	}
	*acertou = !indices.empty();
	return indices;
}

std::string escondePalavra(const std::string &palavra){
	return std::string (palavra.length(), '_');
}

void revelaPalavra(std::string& palavraEscondida, const std::vector<int>& indices, char input){
	for(uint8_t i = 0; i < indices.size(); i++){ palavraEscondida.at(indices[i]) = input;}
}

