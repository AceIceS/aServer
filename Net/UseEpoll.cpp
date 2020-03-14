
#include "UseEpoll.h"


int UseEpoll::SetNonBlocking(int fd)
{
    int old_option = fcntl(fd,F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd,F_SETFL,new_option);
    return old_option;
}


int UseEpoll::AddNewEvent(int clientfd,int kind)
{
    epoll_event aEvent;
    aEvent.data.fd = clientfd;

    //regist read,write,disconnect,et
    aEvent.events = EPOLLIN;
    //aEvent.events |= EPOLLET;
    if(kind == 1)
    {
        aEvent.events |= EPOLLRDHUP;
    }
    epoll_ctl(epollfd,EPOLL_CTL_ADD,clientfd,&aEvent);

    return SetNonBlocking(clientfd);
}

int UseEpoll::RegistWriteEvent(int clientfd)
{
    epoll_event aEvent;
    aEvent.data.fd = clientfd;
    aEvent.events = EPOLLOUT;
    //aEvent.events |= EPOLLET;

    epoll_ctl(epollfd,EPOLL_CTL_MOD,clientfd,&aEvent);
}

int UseEpoll::CancelWriteEvent(int clientfd)
{
    epoll_event aEvent;
    aEvent.data.fd = clientfd;
    aEvent.events = EPOLLIN;
    //aEvent.events |= EPOLLET;

    epoll_ctl(epollfd,EPOLL_CTL_MOD,clientfd,&aEvent);
}


int UseEpoll::DelClientEvent(int clientfd)
{
    if(clientfd < 0)
        return -1;

    epoll_event aEvent;
    aEvent.data.fd = clientfd;
    //regist read,write,disconnect,et
    aEvent.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP | EPOLLET;
    epoll_ctl(epollfd,EPOLL_CTL_DEL,clientfd,&aEvent);

}


EpollInfo* UseEpoll::GetEvents(const int &server_socket)
{
    //wait unitl events come
    int event_nums = epoll_wait(epollfd,&events[0],EVENT_LIMIT,-1);
    if(event_nums <= 0)
        return nullptr;

    EpollInfo *ei = new EpollInfo;
    ei->_size = event_nums;
    ei->res_sockets = new int [event_nums];
    ei->e = new EVENT_TYPES[event_nums];


    for(int i = 0;i < event_nums;++i)
    {

        ei->res_sockets[i] = events[i].data.fd;
        if(server_socket == events[i].data.fd)
        {
            ei->e[i] = NEW_CONNECTION;
        }
        if(events[i].events & EPOLLIN && events[i].data.fd != server_socket)
        {
            ei->e[i] = READ_EVENT;
        }
        if(events[i].events & EPOLLOUT)
        {
            ei->e[i] = WRITE_EVENT;
        }
        if(events[i].events & EPOLLRDHUP)
        {
            ei->e[i] = DISCONNECT;
        }
        if(events[i].data.fd == timeWheel.TimeFD() && events[i].events & EPOLLIN)
        {
            uint64_t t;
            read(timeWheel.TimeFD(),&t, sizeof(t));
            ei->e[i] = TIMEOUT;
        }
    }//end-for

    return ei;
}
