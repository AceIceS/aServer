
#include "NetClient.h"
#include<ctime>

void NetClient::Reset()
{
    ClearReceiveBuffer();
    send_size = -1;
    readingMessage = false;
}

void NetClient::ClearReceiveBuffer()
{
    if(!recvBuffer.empty())
    {
        recvBuffer.clear();
    }
}

//all data has arrived at recv buffer,read it
bool NetClient::GetMessage(char *buffer,int _size)
{
    for(int i = 0;i < _size;++i)
        recvBuffer.push_back(buffer[i]);
    std::cout<<ShowCLientIPandPort()<<"  Read once ,size is "<<_size<<std::endl;
    if(realSize == recvBuffer.size())
    {
        //call algorithm
        //can send result

        std::cout<<"Total Message Size : "<<recvBuffer.size()<<std::endl;
        std::time_t t = std::time(nullptr);
        std::cout<<"Current Time "<<std::asctime(std::localtime(&t))<<std::endl;
        ClearReceiveBuffer();
        return true;
    }
    return false;
}

int NetClient::GetMessageLength(char *buffer,int _size)
{
    if(_size < 4)
    {
        // 1 -3 bytes ?
    }
    int tmpVal = 0;
    char *pointer = (char *)&tmpVal;
    for(int i = 0;i < 4;++i)
        pointer[i] = buffer[i];
    realSize = tmpVal;
    for(int i = 4;i < 8;++i)
        pointer[i - 4] = buffer[i];
    currentFrameNo = tmpVal;
    std::cout<<"Get Length : "<<realSize<<"  No : "<<currentFrameNo<<std::endl;
    //need to collect data in the buffer
    if(_size > 8)
    {
        for(int i = 4;i < _size;++i)
            recvBuffer.push_back(buffer[i]);
        //std::cout<<"Get Message at get length ,Bytes :"<<recvBuffer.size()<<std::endl;
    }
    return tmpVal;
}

bool NetClient::RecvInformation(char *buffer,int _size)
{
    //firstly need get the length of reading message
    if(readingMessage == false)
    {
        GetMessageLength(buffer,_size);
        if(recvBuffer.size() == realSize)
        {
            readingMessage = false;

            //here also can call algorithm
            ClearReceiveBuffer();
            return true;
        }
        else
        {
            //consider unsual condition???
            readingMessage = true;
            return false;
        }
    }
    else
    {
        if(GetMessage(buffer,_size))
        {
            readingMessage = false;
            return true;
        }
    }

}



void NetClient::SendMessage()
{

    int cur_send_size = send(client_socket,send_buffer,send_size,0);

    //std::cout<<"Send Size is "<<send_size<<std::endl;
    //std::cout<<"Send message "<<cur_send_size<<" bytes "<<std::endl;
    //std::cout<<ShowCLientIPandPort()<<std::endl;
    //std::cout<<"Content : "<<send_buffer<<std::endl;

}

void NetClient::GetAlgorithmResult(float *results)
{
    Message2Client message;
    for(int i = 0;i < 6;++i)
        message.data[i] = results[i];
    ResetSendBuffer();
    //modify send size
    send_size = sizeof(message);
    char *pointer = send_buffer;
    memcpy(pointer,&message, sizeof(Message2Client) + 1);

}



void NetClient::ResetSendBuffer()
{
    if(send_buffer != nullptr)
    {
        std::fill(send_buffer,send_buffer + CLIENT_SND_BUF_SIZE,'0');
    }
    send_size = 0;

}


std::string NetClient::ShowCLientIPandPort()
{

    std::string res("Client : ");
    res += inet_ntoa(client_address.sin_addr);
    res += std::to_string(ntohs(client_address.sin_port));
    return res;

}


void NetClient::SetSocketOpt()
{
    //1.set demand recv buffer
    setsockopt(client_socket,SOL_SOCKET,SO_RCVBUF,&DEMAND_RECV_BUFFER_SIZE, sizeof(DEMAND_RECV_BUFFER_SIZE));

}