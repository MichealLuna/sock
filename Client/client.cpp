#include "client.h"

using namespace Luna;
using namespace Tcp;
TcpClient::TcpClient(const char* ip,u_short port)
{
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
            TcpFatal("Connection server");
        }

        std::cout<<"Client has connected to "<<ip<< " "
                <<port<<std::endl;
}

ssize_t TcpClient::send(const char* buf,size_t len,int flags){
   return  ::send(connfd,buf,len,flags);
}

ssize_t TcpClient::send_oob(const char* buf,size_t len){
    return ::send(connfd,buf,len,MSG_OOB);
}

ssize_t TcpClient::recv(char* buf,size_t len,int flags){
   return  ::recv(connfd,buf,len,flags );
}

ssize_t TcpClient::recv_oob(char* buf,size_t len){
    return ::recv(connfd,buf,len,MSG_OOB);
}

TcpClient::~TcpClient(){
    close(connfd);
    std::cout<<"Client has closed."<<std::endl;
}
