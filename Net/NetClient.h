

#ifndef NETCLIENT_H
#define NETCLIENT_H

#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>

#include <string>
#include <string.h>
#include<stdlib.h>
#include <iostream>
#include<vector>


#include "clientBuffer.h"

const int CLIENT_RECV_BUF_SIZE = 5242880;
const int CLIENT_SND_BUF_SIZE = 1024;

//request at least 5MB recv buffer
const int DEMAND_RECV_BUFFER_SIZE = 1024 * 1024 * 5;

struct Message2Client
{
    float data[6];
};


class NetClient{

public:

    NetClient(){}

    NetClient(int socketfd,struct sockaddr_in address) :
            client_socket(socketfd),client_address(address)
    {
        //initialize send buffer
        //The size of send buffer is fixed,and can be reused
        send_buffer = new char[CLIENT_SND_BUF_SIZE];
        //fill every char with '0'
        ResetSendBuffer();
        realSize = -1;
        readingMessage = false;
        //modify socket option
        SetSocketOpt();
    }

    ~NetClient()
    {
        if(client_socket > 0)
            shutdown(client_socket,SHUT_RDWR);
        std::cout<<"========Client kicked,call NetClient destorier"<<std::endl;
    }
    void SetClientSocket(sockaddr_in client_addr,int client_sock)
    {
        client_address = client_addr;
        client_socket = client_sock;
    }

    //first get real length,then allocate enough memory for vector
    int GetMessageLength(char *buffer,int _size);
    bool GetMessage(char *buffer,int _size);
    bool RecvInformation(char *buffer,int _size);

    //receive and send
    //get results from algorithm
    void GetAlgorithmResult(float *results);
    void SendMessage();

    void Reset();
    std::string  ShowCLientIPandPort();

private:
    //need to reset send buffer every time.
    void ResetSendBuffer();

    //when call this function,means client has disconnected from server
    //a new connection comes,so free write memory.
    void ClearReceiveBuffer();

    void SetSocketOpt();

    sockaddr_in client_address;
    int  client_socket;

    char *send_buffer;
    int send_size;

    //how to inplement recv buffer ?
public:

    std::vector<char> recvBuffer;
    int realSize;
    int currentFrameNo;
    bool readingMessage;

    //buffer used to read and send message
    //clientBuffer theBuffer;
};


#endif //NETCLIENT_H
