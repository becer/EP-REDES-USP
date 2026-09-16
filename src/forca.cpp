#include "forca.hpp"
#include "utils.hpp"
#include <string>
#include <cstdint>

Forca::Forca(const std::string& palavra){
	this->palavra = palavra;
	this->letrasAdescobrir = palavra.length();
	this->palavraHash = escondePalavra(this->palavra);
	this->tentRestante = 7;
	this->vitoria = false;
	this->acertou = false;
}

std::string Forca::input(char input){
	std::vector<int> indices = compare(this->palavra, input, &acertou);
	revelaPalavra(this->palavraHash, indices, input);

	if(!acertou) this->tentRestante--;
	this->tentativas.push_back(input);
	
	/*montagem da string*/
	std::string output = this->palavraHash;
	output += "\ntentativas: ";
	for(char c : tentativas){
		output += c;
		output += " ";
	}
	output += "\n" + getDraw();
	
	this->letrasAdescobrir -= indices.size();
	return output;
}

bool Forca::acabou(){
	if(this->tentRestante == 0){
		return 1;
	}
	return 0;
}

std::string Forca::getDraw() const{
	switch(this->tentRestante){
case 0:
return R"(
+---------------------------------+                                     
|       __    __  _^_             |
| \  / /  \  /    |__             |
|  \/  \__/  \__  |__             |
|  __  ___  __   __  ___          |                 
| |__| |__ |__| |  \ |__  |  |    |
| |    |__ |  \ |__/ |__  |__|    |
+---------------------------------+
)";
case 1:
return R"(
          _______
         / o  O  \
         \___~___/
)";
case 2:
return R"(
      _______
     / o  O  \
     \___~___/
         |
    -----------
    |  @    @ |
    |         |
    |         |
    |    P    |
    |         |
    -----------
)";
case 3:
return R"(
          _______
         / o  O  \
         \___~___/
             |            
       /^---------      
      / /             
     / /|  @    @ |
    / /	|         |  
    | |	|         | 
    | |	|    P    |
    @@@	|         |
    |||	-----------
)";
case 4:
return R"(
          _______
         / o  O  \
         \___~___/
             |            |
       /^---------^\     ^|^ 
      / /         \ \    @@@
     / /|  @    @ |\ \  / /
    / /	|         | \ \/ / 
    | |	|         |  ---/
    | |	|    P    |
    @@@	|         |
    |||	-----------
)";
case 5:
return R"(
          _______
         / o  O  \
         \___~___/
             |            |
       /^---------^\     ^|^ 
      / /         \ \    @@@
     / /|  @    @ |\ \  / /
    / /	|         | \ \/ / 
    | |	|         |  ---/
    | |	|    P    |
    @@@	|         |
    |||	-----------
       /  /     
      /  /       
      {  |        
       \  \
     {_____) 
)";
case 6:
return R"(
          _______
         / o  O  \
         \___~___/
             |            |
       /^---------^\     ^|^ 
      / /         \ \    @@@
     / /|  @    @ |\ \  / /
    / /	|         | \ \/ / 
    | |	|         |  ---/
    | |	|    P    |
    @@@	|         |
    |||	-----------
       /  /     \  \
      /  /       \  \
      {  |        |  }
       \  \       /  /
     {_____)      (____} 
)";
case 7:
return R"(
          _______
         / o  O  \
         \___~___/
             |            |
       /^---------^\     ^|^ 
      / /         \ \    @@@
     / /|  @    @ |\ \  / /
    / /	|         | \ \/ / 
    | |	|         |  ---/
    | |	|    P    |
    @@@	|         |
    |||	-----------
       /  / @ @ \  \
      /  /   ||  \  \
      {  |    @   |  }
       \  \       /  /
     {_____)      (____} 
)";
	}
	return "";
}
