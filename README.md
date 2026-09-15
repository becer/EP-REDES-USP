[![USP](https://img.shields.io/badge/USP-Universidade%20de%20S%C3%A3o%20Paulo-blue)](https://www.usp.br)

# EP - Jogo da Forca Distribuído

Trabalho prático da disciplina de Redes de Computadores. Consiste em uma
aplicação distribuída cliente-servidor que implementa o jogo da forca em
modo multiplayer via terminal, utilizando comunicação por sockets TCP.

## Descrição

O servidor mantém o estado central do jogo (palavra secreta, letras já
tentadas, número de erros, turno atual) e coordena múltiplos clientes
conectados simultaneamente. Cada cliente se conecta, informa um nome e
passa a receber o estado atualizado do tabuleiro a cada rodada. O jogo
avança em turnos: apenas o jogador da vez pode enviar um chute, e o
resultado é transmitido a todos os clientes conectados.

## Funcionalidades

- Suporte a múltiplos clientes simultâneos no mesmo servidor
- Coordenação de turnos entre jogadores
- Estado do jogo sincronizado entre todos os clientes
- Desenho ASCII da forca atualizado a cada erro
- Encerramento automático ao esgotar tentativas ou descobrir a palavra

## Arquitetura

O projeto segue o modelo cliente-servidor com comunicação via TCP:

- O servidor é responsável por manter o estado do jogo e validar os chutes.
- Cada cliente conectado gera uma thread dedicada no servidor.
- O envio do estado do jogo é feito por broadcast, ou seja, a mesma
  mensagem é enviada a todos os clientes conectados.
- A comunicação utiliza um protocolo próprio de mensagens com cabeçalho
  de tipo e tamanho.

## Estrutura do Projeto

```
EP_Redes/
├── bin/                # Binários gerados pela compilação
├── include/            # Arquivos de cabeçalho (.hpp)
│   ├── client.hpp
│   ├── forca.hpp
│   ├── protocol.hpp
│   ├── server.hpp
│   └── utils.hpp
├── src/                # Código-fonte (.cpp)
│   ├── client.cpp
│   ├── client_main.cpp
│   ├── forca.cpp
│   ├── protocol.cpp
│   ├── server.cpp
│   ├── server_main.cpp
│   └── utils.cpp
├── Makefile
└── README.md
```

## Dependências

- Compilador C++ com suporte a C++17 (g++ ou clang++)
- GNU Make
- Sistema operacional POSIX (Linux ou macOS)

Nenhuma biblioteca externa é necessária. Toda a comunicação é feita
utilizando as APIs de socket da biblioteca padrão do sistema.

## Compilação

O projeto utiliza um Makefile. Para compilar os dois binários:

```sh
make
```

Para compilar apenas o servidor ou apenas o cliente:

```sh
make bin/server
make bin/client
```

Para remover os binários gerados:

```sh
make clean
```

## Execução

Em um terminal, inicie o servidor:

```sh
./bin/server <palavra>
```

O parâmetro `<palavra>` é opcional. Caso não seja informado, o servidor
utiliza um valor padrão definido em código.

Em outros terminais, conecte um ou mais clientes:

```sh
./bin/client <ip_do_servidor>
```

## Protocolo de Comunicação

As mensagens trafegam sobre TCP no seguinte formato:

```
+----------+-----------------+----------------+
| 1 byte   | 2 bytes         | N bytes        |
| tipo     | tamanho (N)     | payload        |
+----------+-----------------+----------------+
```

- O campo `tipo` identifica o tipo da mensagem (ver `protocol.hpp`).
- O campo `tamanho` é um `uint16_t` em network byte order (big-endian).
- O campo `payload` contém os dados da mensagem, sem terminador nulo.

Os tipos de mensagem implementados são: `MSG_LOGIN`, `MSG_GUESS`,
`MSG_GAME_STATE`, `MSG_GAME_OVER` e `MSG_LOGOUT`.

## Autore

- Joao Pedro Becer 

