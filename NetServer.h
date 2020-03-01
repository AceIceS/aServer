
#ifndef NETSERVER_H
#define NETSERVER_H


#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <unistd.h>

#include <string>
#include <string.h>
#include <vector>
#include <iostream>

#include "UseEpoll.h"
#include "NetClient.h"

const int LISTEN_LIMIT = 50;
const int USER_LIMIT = 65535;

const int MAX_SHADRED_BUFFER_SIZE = 1024 * 1024 * 5;
class NetServer {

public:
    NetServer() : events_notifer(UseEpoll()),clients(USER_LIMIT,NetClient()),sharedRecvBuffer(nullptr)
    {
        bzero(&server_address, sizeof(server_address));
        sharedRecvBuffer = new char[MAX_SHADRED_BUFFER_SIZE];
        std::fill(sharedRecvBuffer,sharedRecvBuffer + MAX_SHADRED_BUFFER_SIZE,'0');
    }

    void Init(const std::string &ip,const int &port );

    void Precess();

    void CloseServer()
    {
        close(server_socket);
    };

private:

    sockaddr_in server_address;
    int  server_socket;
    bool stopServer = false;

    UseEpoll events_notifer;
    std::vector<NetClient> clients;

    char *sharedRecvBuffer;

    void InitServerAddress(const std::string &ip,const int &port);
    void Bind();
    void Listen();
    int Accept();
};


#endif //NETSERVER_H
