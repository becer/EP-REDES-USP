#include "utils.hpp"


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

