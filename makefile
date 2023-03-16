CXX = g++
CFLAGS = -g

all:server client

server:server.cpp
	$(CXX) $(CFLAGS) -o $@ $^

client:client.cpp
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	rm -rf server
	rm -rf client
