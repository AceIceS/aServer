#ifndef USEEPOLL_H
#define USEEPOLL_H

#include <sys/epoll.h>
#include<fcntl.h>
#include <exception>

#include <vector>
#include <iostream>
#include <unistd.h>
#include <memory>

#include "TimeWheel.h"

const int EVENT_LIMIT = 100;

enum EVENT_TYPES
{
    NEW_CONNECTION,
    READ_EVENT,
    WRITE_EVENT,
    DISCONNECT,
    TIMEOUT
};

struct EpollInfo
{
    EpollInfo(){}
    ~EpollInfo()
    {
        if(e != nullptr)
            delete  e;
        if(res_sockets != nullptr)
            delete res_sockets;

        //std::cout<<"EpollInfo Released"<<std::endl;
    }
    EVENT_TYPES *e;
    int *res_sockets;
    int _size;
};

class UseEpoll {

public:

    UseEpoll() :epollfd(0), events(EVENT_LIMIT,epoll_event())
    ,timeWheel(TimeWheel(5))
    {
        epollfd = epoll_create(100);
        AddNewEvent(timeWheel.TimeFD());
    }

    int AddNewEvent(int clientfd,int kind  = 0);
    int RegistWriteEvent(int clientfd);
    int CancelWriteEvent(int clientfd);
    int DelClientEvent(int clientfd);

    //get events
    EpollInfo* GetEvents(const int &server_socket);

    //dealing timeout
    void TimeOut()
    {
        timeWheel.Tick();
    }
    void UpdateThisNetClientTimeout(shared_ptr<NetClient> &ptr,int &sock)
    {
        timeWheel.AddTimer(ptr,sock);
    }
private:
    //some functions
    int SetNonBlocking(int fd);

    int epollfd;
    //a vector used to get events in epoll_wait
    std::vector<epoll_event> events;

    TimeWheel timeWheel;
};


#endif //USEEPOLL_H
