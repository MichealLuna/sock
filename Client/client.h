#pragma once
#include "../common.h"

namespace Luna{
    namespace Tcp{

class TcpClient{
public:
    TcpClient(const char* ip="127.0.0.1",u_int16_t port=5555);

    ssize_t send(const char* buf,ssize_t len,int flags = 0);

    ssize_t recv(char* buf,ssize_t len,int flags = 0);

    ~TcpClient();
private:
    std::string m_ip;
    uint16_t m_port; 
    int connfd;
    struct sockaddr_in servaddr;
};
    } //Tcp
}//Luna