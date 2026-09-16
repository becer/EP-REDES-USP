#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cerrno>
#include <thread>
#include <vector>
#include <string>

const int SIZE = 256;

void receiveMSG(char* receivedText, int status);

void sendMSG(char* sendedText, int sockfd);


void listenToClient(int	sockfd, int* listeningState, struct sockaddr_in *client_addr, socklen_t addr_len);	

std::vector<int> compare(const std::string& palavra, char input, bool *acertou);
std::string escondePalavra(const std::string& palavra);
void revelaPalavra(std::string& palavraEscondida, const std::vector<int>& indices, char input);

#endif 
