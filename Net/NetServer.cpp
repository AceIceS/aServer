
#include "NetServer.h"


void NetServer::InitServerAddress(const std::string &ip, const int &port)
{

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    inet_pton(AF_INET,ip.c_str(),&server_address.sin_addr);

}

void NetServer::Bind()
{
    server_socket = socket(PF_INET, SOCK_STREAM, 0);

    int reuse = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    if (server_socket < 0)
    {
        //create server socket error??
    }

    int ret = bind(server_socket,(struct sockaddr *)&server_address, sizeof(server_address));
    if(ret == -1)
    {
        //Bind socket address error
    }

}

void NetServer::Listen()
{
    int ret = listen(server_socket,LISTEN_LIMIT);

    if(ret == -1)
    {
        //Listen error??
    }
}


void NetServer::Init(const std::string &ip, const int &port)
{
    InitServerAddress(ip,port);
    Bind();
    Listen();
    //register self to accept new connection
    events_notifer.AddNewEvent(server_socket);
}

int NetServer::Accept()
{
    sockaddr_in new_client_addr;
    socklen_t new_client_addrlength = sizeof(new_client_addr);
    int connfd = accept(server_socket,
            (struct sockaddr *)&new_client_addr,&new_client_addrlength);

    //store this client and regist events
    if(connfd >= USER_LIMIT)
    {
        //not enough file descriptor
        close(connfd);
        //send a byte flag
        return -1;
    }
    if(clients[connfd] == nullptr)
    {
        //std::cout<<"aaa";
        clients[connfd] = std::make_shared<NetClient>(connfd,new_client_addr);
    }
    else
    {
        //std::cout<<"bbb";
        clients[connfd]->SetClientSocket(new_client_addr,connfd);

    }
    events_notifer.AddNewEvent(connfd,1);
    //start timing
    events_notifer.UpdateThisNetClientTimeout(clients[connfd],connfd);

    std::cout<<"New Connection comming :"<< clients[connfd]->ShowCLientIPandPort()<<std::endl;


}

void NetServer::Process()
{
    int cur_socket = -1;
    while (true)
    {


        std::shared_ptr<EpollInfo> ei(events_notifer.GetEvents(server_socket));

        int iterations = ei->_size;
        //std::cout<<"Get "<<iterations<<" events"<<std::endl;
        for (int i = 0; i < iterations; ++i) {
            cur_socket = ei->res_sockets[i];

            //new connection test ok
            if (ei->e[i] == NEW_CONNECTION) {
                int ret = Accept();
                continue;
            }

            //read events
            if (ei->e[i] == READ_EVENT)
            {
                //directly receive message from client
                //need to determine length

                //FLAG:
                int readSize = recv(cur_socket,sharedRecvBuffer,MAX_SHADRED_BUFFER_SIZE,0);
                if (readSize == 0)
                {
                    //client close socket,client calls close();
                    std::cout << clients[cur_socket]->ShowCLientIPandPort() << "  Disconnect 0" << std::endl;
                    events_notifer.DelClientEvent(cur_socket);
                    clients[cur_socket]->Reset();
                    close(cur_socket);
                }
                else if (readSize > 0)
                {
                    events_notifer.UpdateThisNetClientTimeout(clients[cur_socket],cur_socket);

                    //events_notifer.RegistWriteEvent(cur_socket);
                    bool con = clients[cur_socket]->RecvInformation(sharedRecvBuffer,readSize);
                    if(con == true)
                    {
                        //already read all the information,adjust socket to send something.
                        events_notifer.RegistWriteEvent(cur_socket);
                    }


                }
                else
                {

                    if (errno == EAGAIN || errno == EWOULDBLOCK)
                    {
                        //std::cout << "Read later" << std::endl;

                    }
                    else
                    {
                        std::cout << clients[cur_socket]->ShowCLientIPandPort() << "  Disconnect -1" << std::endl;
                        events_notifer.DelClientEvent(cur_socket);
                        clients[cur_socket]->Reset();
                        close(cur_socket);
                    }

                }

            }
            if (ei->e[i] == WRITE_EVENT) {

                //replace
                //here to call detector

                initRe3DX();
                ModelSet models;
                models.load("list -models xiaoMing_r -dataFile"
                            " /home/k/CLionProjects/aServer/%%s.mdb1 -meshFile /home/k/3DTracking/xiaoMing_r.3ds");


                Size imgSize(1280, 720);

                Matx33f K = cvrm::defaultK(imgSize, 1.2f);
                auto detector = Detector3D::create();
                std::cout<<"Detector Set Models"<<std::endl;
                detector->setModels(&models);

                FrameData fd;
                fd.cameraK = K;

                //jpeg to cv::mat



                cv::Mat imgMat = cv::imdecode(clients[cur_socket]->recvBuffer[0],1);
                detector->pro(imgMat,fd);

                for (int i = 0; i<fd.objs3DNumbers; ++i) {
                    auto &r = fd.objs3D[i];

                    float res[6] = {r.tvec[0],r.tvec[1],r.tvec[2],r.rvec[0],r.rvec[1],r.rvec[2]};

                    clients[cur_socket]->GetAlgorithmResult(res);
                    clients[cur_socket]->SendMessage();

                }


                events_notifer.CancelWriteEvent(cur_socket);
                events_notifer.UpdateThisNetClientTimeout(clients[cur_socket],cur_socket);
            }

            if (ei->e[i] == DISCONNECT)//test ok
            {
                //
                std::cout << "Disconnect EPOLLRDHUP " << clients[cur_socket]->ShowCLientIPandPort()
                          << std::endl;

                //client has disconnected,remove event and reset clients[connfd]
                events_notifer.DelClientEvent(cur_socket);

                clients[cur_socket]->Reset();
                close(cur_socket);
            }


            if(ei->e[i] == TIMEOUT)
            {
                events_notifer.TimeOut();
            }
        }

        //check to kick idles
        //alow stop server.
        if (stopServer == true) {
            break;
        }
    }//end while-true
}