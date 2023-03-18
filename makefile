CXX = g++
CFLAGS = -g

all:server client


server:./Server/*.cpp
	$(CXX) $(CFLAGS) -o $@ $^

client:./Client/*.cpp
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	rm -rf server
	rm -rf client
