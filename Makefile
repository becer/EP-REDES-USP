CXX      = g++
CXXFLAGS = -Wall -Wextra -g -Iinclude
BIN      = bin
COMMON   = src/utils.cpp src/protocol.cpp

all: $(BIN)/server $(BIN)/client

$(BIN)/server: src/server_main.cpp src/server.cpp src/forca.cpp $(COMMON)
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN)/client: src/client_main.cpp src/client.cpp $(COMMON)
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(BIN)
