# aServer

在Ubuntu 18.04.4 LTS上测试通过

采用TCP/IP协议，Linux socket实现网络通信。
客户端与服务器建立TCP长连接。

类Usepoll封装了epoll相关系统调用，通过I/O复用实现客户端并发访问。
类NetClient管理每个与服务器连接的客户端。
类NetServer管理客户端连接请求，通知相应NetClient实例收发数据。
