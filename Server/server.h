#include"../common.h"

namespace Luna{
    namespace Tcp{
        
class TcpServer{
public:
    TcpServer(const char* ip = "127.0.0.1",u_int16_t port = 5555);

    TcpServer(const TcpServer&) = delete;
    TcpServer(TcpServer&&) = delete;
    TcpServer& operator=(const TcpServer) = delete;
    TcpServer& operator=(TcpServer&&) = delete;

    void listen(int maxList);

    int accept();

    ssize_t recv(char* buf,size_t len,int flags = 0);

    ssize_t send(const char* buf,size_t len,int flags = 0);

    void close_client();

    ~TcpServer();

private:
    u_int16_t m_port;
    std::string m_ip;
    int m_listen_sock;
    int m_client_sock;
    struct sockaddr_in m_clientaddr;
    socklen_t m_client_sock_len;
    struct sockaddr_in m_servaddr;
};
    }//Tcp
}//Luna
