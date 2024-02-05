#include "./ServiceRegistry.h"
#include <utility>

//关于两个mp的说明
// mp_server    - 根据string的服务名 - list<可用ip - port>
// socket_server- sockfd - 服务名 - pair<可用ip - port>

// epoll
int                epollfd;
int                serverfd;
struct epoll_event ready_array[ SRCenter_epoll_event_num ];
//开启线程池 int thread_max, int thread_min, int queue_max
pthread_pool_t mypool( SRCenter_pool_thread_max, SRCenter_pool_thread_min, SRCenter_pool_queue_max );
//根据string的服务名 - list<可用ip - port>
map< string, list< pair< string, string > > > mp_server;
//下线删除 sockfd - 对应服务
map< int, pair< string, pair< string, string > > > socket_server;
//定时器相关
Time_Wheel heart_time;   //心跳监控 - 定时器
timer_t    heart_timer;  //心跳监控 - 时钟

//对应事件的处理函数
void DEAL_REG( int fd, ServiceRegistry_Info_REQ* req ) {
    socket_server[ fd ] = make_pair( req->servername, make_pair( req->ip, req->port ) );
    mp_server[ req->servername ].push_back( make_pair( req->ip, req->port ) );
    cout << "[+] 服务注册" << req->servername << "(" << req->ip << "," << req->port << ")" << endl;
    ServiceRegistry_Info_RESP res;
    res.type    = REG_RESP;
    res.status  = status_OK;
    res.Infolen = sizeof( res );
    send( fd, ( void* )&res, sizeof( res ), 0 );
}
void DEAL_DOWN( int fd, ServiceRegistry_Info_REQ* req ) {
    ServiceRegistry_Info_RESP res;
    res.type    = Down_RESP;
    res.Infolen = sizeof( res );
    map< string, string > mp;
    int                   idnum = 0;
    if ( ( mp_server.find( req->servername ) != mp_server.end() ) && ( mp_server[ req->servername ].size() != 0 ) ) {
        res.status = status_OK;
        cout << "[√] 服务发现成功 " << endl;
        for ( auto it : mp_server[ req->servername ] ) {
            mp[ to_string( ++idnum ) ] = it.first + "-" + it.second;
        }

        string s = MapToJsonstring( mp );
        // cout << s << endl;
        bzero( res.respinfo, sizeof( res.respinfo ) );
        strncpy( res.respinfo, s.data(), s.size() );
    } else {
        res.status = status_ERR;
        cout << "[x] 服务发现失败 没有该服务" << endl;
    }
    send( fd, ( void* )&res, sizeof( res ), 0 );
}
void DEAL_HEART( int fd, ServiceRegistry_Info_REQ* req ) {
    ServiceRegistry_Info_RESP res;
    res.type    = Heart_RESP;
    res.status  = status_OK;
    res.Infolen = sizeof( res );
    Cheak_and_UpdataToHeart( fd );
    send( fd, ( void* )&res, sizeof( res ), 0 );
}
void DEAL_EXIT( int fd ) {
    // 服务下线
    pair< string, pair< string, string > > delinfo       = socket_server[ fd ];
    string                                 delservername = delinfo.first;
    pair< string, string >                 delpair       = delinfo.second;
    for ( auto it = mp_server[ delservername ].begin(); it != mp_server[ delservername ].end(); ) {
        if ( *it == delpair ) {
            cout << "[-]由于下线 删除服务" << delservername << " "
                 << "(" << it->first << "," << it->second << ")" << endl;
            it = mp_server[ delservername ].erase( it );
        } else {
            it++;
        }
    }
}

// 定时时间处理
void timedeal( sigval_t arg ) {
    switch ( arg.sival_int ) {
    case 1: {  //时钟心跳事件
        heart_time.time_go();
        //结束处理
        cout << "[S]本轮注册中心心跳检查结束 当前服务数量:" << heart_time.size() << endl;
    } break;

    default: {
        cerr << "[x]错误的未知定时信号" << endl;
        break;
    }
    }
}

// 此时时钟使用socket作为下标 true代表之前没有
bool Cheak_and_UpdataToHeart( int sockid ) {
    if ( heart_time.find_work( sockid ) ) {
        heart_time.change_work( sockid, SRCenter_heart_outtime );
        cout << "[S] 注册中心更新" << socket_server[ sockid ].first << "(" << socket_server[ sockid ].second.first << " " << socket_server[ sockid ].second.second << ")" << endl;
        return false;
    } else {
        int* arg = new int( sockid );
        heart_time.add_work( sockid, SRCenter_heart_outtime, TIMEOUT_heart, ( void* )arg );
        cout << "[S] 注册中心服务添加" << socket_server[ sockid ].first << "(" << socket_server[ sockid ].second.first << " " << socket_server[ sockid ].second.second << ")" << endl;
        return true;
    }
}

void DelToHeart( int fd ) {
    heart_time.del_work( fd );
    cout << "[S]注册中心心跳移除" << endl;
}

void* TIMEOUT_heart( void* arg ) {
    int fd = *( int* )arg;
    DEAL_EXIT( fd );
    DelToHeart( fd );
    return nullptr;
}

void clock_init() {
    //初始化时钟
    struct sigevent sev;
    bzero( &sev, sizeof( sev ) );
    sev.sigev_notify          = SIGEV_THREAD;
    sev.sigev_notify_function = timedeal;
    sev.sigev_value.sival_ptr = &heart_timer;
    sev.sigev_value.sival_int = 1;

    int err;
    err = timer_create( CLOCK_REALTIME, &sev, &heart_timer );
    if ( err )
        perror( "timer_create" );
    struct itimerspec itc;
    itc.it_interval.tv_sec  = SRCenter_heart_jgtime;
    itc.it_interval.tv_nsec = 0;
    itc.it_value.tv_sec     = SRCenter_heart_jgtime;
    itc.it_value.tv_nsec    = 0;

    err = timer_settime( heart_timer, TIMER_ABSTIME, &itc, NULL );
    if ( err )
        perror( "timer_setting" );
}

//挂载事件
void serverdeal() {
    //记录对方的socket信息
    sockaddr_in aimsockaddr;
    socklen_t   aimsocklen = sizeof( sockaddr_in );

    // accpet取出连接
    int clientfd = accept( serverfd, ( sockaddr* )&aimsockaddr, &aimsocklen );
    if ( clientfd > 0 ) {
        // cout << "[+] 新连接accpet成功" << endl;
    } else {
        perror( "[x] 新连接accpet失败" );
        pthread_exit( 0 );
    }

    //创建节点并且挂载
    struct epoll_event node;
    node.data.fd = clientfd;
    node.events  = EPOLLIN | EPOLLET | EPOLLONESHOT;
    //挂载
    int err = epoll_ctl( epollfd, EPOLL_CTL_ADD, clientfd, &node );
    if ( err != 0 ) {
        perror( "[x] 挂载节点失败" );
    } else {
        // cout << "[+] 挂载节点成功" << endl;
    }
}
//处理响应事件
void* clientdeal( void* arg ) {
    int  fd = *( int* )arg;
    char buffer[ SRCenter_event_buffer_size ];
    bzero( buffer, sizeof( buffer ) );
    //先读长度
    read( fd, buffer, 4 );
    int len = *( int* )buffer;
    // cout << "client 认为的len" << len << endl;
    read( fd, buffer + 4, len - 4 );
    //读取完成
    ServiceRegistry_Info_REQ* req = ( ServiceRegistry_Info_REQ* )buffer;

    // cout << req->Infolen << endl;
    // cout << req->type << endl;
    // cout << req->servername << endl;
    // cout << req->port << endl;
    // cout << req->ip << endl;
    switch ( req->type ) {
    case REG_REQ: {
        DEAL_REG( fd, req );
        break;
    }
    case Down_REQ: {
        DEAL_DOWN( fd, req );
        break;
    }
    case Heart_REQ: {
        DEAL_HEART( fd, req );
        break;
    }
    default: {
        if ( len != 0 )
            cout << "[x] 没有对应的请求类型 " << endl;
        else {
            cout << "[√] 断开连接请求处理 " << endl;
            DEAL_EXIT( fd );
        }
        break;
    }
    }
    if ( req->type == REG_REQ || req->type == Heart_REQ ) {  //服务端
        //保留
        struct epoll_event node;
        node.data.fd = fd;
        node.events  = EPOLLIN | EPOLLET | EPOLLONESHOT;

        int err = epoll_ctl( epollfd, EPOLL_CTL_MOD, fd, &node );
        if ( err != 0 ) {
            perror( "[x] 任务执行成功 - 修改节点失败" );
        } else {
            // cout << "[√] 任务执行成功 - 修改节点成功" << endl;
        }
    } else {
        int err = epoll_ctl( epollfd, EPOLL_CTL_DEL, fd, NULL );
        if ( err != 0 ) {
            perror( "[x] 任务执行成功 - 删除节点失败" );
        } else {
            // cout << "[√] 任务执行成功 - 删除节点成功" << endl;
        }
    }
    // DEBUG；
    // for ( auto it : mp_server ) {
    //     cout << it.first << " " << it.second.first << " " << it.second.second << endl;
    // }
    return nullptr;
}

int main() {
    //建立连接socket 开启监听
    serverfd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    int opt  = 1;
    setsockopt( serverfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof( opt ) );

    struct sockaddr_in serverfdaddr;
    socklen_t          serverfdaddr_len = sizeof( sockaddr_in );
    serverfdaddr.sin_addr.s_addr        = inet_addr( center_reg_ip );
    serverfdaddr.sin_port               = htons( center_reg_port );
    serverfdaddr.sin_family             = AF_INET;
    int err;
    err = bind( serverfd, ( sockaddr* )&serverfdaddr, serverfdaddr_len );
    if ( err != 0 ) {
        perror( "注册中心 - 绑定失败" );
        return 1;
    } else {
        cout << "注册中心 - 绑定成功" << endl;
    }
    err = listen( serverfd, 10 );
    if ( err != 0 ) {
        perror( "注册中心 - 监听失败" );
        return 1;
    } else {
        cout << "注册中心 - 监听成功" << endl;
    }

    //开始接收socket请求
    //对方信息的接收
    //   struct sockaddr_in serverfdaddr;
    //   socklen_t serverfdaddr_len = sizeof(sockaddr_in);
    //   int Nserverfd = accept(serverfd, )

    // epoll
    epollfd = epoll_create( SRCenter_epoll_event_num );
    //添加根节点
    struct epoll_event event;
    event.events  = EPOLLIN;
    event.data.fd = serverfd;
    epoll_ctl( epollfd, EPOLL_CTL_ADD, serverfd, &event );

    mypool.open();
    //开始
    // running
    while ( 1 ) {
        int num = epoll_wait( epollfd, ready_array, SRCenter_epoll_event_num, -1 );
        if ( num == -1 ) {
            perror( "epollwait:" );
            exit( 0 );
        }
        //如果我不进行处理
        //遍历每一个节点
        for ( int i = 0; i < num; i++ ) {
            //判断是不是ac
            if ( ready_array[ i ].data.fd == serverfd ) {
                serverdeal();
            } else {
                mypool.addwork( { &clientdeal, &ready_array[ i ].data.fd } );
            }
        }
    }
    close( epollfd );
}
