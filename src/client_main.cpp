#include "client.hpp"
#include <exception>
#include <iostream>


int main(){
	
	std::string IP = "127.0.0.1";
	int porta = 8888;

	try{
		std::cout << "Digite o IP: " << std::endl;
		std::cin >> IP;
		std::cout << "Digite a porta: " << std::endl;
		std::cin >> porta;

		Client cliente;
		cliente.setPort(porta);
		cliente.setIP(IP);
		cliente.init();
	} catch(const std::exception& e){
		std::cerr << "Erro: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
