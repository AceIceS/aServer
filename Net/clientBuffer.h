
#ifndef CLIENTBUFFER_H
#define CLIENTBUFFER_H

#include<vector>
#include<iostream>

#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>


class clientBuffer
{
public:
    clientBuffer(int _readsize,int _sendsize)
        :theReadBuffer(_readsize,'0'),theSendBuffer(_sendsize,'0')
        ,startIndex(0),endIndex(0)
    {
    }

    // read = 0
    // read size
    // read frameNo
    // read data
    int ReadData(int &clientsock);

private:

    bool GetPreInfo(int &clientsock);
    bool GetData(int &clientsock);


    //send
    int startIndex;
    int endIndex;
    std::vector<char> theReadBuffer;
    int _realSize;
    int _currentFrameNo;

    //recv
    std::vector<char> theSendBuffer;


};


#endif //CLIENTBUFFER_H
