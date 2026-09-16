#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <cstdint>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>

enum tipoMsg : uint8_t{
	LOGIN      = 0x01;
	GUESS      = 0x02;
	STATE      = 0x03;
	END_GAME   = 0x04;
	LOGOUT     = 0x05;
}

bool enviarPacote(int fd, tipoMsg tipo, const std::string& payload);
bool receberPacote(int fd, tipoMsg& tipo, std::string& payload);


#endif

