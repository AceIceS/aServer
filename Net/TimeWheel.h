
#ifndef TIMEWHEEL_H
#define TIMEWHEEL_H

#include"NetClient.h"

#include<memory>
#include <sys/timerfd.h>
#include <time.h>
#include <sys/fcntl.h>

#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <unistd.h>
using std::shared_ptr;

class Timer
{
public:
    Timer() : client_ptr(nullptr),sockfd(0){}
    Timer(shared_ptr<NetClient> &ptr,int &sockfd) : client_ptr(ptr),sockfd(sockfd){}
    ~Timer()
    {
        //std::cout<<"Timer's destorier"<<std::endl;
        //std::cout<<"Time ... "<<client_ptr.use_count()<<std::endl;
        if(client_ptr.use_count() == 2)
        {
            close(sockfd);
        }
        if(client_ptr.get() != nullptr)
        {
            client_ptr.reset();
            //std::cout<<"Reset client_ptr"<<std::endl;
        }

    }

    shared_ptr<NetClient> client_ptr;
    int sockfd;
private:



};


class TimeWheel{

public:
    TimeWheel(int _t) : timerfd(0),timelimits(_t),
        current_index(0),slots(_t * 2,std::vector<Timer>())
    {
        InitTimeWheel();
    }

    ~TimeWheel()
    {

    };

    // 1. add new client into slots
    // 2. former client recv data,update time by adding a new timer
    void AddTimer(shared_ptr<NetClient> &ptr,int &sock);
    // one call per 10 seconds
    // destory all timer in slots[current_index];
    void Tick();

    int TimeFD()
    {
        return timerfd;
    }

private:

    // set first timeout time
    void InitTimeWheel();
    //start clock one time
    void SetTimeout();

    int timerfd;
    int timelimits;
    struct itimerspec the_time;

    int current_index;
    std::vector<std::vector<Timer>> slots;



};


#endif //TIMEWHEEL_H
