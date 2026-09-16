#include "server.hpp"
#include <chrono>
#include <exception>
#include <thread>
#include <iostream>

int main(){
	int porta;
	std::string palavra;
	try {
		std::cout << "Digite a palavra desejada: " << std::endl;
		std::cin >> palavra;
		std::cout << "Digite a porta a ser aberta pelo servidor: " << std::endl;
		std::cin >> porta;

		Server servidor(palavra);
		servidor.setPort(porta);
		servidor.init();

	} catch (const std::exception& e) {
		std::cerr << "Erro: " << e.what() << std::endl;
		return 1;
	}

	//std::this_thread::sleep_for(std::chrono::seconds(540)); //7min
	//servidor.closeSock();
}
