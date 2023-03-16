
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<signal.h>

#include<cstring>
#include<iostream>

void TcpClientFatal(const std::string& fatal){
    std::cout<<"TcpClient Fatal:"<<fatal<<std::endl;
    exit(-1);
}

void TcpClientError(const std::string& error){
    std::cout<<"TcpClient Error:"<<error<<std::endl;
}

typedef struct sockaddr SA;

class TcpClient{
public:
    TcpClient(const char* ip="localhost",u_short port=5555){
        m_ip = ip;
        m_port = port;

        //init server address 
        bzero(&servaddr,sizeof(servaddr));   // bzero  in the cstring,
        servaddr.sin_family = AF_INET;
        servaddr.sin_port   = htons(port);
        inet_pton(AF_INET,ip,&servaddr.sin_addr);
        
        //we also need socket in a Tcpclient which is used for connection!!!
        connfd = socket(AF_INET,SOCK_STREAM,0);

        //connect,connect function return value is -1 or 0 Not a connection socket!
        if ( connect(connfd,(SA*)&servaddr,sizeof(servaddr)) < 0 ){
            TcpClientFatal("Connection server");
        }

        std::cout<<"Client has connected to "<<ip<< " "
                <<port<<std::endl;
    }

    ssize_t TcpSend(const char* buf,ssize_t len,int flag = 0){
       return  send(connfd,buf,len,flag);
    }

    ssize_t TcpRecv(char* buf,ssize_t len,int flag = 0){
       return  recv(connfd,buf,len,flag );
    }

    ~TcpClient(){
        close(connfd);
        std::cout<<"Client has closed."<<std::endl;
    }
private:
    std::string m_ip;
    uint16_t m_port; 
    int connfd;
    struct sockaddr_in servaddr;
private:
    // std::string m_recv;
    // std::string m_send;
};


int main(int argc,char** argv){
    if(argc <= 2){
        std::cout<<"Using "<<argv[0]<<" <server ip> <server port>"<<std::endl;
        exit(-1);
    }

    TcpClient aclient(argv[1],atoi(argv[2]));

    char sendbuf[128];
    memset(sendbuf,0,sizeof(sendbuf));
    sprintf(sendbuf,"Are you okay?");

    for(int i = 0; i < 10 ; ++i){
        ssize_t bytes = aclient.TcpSend(sendbuf,strlen(sendbuf));
        std::cout<<"Data has send byte: "<<bytes<<std::endl;

        char recvbuff[128];
        memset(recvbuff,0,sizeof(recvbuff));

        aclient.TcpRecv(recvbuff,sizeof(recvbuff));
        std::cout<<"["<<i<<"]:"<<"recv length:"<<strlen(recvbuff)<<"\nmessage:" << recvbuff<<std::endl;
    }
    return 1;
}
