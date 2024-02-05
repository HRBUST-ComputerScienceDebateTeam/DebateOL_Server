#include "../../cmd/conf.hh"
#include "../time_wheel/time_wheel.h"
#include <arpa/inet.h>
#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>
#include <bits/stdc++.h>
#include <bits/types/time_t.h>
#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fcntl.h>
#include <iostream>
#include <mutex>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <pthread.h>
#include <string>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/mman.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>
#include <unistd.h>
//添加线程池
#include "../../pkg/pool/threadpool.h"

struct NODE {
    char* buffer;
    int   len;
};

class Sidecar {
private:
    char* server_name;
    char* sidecar_ip;
    char* sidecar_port;
    char* server_ip;
    char* server_port;

public:
    //构造函数
    Sidecar( char* server_name, char* sidecar_ip, char* sidecar_port, char* server_ip, char* server_port );
    ~Sidecar();
    bool         net_init();
    bool         clock_init();
    bool         Reg_tocenter();
    int          start();
    int          init();
    static void* dealzf( void* arg );

    static void time_heart( sigval_t v );
    static bool zf( int fd_in, int fd_out );

private:
    //全局变量
    static int sockfd_listen;
    static int sockfd_server;
    static int sockfd_client;
    static int sockfd_center;

    struct sockaddr_in sockaddr_listen;
    struct sockaddr_in sockaddr_client;
    struct sockaddr_in sockaddr_server;
    struct sockaddr_in sockaddr_center;

    socklen_t len_sockaddr_client = sizeof( sockaddr_in );
    socklen_t len_sockaddr_server = sizeof( sockaddr_in );
    socklen_t len_sockaddr_listen = sizeof( sockaddr_in );
    socklen_t len_sockaddr_center = sizeof( sockaddr_in );

    Time_Wheel heart_time;   //心跳监控 - 定时器
    timer_t    heart_timer;  //心跳监控 - 时钟

    bool initflag_net;
    bool initflag_clock;
    bool initflag_reg;

    static int epollfd;

public:
    static const int recv_buffer = 1005;
};
//下载服务
list< pair< string, string > > down_server_info( char* server_name );