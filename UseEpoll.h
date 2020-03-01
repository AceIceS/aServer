#ifndef USEEPOLL_H
#define USEEPOLL_H

#include <sys/epoll.h>
#include<fcntl.h>
#include <exception>

#include <vector>

const int EVENT_LIMIT = 100;
const int FD_LIMIT = 65535;

enum EVENT_TYPES
{
    NEW_CONNECTION,
    READ_EVENT,
    WRITE_EVENT,
    DISCONNECT,

};

struct EpollInfo
{
    EVENT_TYPES *e;
    int *res_sockets;
    int _size;
};

class UseEpoll {

public:

    UseEpoll() :epollfd(0), events(EVENT_LIMIT,epoll_event())
    {
        epollfd = epoll_create(100);
    }

    int AddNewEvent(int clientfd,int kind  = 0);
    int RegistWriteEvent(int clientfd);
    int CancelWriteEvent(int clientfd);
    int DelClientEvent(int clientfd);

    //get events
    EpollInfo* GetEvents(const int &server_socket);

private:
    //some functions
    int SetNonBlocking(int fd);

    int epollfd;
    std::vector<epoll_event> events;

};


#endif //USEEPOLL_H
