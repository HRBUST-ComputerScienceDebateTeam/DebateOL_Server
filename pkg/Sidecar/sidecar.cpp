#include "./sidecar.h"
#include "../../cmd/ServiceRegistry_config.h"
#include "../JsonChange/jsonchange.h"
#include <sys/epoll.h>

using namespace std;

//服务名 + 边车的ip port  + 服务的ip port
Sidecar::Sidecar( char* server_name, char* sidecar_ip, char* sidecar_port, char* server_ip, char* server_port ) {
    this->server_name  = server_name;
    this->sidecar_ip   = sidecar_ip;
    this->sidecar_port = sidecar_port;
    this->server_ip    = server_ip;
    this->server_port  = server_port;

    initflag_net   = 0;
    initflag_clock = 0;
    initflag_reg   = 0;
}
Sidecar::~Sidecar(){};

bool Sidecar::net_init() {
    sockaddr_server.sin_addr.s_addr = inet_addr( server_ip );
    sockaddr_server.sin_family      = AF_INET;
    sockaddr_server.sin_port        = htons( stoi( string( server_port ) ) );

    sockaddr_listen.sin_addr.s_addr = inet_addr( sidecar_ip );
    sockaddr_listen.sin_family      = AF_INET;
    sockaddr_listen.sin_port        = htons( stoi( string( sidecar_port ) ) );

    //服务端 接收客户端数据
    sockfd_listen = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    sockfd_server = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    int err;
    err = bind( sockfd_listen, ( sockaddr* )&sockaddr_listen, len_sockaddr_listen );
    listen( sockfd_listen, 10 );
    if ( err != 0 ) {
        perror( "边车监听 - 绑定失败" );
        return false;
    } else {
        cout << "边车监听 - 绑定成功" << endl;
    }

    err = connect( sockfd_server, ( sockaddr* )&sockaddr_server, len_sockaddr_server );
    if ( err != 0 ) {
        perror( "边车上游 - 连接失败" );
        return false;
    } else {
        cout << "边车上游 - 连接成功" << endl;
    }
    initflag_net = 1;
    return true;
}

//
void Sidecar::time_heart( sigval_t v ) {
    //发送注册请求
    ServiceRegistry_Info_REQ req;
    req.type    = Heart_REQ;
    req.Infolen = sizeof( req );

    char buffer[ recv_buffer ];
    bzero( buffer, recv_buffer );

    //发送
    int len;
    len = send( sockfd_center, ( char* )&req, req.Infolen, 0 );

    int tmplen = 0;
    int n      = 0;
    //接收响应

    recv( sockfd_center, buffer, 4, 0 );
    len = *( int* )buffer;
    recv( sockfd_center, buffer + 4, len - 4, 0 );
    ServiceRegistry_Info_RESP* resq = ( ServiceRegistry_Info_RESP* )buffer;
    if ( resq->status == status_OK ) {
        cout << "[S]边车： 注册中心心跳成功" << endl;
    } else {
        cout << "[S]边车： 注册中心心跳失败" << endl;
    }
}

//设置心跳事件
bool Sidecar::clock_init() {
    //初始化时钟
    struct sigevent sev;
    bzero( &sev, sizeof( sev ) );
    sev.sigev_notify          = SIGEV_THREAD;
    sev.sigev_notify_function = time_heart;
    sev.sigev_value.sival_ptr = &heart_timer;
    sev.sigev_value.sival_int = 1;

    int err;
    err = timer_create( CLOCK_REALTIME, &sev, &heart_timer );
    if ( err ) {
        perror( "timer_create" );
        return false;
    }
    struct itimerspec itc;
    itc.it_interval.tv_sec  = SRCenter_heart_jgtime;
    itc.it_interval.tv_nsec = 0;
    itc.it_value.tv_sec     = SRCenter_heart_jgtime;
    itc.it_value.tv_nsec    = 0;

    err = timer_settime( heart_timer, TIMER_ABSTIME, &itc, NULL );
    if ( err ) {
        perror( "timer_setting" );
        return false;
    }
    initflag_clock = 1;
    return true;
}

//向服务注册中心注册
bool Sidecar::Reg_tocenter() {
    sockfd_center                   = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    sockaddr_center.sin_addr.s_addr = inet_addr( center_reg_ip );
    sockaddr_center.sin_port        = htons( center_reg_port );
    sockaddr_center.sin_family      = AF_INET;
    int err;
    err = connect( sockfd_center, ( sockaddr* )&sockaddr_center, len_sockaddr_center );
    if ( err == 0 ) {
        // cout << "连接到注册中心成功" << endl;
    } else {
        perror( "连接到注册中心失败" );
        return false;
    }
    //发送注册请求
    ServiceRegistry_Info_REQ req;
    req.type    = REG_REQ;
    req.Infolen = sizeof( req );
    bzero( &req.ip, sizeof( req.ip ) );
    strncpy( req.ip, sidecar_ip, strlen( sidecar_ip ) );

    bzero( &req.port, sizeof( req.port ) );
    strncpy( req.port, sidecar_port, strlen( sidecar_port ) );

    bzero( &req.servername, sizeof( req.servername ) );
    strncpy( req.servername, server_name, strlen( server_name ) );
    // cout << req.Infolen << endl;
    // cout << req.type << endl;
    // cout << req.servername << endl;
    // cout << req.port << endl;
    // cout << req.ip << endl;
    char buffer[ 10005 ];
    bzero( buffer, 10005 );

    //发送
    int len;
    // cout << "记录长度 " << req.Infolen << endl;
    len = send( sockfd_center, ( char* )&req, req.Infolen, 0 );
    // cout << "发送字节长度" << len << endl;

    int tmplen = 0;
    int n      = 0;
    //接收响应

    recv( sockfd_center, buffer, 4, 0 );
    len = *( int* )buffer;
    recv( sockfd_center, buffer + 4, len - 4, 0 );
    ServiceRegistry_Info_RESP* resq = ( ServiceRegistry_Info_RESP* )buffer;
    if ( resq->status == status_OK ) {
        initflag_reg = 1;
        return true;
    } else {
        return false;
    }
}

bool Sidecar::zf( int fd_in, int fd_out ) {
    //监听下游信息事件
    char buffer[ 10005 ];
    int  off         = 0;
    int  tmptitlelen = 0;

    // 暂时不启用零拷贝
    // // 创建管道
    // int pipefd[ 2 ];
    // pipe( pipefd );

    // //监听
    // fd_set readfds, tmpfds;
    // FD_ZERO( &readfds );
    // FD_SET( fd_in, &readfds );

    // // 使用splice函数进行数据转发
    // ssize_t n      = 0;
    // int     offtmp = 0;
    // while ( 1 ) {
    //     tmpfds = readfds;
    //     if ( select( fd_in + 1, &tmpfds, NULL, NULL, NULL ) <= 0 )
    //         break;
    //     if ( FD_ISSET( fd_in, &tmpfds ) == 0 )
    //         break;
    //     // cout << "now fdset : " << FD_ISSET( fd_in, &tmpfds ) << endl;
    //     // if ( ( offtmp = splice( fd_in, NULL, pipefd[ 1 ], NULL, 4096, SPLICE_F_MOVE | SPLICE_F_MORE ) ) > 0 ) {
    //     //     splice( pipefd[ 0 ], NULL, fd_out, NULL, offtmp, SPLICE_F_MOVE | SPLICE_F_MORE );
    //     //     n += offtmp;
    //     //     offtmp = 0;
    //     //     cout << n << endl;
    //     read( fd_in, buffer + off, 62 );
    //     // } else {
    //     //     break;
    //     // }
    // }
    // cout << "转发了" << n << endl;
    // close( pipefd[ 0 ] );
    // close( pipefd[ 1 ] );
    // return true;

    //读入数据
    off += read( fd_in, buffer + off, 4 );
    off += read( fd_in, buffer + off, 4 );
    for ( int i = 1; i <= 4; i++ ) {
        tmptitlelen = tmptitlelen * 256 + ( int )buffer[ 3 + i ];
    }  //名长度
    off += read( fd_in, buffer + off, tmptitlelen );
    off += read( fd_in, buffer + off, 7 );

    int type = 0;
    do {
        off += read( fd_in, buffer + off, 1 );
        type = ( int )buffer[ off - 1 ];
        switch ( type ) {
        case 8: {
            off += read( fd_in, buffer + off, 6 );
            break;
        }
        case 11: {
            off += read( fd_in, buffer + off, 6 );
            int stringlen = 0;
            for ( int i = 1; i <= 4; i++ ) {
                stringlen = stringlen * 256 + ( int )buffer[ off - 5 + i ];
            }  //字符串长度
            off += read( fd_in, buffer + off, stringlen );
            break;
        }
        default:
            break;
        }
    } while ( type != 0 );

    off += read( fd_in, buffer + off, 1 );

    //记录之后转发
    int len = write( fd_out, buffer, off );
    if ( len != off ) {
        perror( "转发失败" );
        return false;
    } else {
        cout << "转发成功 转发字节" << len << endl;
    }

    return true;
}

int Sidecar::sockfd_listen;
int Sidecar::sockfd_server;
int Sidecar::sockfd_client;
int Sidecar::sockfd_center;
int Sidecar::init() {
    if ( initflag_net == false ) {
        if ( net_init() == false ) {
            cout << "边车启动失败 : net初始化失败" << endl;
            return false;
        } else {
            initflag_net = true;
        }
    }

    if ( initflag_reg == false ) {
        if ( Reg_tocenter() == false ) {
            cout << "边车启动失败 : 服务注册失败" << endl;
            return false;
        } else {
            initflag_reg = true;
        }
    }

    if ( initflag_clock == false ) {
        if ( clock_init() == false ) {
            cout << "边车启动失败 : 时钟失败" << endl;
            return false;
        } else {
            initflag_clock = true;
        }
    }

    return true;
}
void* Sidecar::dealzf( void* arg ) {
    int clientfd = *( int* )arg;
    zf( clientfd, sockfd_server );
    zf( sockfd_server, clientfd );
    if ( arg ) {
        delete arg;
    }
    //任务添加
    // 重新挂载节点
    struct epoll_event epollnode1;
    epollnode1.data.fd = clientfd;
    epollnode1.events  = EPOLLIN | EPOLLET | EPOLLONESHOT;
    epoll_ctl( epollfd, EPOLL_CTL_MOD, clientfd, &epollnode1 );

    return nullptr;
}
int Sidecar::start() {
    if ( init() ) {
        cout << "边车 - 初始化成功" << endl;
    }
    // epoll
    pthread_pool_t mypool( 100, 10, 10000 );
    mypool.open();
    Sidecar::epollfd = epoll_create( EPOLL_EVENT_MAX );
    struct epoll_event epoll_result[ EPOLL_EVENT_MAX ];
    epoll_event        node;
    node.events  = EPOLLIN;
    node.data.fd = sockfd_listen;

    epoll_ctl( epollfd, EPOLL_CTL_ADD, sockfd_listen, &node );
    sockfd_client = accept( sockfd_listen, ( sockaddr* )&sockaddr_client, &len_sockaddr_client );
    while ( 1 ) {
        int readynum = epoll_wait( epollfd, epoll_result, EPOLL_EVENT_MAX, 0 );
        for ( int i = 0; i < readynum; i++ ) {
            int sockfd = epoll_result[ i ].data.fd;
            if ( sockfd == sockfd_listen ) {
                struct sockaddr_in client_address;
                socklen_t          client_address_len = sizeof( client_address );
                int                client_socket      = accept( sockfd_listen, ( struct sockaddr* )&client_address, &client_address_len );
                if ( client_socket == -1 ) {
                    perror( "Accept failed!" );  //错误
                } else {
                    // tcp keepalive
                    int keepalive    = 1;   // 开启keepalive属性
                    int keepidle     = 20;  // 如该连接在20秒内没有任何数据往来,则进行探测
                    int keepinterval = 3;   // 探测时发包的时间间隔为3 秒
                    int keepcount    = 5;   // 探测尝试的次数.如果第5次探测包就收到响应了,则后2次的不再发.
                    setsockopt( client_socket, SOL_SOCKET, SO_KEEPALIVE, ( void* )&keepalive, sizeof( keepalive ) );
                    setsockopt( client_socket, SOL_TCP, TCP_KEEPIDLE, ( void* )&keepidle, sizeof( keepidle ) );
                    setsockopt( client_socket, SOL_TCP, TCP_KEEPINTVL, ( void* )&keepinterval, sizeof( keepinterval ) );
                    setsockopt( client_socket, SOL_TCP, TCP_KEEPCNT, ( void* )&keepcount, sizeof( keepcount ) );

                    //客户端的绑定
                    struct epoll_event epollnode1;
                    epollnode1.data.fd = client_socket;
                    epollnode1.events  = EPOLLIN | EPOLLET | EPOLLONESHOT;
                    epoll_ctl( epollfd, EPOLL_CTL_ADD, client_socket, &epollnode1 );
                }
            } else {
                //客户端信息
                int* arg = new int( sockfd );
                mypool.addwork( { &Sidecar::dealzf, ( void* )arg } );
            }
        }
    }
    close( sockfd_server );
    close( sockfd_listen );
    close( sockfd_center );
    return 0;
}

list< pair< string, string > > down_server_info( char* server_name ) {
    list< pair< string, string > > ret;
    int                            len;
    int                            sockfd_center;
    struct sockaddr_in             sockaddr_center;
    socklen_t                      len_sockaddr_center = sizeof( sockaddr_in );
    sockfd_center                                      = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    sockaddr_center.sin_addr.s_addr                    = inet_addr( center_reg_ip );
    sockaddr_center.sin_port                           = htons( center_reg_port );
    sockaddr_center.sin_family                         = AF_INET;
    int err;
    err = connect( sockfd_center, ( sockaddr* )&sockaddr_center, len_sockaddr_center );
    if ( err == 0 ) {
        cout << "连接到注册中心成功" << endl;
    } else {
        perror( "连接到注册中心失败" );
        return ret;
    }

    //发送下载请求
    ServiceRegistry_Info_REQ req;
    req.Infolen = sizeof( req );
    req.type    = Down_REQ;
    bzero( &req.servername, sizeof( req.servername ) );
    strncpy( req.servername, server_name, strlen( server_name ) );
    len = send( sockfd_center, ( char* )&req, req.Infolen, 0 );

    //接收应答信息
    char buffer[ 10005 ];
    bzero( buffer, 10005 );
    //接收响应
    recv( sockfd_center, buffer, 4, 0 );
    len = *( int* )buffer;
    // cout << "认为应该接受的长度" << len << endl;
    recv( sockfd_center, buffer + 4, len - 4, 0 );
    ServiceRegistry_Info_RESP* resq = ( ServiceRegistry_Info_RESP* )buffer;

    if ( resq->status == status_OK ) {
        //更新数据
        string resq_str( resq->respinfo );
        cout << resq_str;
        map< string, string > mp = JsonstringToMap( resq_str );  // id , ip-post
        for ( auto it : mp ) {
            int pos = it.second.find( '-' );

            ret.push_back( make_pair( it.second.substr( 0, pos ), it.second.substr( pos + 1 ) ) );
            // cout << it.second.substr( 0, pos ) << " " << it.second.substr( pos + 1 ) << endl;
        }
        return ret;
    } else {
        cout << "获得服务失败" << endl;
        return ret;
    }
}

int Sidecar::epollfd;