
#include "TimeWheel.h"


void TimeWheel::Tick()
{
    slots[current_index].clear();
    current_index = (current_index + 1) % slots.size();

    //std::cout<<"Tick : " << current_index<<std::endl;
    //next
    SetTimeout();
}

void TimeWheel::AddTimer(shared_ptr<NetClient> &ptr,int &sock)
{
    int index = (current_index + (timelimits % slots.size())) % slots.size();
    //std::cout<<"CCCCCCC"<<std::endl;
    slots[index].push_back(Timer(ptr,sock));
    //std::cout<<"CCCCCCC"<<std::endl;
    //slots[index].back().SetTarget(target);
    //std::cout<<"***********"<<slots[index].back().client_ptr.use_count()<<std::endl;
}

void TimeWheel::InitTimeWheel()
{
    timerfd = timerfd_create(CLOCK_MONOTONIC,0);

    the_time.it_value.tv_sec = 1;
    the_time.it_value.tv_nsec = 0;
    //only once
    the_time.it_interval.tv_sec = the_time.it_interval.tv_nsec = 0;

    //start
    SetTimeout();
}

void TimeWheel::SetTimeout()
{
    timerfd_settime(timerfd,0, &the_time, nullptr);
}
