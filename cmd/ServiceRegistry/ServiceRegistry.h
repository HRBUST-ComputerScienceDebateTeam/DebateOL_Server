#include "../../pkg/JsonChange/jsonchange.h"
#include "../../pkg/pool/threadpool.h"
#include "../../pkg/time_wheel/time_wheel.h"
#include "../ServiceRegistry_config.h"
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <bits/types/sigevent_t.h>
#include <bits/types/siginfo_t.h>
#include <bits/types/sigset_t.h>
#include <bits/types/struct_itimerspec.h>
#include <bits/types/struct_timeval.h>
#include <bits/types/time_t.h>
#include <csignal>
#include <cstdlib>
#include <ctime>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <mqueue.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <pthread.h>
#include <queue>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/poll.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>
#include <unistd.h>
#include <utility>
using namespace std;

//声明
//对应事件的处理函数
static void DEAL_REG( int fd, ServiceRegistry_Info_REQ* req );
static void DEAL_DOWN( int fd, ServiceRegistry_Info_REQ* req );
static void DEAL_HEART( int fd, ServiceRegistry_Info_REQ* req );
static void DEAL_EXIT( int fd );
// 定时时间处理
static void timedeal( sigval_t arg );
// 此时时钟使用socket作为下标 true代表之前没有
static bool  Cheak_and_UpdataToHeart( int sockid );
static void  DelToHeart( int fd );
static void* TIMEOUT_heart( void* arg );
static void  clock_init();
//挂载事件
static void serverdeal();
//处理响应事件
static void* clientdeal( void* arg );
