#include "client.h"

using namespace Luna::Tcp;

int main(int argc,char** argv){
    if(argc < 3){
        std::cout<<"Usage : "<<argv[0]<<" <server ip> <server port>"<<std::endl;
        std::cout<<"Such as: "<<argv[0]<<" 192.168.245.128 5555"<<std::endl;
        exit(-1);
    }

    //create 
    TcpClient client(argv[1]);

    char buf[1024];
    for(int i = 0; i < 6; ++i){
        memset(buf,0,sizeof(buf));
        sprintf(buf,"I am Micheal Luna.what server do you provide?");
        client.send(buf,strlen(buf));

        //recv
        memset(buf,0,sizeof(buf));
        client.recv(buf,sizeof(buf));
        std::cout<<"["<<i<<"]"<<"recv: "<<buf<<std::endl;

        //send oob
        client.send_oob("This is emergent msg from client!",33);

        //recv_oob
        // memset(buf,0,sizeof(buf));
        // client[i].recv_oob(buf,sizeof(buf));
        // std::cout<<"MSG_OOB: "<<buf<<std::endl;

        //必须得关闭，因为当前的server每次只能处理一个连接，并且得等到连接关闭之后，才处理下一个连接！(网络死锁)
        //client.~TcpClient();
    }

    return 1;
}