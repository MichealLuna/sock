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

    ssize_t recv_oob(char* buf,size_t len);

    ssize_t send(const char* buf,size_t len,int flags = 0);

    ssize_t send_oob(const char* buf,size_t len);
    
    void close_client();

    ~TcpServer();

private:
    u_int16_t m_port;   //server port
    std::string m_ip;   //server ip
    int m_listen_sock;  //server listen 
    int m_client_sock;  //accept socket from listen
    struct sockaddr_in m_clientaddr;
    struct sockaddr_in m_servaddr;
    socklen_t m_client_sock_len;
};
    }//Tcp
}//Luna
