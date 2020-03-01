
#include"NetServer.h"

int main(int argc,char *argv[])
{
    const std::string ip = argv[1];
    const int port = atoi(argv[2]);

    NetServer server;
    server.Init(ip,port);
    server.Precess();
    server.CloseServer();

    return 0;
}
