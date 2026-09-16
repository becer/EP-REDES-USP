#ifndef FORCA_HPP
#define FORCA_HPP

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

class Forca{
private:
	std::string palavra;
	std::string palavraHash;
	std::vector<char> tentativas;
	int tentRestante;
	int letrasAdescobrir;
	bool vitoria;
	bool acertou;
public:
	Forca(const std::string& palavra);
	std::string input(char input);
	std::string getDraw() const;
	bool acabou();


};

#endif
