#include "server.h"

namespace Luna{
    namespace Tcp{

    TcpServer::TcpServer(const char* ip,u_int16_t port){
        //init sockaddr_in
        bzero(&m_servaddr,sizeof(m_servaddr));
        m_servaddr.sin_family = AF_INET;
        m_servaddr.sin_port = htons(port);
        inet_pton(AF_INET,ip,&m_servaddr.sin_addr);

        if( (m_listen_sock = socket(AF_INET,SOCK_STREAM,0)) <= 0 ){
            TcpFatal("Create m_listen_sock failed!");
        }

        //bind
        if( bind(m_listen_sock,(SA*)&m_servaddr,sizeof(m_servaddr)) < 0 ){
            TcpFatal("binding socket address failed!");
        }
    }

    void TcpServer::listen(int maxList){
        if( ::listen(m_listen_sock,maxList) < 0 ){
            TcpFatal("listening failed!");
        }
    }

    int TcpServer::accept(){
        m_client_sock_len = sizeof(m_clientaddr);
        if( (m_client_sock = ::accept(m_listen_sock,(SA*)&m_clientaddr,&m_client_sock_len)) < 0 ){
            TcpError("accepting failed!");
        }
        return m_client_sock;
    }

    ssize_t TcpServer::recv(char* buf,size_t len,int flags){
        return ::recv(m_client_sock,buf,len,flags);
    }

    ssize_t TcpServer::send(const char* buf,size_t len,int flags){
        return ::send(m_client_sock,buf,len,flags);
    }

    void TcpServer::close_client(){
        close(m_client_sock);
        bzero(&m_clientaddr,sizeof(m_clientaddr));
        m_client_sock = -1;
    }

    TcpServer::~TcpServer(){
        close(m_client_sock);
        close(m_listen_sock);
    }

    }//Tcp
}//Luna