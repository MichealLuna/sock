#pragma once 

#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<signal.h>
#include<cstring>
#include<iostream>

typedef struct sockaddr SA;

static void TcpFatal(const std::string& fatal){
    std::cout<<"Tcp Fatal:"<<fatal<<std::endl;
    exit(-1);
}

static void TcpError(const std::string& error){
    std::cout<<"Tcp Error:"<<error<<std::endl;
}


