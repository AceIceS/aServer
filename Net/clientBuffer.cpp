
#include "clientBuffer.h"


bool clientBuffer::GetData(int &clientsock)
{

}

bool clientBuffer::GetPreInfo(int &clientsock)
{
    int readSize =recv(clientsock,&theReadBuffer[startIndex],
            theReadBuffer.size() - endIndex,0);
    if(readSize == 8)
    {
        int length = 0;
        char *pointer = (char *)&length;
        for(int i = 0;i < 4;++i)
            pointer[i] = theReadBuffer[i];
        _realSize = length;
        for(int i = 4;i < 8;++i)
            pointer[i] = theReadBuffer[i];
        _currentFrameNo = length;

        std::cout<<"Get RealSize "<<_realSize<<"  current NO : "<<_currentFrameNo;
    }
    else if(readSize > 8)
    {

    }
    else
    {

    }


}

