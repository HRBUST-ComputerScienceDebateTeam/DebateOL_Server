//这个文件启动http服务器 接受http请求
#include "../conf.hh"
#include "./rpc.hh"
#include <arpa/inet.h>
#include <asm-generic/errno-base.h>
#include <cerrno>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <mutex>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <pthread.h>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
//添加线程池
#include "../../pkg/pool/threadpool.h"

const int PORT        = HTTP_PORT;
const int BUFFER_SIZE = HTTP_REQ_BUFFER_SIZE;

char buffer[ THREAD_POOL_MAXTHREADNUM ][ BUFFER_SIZE ];  //最多100个线程 所以安全
int  now_bufferid = 0;

//锁
pthread_mutex_t plock;

//线程池优化 - 处理性能
pthread_pool_t pool( THREAD_POOL_MINTHREADNUM, THREAD_POOL_MINTHREADNUM, THREAD_POOL_MAXTASKNUM );

// epoll
int                epollfd;
struct epoll_event epoll_result[ EPOLL_EVENT_MAX ];

// socket
int              serverfd;
std::list< int > sockls;

//属性
typedef class URI {
public:
    // 1.访问的微服务或者文件路径
    std::string path;
    // 2.追加的查询条件
    std::map< std::string, std::string > query;
} uri_info;

typedef class RequestInfo {
public:
    // 1.方法
    std::string method;
    // 2.URi
    uri_info uri;
    // 3.版本
    std::string version;
    // 4.首部字段
    std::map< std::string, std::string > options;
    // 5.体
    std::string body;

public:
    RequestInfo( std::string& );
    RequestInfo();
} RequestInfo;
RequestInfo::RequestInfo( std::string& s ) {
    size_t pos      = s.find( ' ' );
    this->method    = s.substr( 0, pos );
    pos             = s.find( ' ', pos + 1 );
    std::string uri = s.substr( s.find( ' ' ) + 1, pos - s.find( ' ' ) - 1 );

    size_t uripos = uri.find( '?' );
    //如果有问号就是有选项的
    //如果没有问号就是只有url
    if ( uripos == std::string::npos ) {
        //没有
        this->uri.path = uri;
    } else {
        this->uri.path = uri.substr( 0, uripos );
        //记录查询项
        std::string q      = uri.substr( uripos + 1 );
        size_t      andpos = std::string::npos;
        int         nowpos = 0;
        do {

            andpos   = q.find( '&', nowpos );
            size_t l = nowpos;
            size_t r = andpos;
            size_t eqpos;
            if ( r != std::string::npos ) {
                eqpos = q.substr( l, r - l + 1 ).find( '=' );  //第一个等于号左侧就等于右侧
            } else {
                eqpos = q.substr( l ).find( '=' );  //第一个等于号左侧就等于右侧
            }
            this->uri.query[ q.substr( l, eqpos ) ] = q.substr( l + eqpos + 1, r - l - eqpos - 1 );
            if ( andpos != std::string::npos ) {
                nowpos = andpos + 1;
            }
        } while ( andpos != std::string::npos );
    }
    size_t l, r;
    l             = pos + 1;
    pos           = s.find( "\r\n", pos + 1 );
    r             = pos;
    this->version = s.substr( l, r - l + 1 );
    pos += 2;

    //首字段
    while ( true ) {
        l   = pos;
        pos = s.find( "\r\n", pos );
        r   = pos;
        if ( l == r )
            break;
        else
            pos += 2;

        std::string tmps                          = s.substr( l, r - l + 1 );
        int         tmppos                        = tmps.find( ": " );
        this->options[ tmps.substr( 0, tmppos ) ] = tmps.substr( tmppos + 2 );
    }
    this->body = s.substr( pos + 2 );
}

// 处理HTTP请求
std::string handleRequest( RequestInfo& reqinfo ) {
    std::string response;
    if ( reqinfo.method == "GET" ) {
        /* 回应头 */
        response = "HTTP/1.1 200 OK\r\n"
                   "Content-Type: text/html; charset=utf-8\r\n"
                   "Connection: keep-alive\r\n"
                   "\r\n";

        /* 路由 */
        if ( reqinfo.uri.path == "/videodownload/" ) {
            std::cout << "\tvideodownload" << std::endl;
            if ( reqinfo.uri.query.find( "info" ) != reqinfo.uri.query.end() ) {
                response += rpc::VideoDownload( reqinfo.uri.query[ "info" ] );
            }
        } else if ( reqinfo.uri.path == "/audiodownload/" ) {
            std::cout << "\taudiodownload" << std::endl;
            if ( reqinfo.uri.query.find( "info" ) != reqinfo.uri.query.end() ) {
                response += rpc::AudioDownload( reqinfo.uri.query[ "info" ] );
            }
        } else {
            response += "<html><head><title>Get Request</title></head><body><h1>Get Request Received!</h1></body></html>";
        }

    } else if ( reqinfo.method == "POST" ) {
        /* 回应头 */
        response = "HTTP/1.1 200 OK\r\n"
                   "Content-Type: text/html; charset=utf-8\r\n"
                   "Connection: keep-alive\r\n"
                   "\r\n";
        using namespace std;
        // cout << reqinfo.method <<endl;
        // cout << reqinfo.uri.path <<endl;
        // cout << reqinfo.body <<endl;
        // //cout << reqinfo.options <<endl;
        // cout << reqinfo.version <<endl;

        /* 路由 */
        if ( reqinfo.uri.path == "/echo" ) {
            std::cout << "\techo post" << std::endl;
            if ( reqinfo.body == "" )
                return "";
            response += rpc::Del_echo( reqinfo.body );
        } else if ( reqinfo.uri.path == "/videoupload" ) {
            std::cout << "\tvideoupload" << std::endl;
            if ( reqinfo.body == "" )
                return "";
            response += rpc::VideoUpload( reqinfo.body );
        } else if ( reqinfo.uri.path == "/videoclean" ) {
            std::cout << "\tvideoclean" << std::endl;
            if ( reqinfo.body == "" )
                return "";
            rpc::VideoClean( reqinfo.body );
        } else if ( reqinfo.uri.path == "/audioupload" ) {
            std::cout << "\taudioupload" << std::endl;
            if ( reqinfo.body == "" )
                return "";
            response += rpc::VideoUpload( reqinfo.body );
        } else if ( reqinfo.uri.path == "/audioclean" ) {
            std::cout << "\taudioclean" << std::endl;
            if ( reqinfo.body == "" )
                return "";
            rpc::AudioClean( reqinfo.body );
        } else {
            response += "<html><head><title>Post Request</title></head><body><h1>Post Request Received!</h1><p>" + reqinfo.body + "</p></body></html>";
        }

    } else {
        // 处理其他请求
        response = "HTTP/1.1 404 Not Found\r\n"
                   "Content-Type: text/html; charset=utf-8\r\n"
                   "\r\n"
                   "<html><head><title>Not Found</title></head><body><h1>404 Not Found</h1></body></html>";
    }

    return response;
}

// 处理客户端信息
void* handleClient( void* arg ) {
    int     client_socket = *( int* )arg;
    ssize_t buffer_len    = 0;

    // TODO 待优化
    pthread_mutex_lock( &plock );
    // char * buffer = &buffer[now_bufferid];
    now_bufferid = ( now_bufferid + 1 ) % THREAD_POOL_MAXTHREADNUM;
    pthread_mutex_unlock( &plock );
    char buffer[ BUFFER_SIZE ];

    //读入头
    int readlen = 0;
    while ( true ) {
        ssize_t n1 = recv( client_socket, buffer + buffer_len, 300, MSG_DONTWAIT );  //通常自定义包头200左右 300 为了限定不会接受两个包
        if ( n1 <= 0 ) {
            //重新读入
            continue;
        } else {
            buffer_len += n1;
            //寻找/r/n/r/n;
            std::string request( buffer );
            int         pos = request.find( "\r\n\r\n", 0 );
            if ( pos == std::string::npos ) {
                //没有找到继续读入
                continue;
            }
            //解析
            RequestInfo reqinfo( request );
            //获取长度
            if ( reqinfo.options.find( "Content-Length" ) != reqinfo.options.end() ) {
                readlen = stoi( reqinfo.options[ "Content-Length" ] );
            } else {
                readlen = 0;
            }
            // std::cout <<"读入到body共" <<  readlen << std::endl;
            readlen += ( pos + 4 );
            readlen -= buffer_len;
            break;
        }
    }
    // std::cout <<"仍然需要读入" <<  readlen << std::endl;
    while ( readlen ) {
        ssize_t n = recv( client_socket, buffer + buffer_len, BUFFER_SIZE - buffer_len, MSG_DONTWAIT );
        // std::cout << n << std::endl;
        //找到/r/n

        if ( n > 0 ) {
            buffer_len += n;
            readlen -= n;
        } else if ( n == 0 ) {  //连接关闭
            break;
        } else {
            // n<0
            if ( errno != EAGAIN ) {
                perror( "read 异常退出" );
                break;
            }
        }
    }

    std::string request( buffer );
    //打印包信息
    // std::cout << buffer_len <<std::endl;
    // std::cout << request <<std::endl;

    // 解析HTTP请求
    RequestInfo reqinfo( request );
    std::string response = handleRequest( reqinfo );
    // std::cout << request << std::endl;
    // std::cout << response <<std::endl;

    send( client_socket, response.c_str(), response.length(), MSG_NOSIGNAL );

    buffer_len = 0;

    // struct epoll_event epollnode1;
    // epollnode1.data.fd = client_socket;
    // epollnode1.events =EPOLLIN|EPOLLET|EPOLLONESHOT;
    // epoll_ctl(epollfd , EPOLL_CTL_MOD , client_socket , &epollnode1);
    epoll_ctl( epollfd, EPOLL_CTL_DEL, client_socket, NULL );
    close( client_socket );
    //线程池自带 回收资源
    free( arg );
    return nullptr;
}

int main() {
    //初始化锁
    pthread_mutex_init( &plock, NULL );

    // 创建TCP套接字
    serverfd = socket( AF_INET, SOCK_STREAM, 0 );
    if ( serverfd == -1 ) {
        std::cerr << "Create socket failed!" << std::endl;
        return -1;
    }
    //复用端口
    int opt = 1;
    setsockopt( serverfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof( opt ) );
    //监听套接字 非阻塞 防止客户端再accept之后 取出之前关闭了
    int flag = fcntl( serverfd, F_GETFL, 0 );
    fcntl( serverfd, F_SETFL, flag | O_NONBLOCK );

    // 绑定地址
    struct sockaddr_in server_address {};
    memset( &server_address, 0, sizeof( server_address ) );
    server_address.sin_family      = AF_INET;
    server_address.sin_port        = htons( PORT );
    server_address.sin_addr.s_addr = htonl( INADDR_ANY );
    if ( bind( serverfd, ( struct sockaddr* )&server_address, sizeof( server_address ) ) == -1 ) {
        std::cerr << "Bind failed!" << std::endl;
        return -1;
    }

    // 监听端口
    if ( listen( serverfd, SOMAXCONN ) == -1 ) {
        std::cerr << "Listen failed!" << std::endl;
        return -1;
    }

    std::cout << "Server started. Listening on port " << PORT << "..." << std::endl;

    // 线程池开启服务
    pool.open();

    // EPOLL IO复用优化
    epollfd = epoll_create( EPOLL_EVENT_MAX );
    struct epoll_event epollnode;
    epollnode.data.fd = serverfd;
    epollnode.events  = EPOLLIN;
    epoll_ctl( epollfd, EPOLL_CTL_ADD, serverfd, &epollnode );

    while ( true ) {
        int readynum = epoll_wait( epollfd, epoll_result, EPOLL_EVENT_MAX, 0 );
        for ( int i = 0; i < readynum; i++ ) {
            int sockfd = epoll_result[ i ].data.fd;
            if ( sockfd == serverfd ) {
                struct sockaddr_in client_address {};
                socklen_t          client_address_len = sizeof( client_address );
                int                client_socket      = accept( serverfd, ( struct sockaddr* )&client_address, &client_address_len );
                if ( client_socket == -1 ) {
                    // perror("Accept failed!");
                    break;
                } else {
                    // keepalive
                    int keepalive    = 1;  // 开启keepalive属性
                    int keepidle     = 5;  // 如该连接在5秒内没有任何数据往来,则进行探测
                    int keepinterval = 1;  // 探测时发包的时间间隔为1 秒
                    int keepcount    = 3;  // 探测尝试的次数.如果第1次探测包就收到响应了,则后2次的不再发.
                    setsockopt( client_socket, SOL_SOCKET, SO_KEEPALIVE, ( void* )&keepalive, sizeof( keepalive ) );
                    setsockopt( client_socket, SOL_TCP, TCP_KEEPIDLE, ( void* )&keepidle, sizeof( keepidle ) );
                    setsockopt( client_socket, SOL_TCP, TCP_KEEPINTVL, ( void* )&keepinterval, sizeof( keepinterval ) );
                    setsockopt( client_socket, SOL_TCP, TCP_KEEPCNT, ( void* )&keepcount, sizeof( keepcount ) );

                    struct epoll_event epollnode1;
                    epollnode1.data.fd = client_socket;
                    epollnode1.events  = EPOLLIN | EPOLLET | EPOLLONESHOT;
                    epoll_ctl( epollfd, EPOLL_CTL_ADD, client_socket, &epollnode1 );
                    sockls.push_back( client_socket );
                }
            } else {
                int* client_socket = new int( epoll_result[ i ].data.fd );
                pool.addwork( { &handleClient, ( void* )client_socket } );
            }
        }
    }

    // 关闭服务器套接字
    close( serverfd );
    for ( auto sockfd : sockls ) {
        close( sockfd );
    }
    //初始化锁
    pthread_mutex_destroy( &plock );

    return 0;
}