
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
#include <memory>

#include "UseEpoll.h"
#include "NetClient.h"



#include"../Re3D/base.h"
#include"../Re3D/re3dx.h"
#include"../Re3D/commands.h"

#define CVRENDER_NO_GUI
#include"../Re3D/cvrender.h"
using namespace re3d;

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include"opencv2/imgproc.hpp"
#include"opencv2/highgui.hpp"
#include"opencv2/calib3d.hpp"
using namespace cv;
#include<time.h>


const int LISTEN_LIMIT = 50;
const int USER_LIMIT = 65535;

const int MAX_SHADRED_BUFFER_SIZE = 1024 * 1024 * 5;
class NetServer {

public:
    NetServer() : events_notifer(UseEpoll()),
    clients(USER_LIMIT, std::shared_ptr<NetClient>(nullptr)),
    sharedRecvBuffer(nullptr)
    {
        bzero(&server_address, sizeof(server_address));
        sharedRecvBuffer = new char[MAX_SHADRED_BUFFER_SIZE];
        std::fill(sharedRecvBuffer,sharedRecvBuffer + MAX_SHADRED_BUFFER_SIZE,'0');
    }

    void Init(const std::string &ip,const int &port );

    void Process();

    void CloseServer()
    {
        close(server_socket);
    };


private:

    sockaddr_in server_address;
    int  server_socket;
    bool stopServer = false;

    UseEpoll events_notifer;
    std::vector<shared_ptr<NetClient>> clients;


    char *sharedRecvBuffer;

    void InitServerAddress(const std::string &ip,const int &port);
    void Bind();
    void Listen();
    int Accept();
};


#endif //NETSERVER_H
