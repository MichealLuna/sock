#include "server.h"

using namespace Luna::Tcp;

int main(int argc,char** argv){
    if(argc < 3){
        std::cout<<"Usage : "<<argv[0]<<" <server ip> <server port>"<<std::endl;
        std::cout<<"Such as: "<<argv[0]<<" 192.168.245.128 5555"<<std::endl;
        exit(-1);
    }

    //create 
    TcpServer server(argv[1]);

    //listen
    server.listen(5);
    
    char buf[1024];
    memset(buf,0,sizeof(buf));
    for(;;){
        //blocking here.
        server.accept();

        while( server.recv(buf,sizeof(buf)) > 0 )
        {
            std::cout<<"recv: "<<buf<<std::endl;

            //recv oob
            memset(buf,0,sizeof(buf));
            server.recv_oob(buf,sizeof(buf));
            std::cout<<"MSG_OOB: "<<buf<<std::endl;

            //send
            memset(buf,0,sizeof(buf));
            sprintf(buf,"This is Luna Server Over!");
            server.send(buf,sizeof(buf));
            std::cout<<"send: "<<buf<<std::endl;

            // //send oob
            // memset(buf,0,sizeof(buf));
            // sprintf(buf,"This is emergent msg from server!");
            // server.send_oob(buf,strlen(buf));

            memset(buf,0,sizeof(buf));
        }

        server.close_client();
    }

    return 1;
}