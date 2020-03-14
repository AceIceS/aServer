#include <memory>

#include"Net/NetServer.h"

#include "theDetector.h"

using namespace std;

int main(int argc,char *argv[])
{

    const std::string ip = argv[1];
    const int port = atoi(argv[2]);

    NetServer server;
    server.Init(ip,port);
    server.Process();
    server.CloseServer();



    return 0;
}
