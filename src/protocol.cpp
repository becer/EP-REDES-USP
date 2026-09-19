#include "protocol.hpp"
#include <cstddef>

static bool enviarTudo(int fd, const void* buf, size_t n){
	const char* p = static_cast<const char*>(buf);
	size_t enviados = 0;

	while(enviados < n){
		ssize_t r = send(fd, p + enviados, n - enviados, 0);
		if(r <= 0) return false;
		enviados += static_cast<size_t>(r);
	}
	return true;
}

static bool receberTudo(int fd, void* buf, size_t n){
	char* p = static_cast<char*>(buf);
	size_t recebidos = 0;

	while (recebidos < n){
		ssize_t r = recv(fd, p + recebidos, n - recebidos, 0);
		if(r <= 0) return false;
		recebidos += static_cast<size_t>(r);
	}
	return true;
}

bool enviarPacote(int fd, TipoMsg tipo, const std::string& payload) {
    //cabecalho 1 byte de tipo + 2 bytes de tamanho em network byte order.
    uint8_t  tipoRaw = static_cast<uint8_t>(tipo);
    uint16_t tamRaw  = htons(static_cast<uint16_t>(payload.size()));

    if (!enviarTudo(fd, &tipoRaw, sizeof(tipoRaw))) return false;
    if (!enviarTudo(fd, &tamRaw,  sizeof(tamRaw)))  return false;
    if (!payload.empty()) {
        if (!enviarTudo(fd, payload.data(), payload.size())) return false;
    }
    return true;
}

bool receberPacote(int fd, TipoMsg& tipo, std::string& payload) {
    //ler o cabeçalho completo (1 + 2 bytes).
    uint8_t  tipoRaw = 0;
    uint16_t tamRaw  = 0;

    if (!receberTudo(fd, &tipoRaw, sizeof(tipoRaw))) return false;
    if (!receberTudo(fd, &tamRaw,  sizeof(tamRaw)))  return false;

    tipo = static_cast<TipoMsg>(tipoRaw);
    uint16_t tam = ntohs(tamRaw);

    //ler o payload inteiro, se houver.
    payload.clear();
    if (tam > 0) {
        payload.resize(tam);
        if (!receberTudo(fd, payload.data(), tam)) return false;
    }
    return true;
}
