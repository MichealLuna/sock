#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<signal.h>
#include<assert.h>
#include<cstring>
#include<iostream>


typedef struct sockaddr SA;

static bool stop = false;

static void handle_sig(int sig){
	stop = true;
}

int main(int argc,char** argv)
{
	if(argc != 3){
		std::cout<<"Usage: server <ip> <port>"<<std::endl;
		exit(-1);
	}

	int fd;
	fd = socket(PF_INET,SOCK_STREAM,0);
	if(fd < 0){
		std::cout<<"Create a socket failed."<<std::endl;
		exit(-1);
	}

	int port = atoi(argv[2]);
	const char* ip = argv[1];

	struct sockaddr_in servaddr;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	inet_pton(AF_INET,ip,&servaddr.sin_addr);

	//bind
	if( bind(fd,(SA*)&servaddr,sizeof(servaddr)) == -1 ){
		std::cout<<"bind socket address failed."<<std::endl;
		exit(-1);
	}	

	//listen
	if( listen(fd,5) == -1 ){
		std::cout<<"listen failed."<<std::endl;
		exit(-1);
	}	

	signal(SIGTERM,handle_sig);
	while(!stop){
		sockaddr_in clientaddr;
		socklen_t clientaddr_len = sizeof(clientaddr);
		bzero(&clientaddr,sizeof(clientaddr));
		
		//accept
		int clientfd = accept(fd,(SA*)&clientaddr,&clientaddr_len);

		//recv
		char recvbuff[1024];
		memset(recvbuff,0,sizeof(recvbuff));

		while( recv(clientfd,recvbuff,sizeof(recvbuff),0) >0){
			std::cout<<recvbuff<<std::endl;
			memset(recvbuff,0,sizeof(recvbuff));

			//response
			char sendbuff[64];
			memset(sendbuff,0,sizeof(sendbuff));
			sprintf(sendbuff,"Got it!\n");
			send(clientfd,sendbuff,sizeof(sendbuff),0);
		}
		close(clientfd);
	}

	return 1;
}
