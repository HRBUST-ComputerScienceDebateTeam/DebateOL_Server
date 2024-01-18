//这个文件启动http服务器 接受http请求
#include <arpa/inet.h>
#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>
#include <cerrno>
#include <cstddef>
#include <cstdio>
#include <ctime>
#include <fcntl.h>
#include <iostream>
#include <pthread.h>
#include <string>
#include <cstring>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include "../conf.hh"
#include "./rpc.hh"
#include <netinet/tcp.h>
//添加线程池
#include "../../pkg/pool/threadpool.h"

//DEBUG:
std::map<int , int > mp1;//fd - port ,cnt
std::map<int , int > mp2;//fd - port ,cnt
// 网络的设置
const int PORT = HTTP_POST;
// 缓冲区设置
const int BUFFER_SIZE = HTTP_REQ_BUFFER_SIZE ;
// 锁
pthread_mutex_t plock;
// 线程池优化 - 处理性能
pthread_pool_t pool(THREAD_POOL_MINTHREADNUM  , THREAD_POOL_MINTHREADNUM , THREAD_POOL_MAXTASKNUM);
// epoll
int epollfd;
struct epoll_event epoll_result[EPOLL_EVENT_MAX];
// socket 
int serverfd;
std::list<int>sockls;

// 给定sock 返回对应端口
int getpost(int sock){
    struct sockaddr_in localaddr;
    socklen_t len = sizeof(localaddr);
    int ret = getsockname(sock, (struct sockaddr*)&localaddr, &len);
    if(ret != 0)
    {
        perror("getsockname");
    }
    return ntohs(localaddr.sin_port);
}
// 属性
typedef class URI{
    public:
        //1.访问的微服务或者文件路径
        std::string path;
        //2.追加的查询条件
        std::map<std::string , std::string>query;
}uri_info;

typedef class RequestInfo{
    public:
        //1.方法
        std::string method;
        //2.URi
        uri_info uri;
        //3.版本
        std::string version;
        //4.首部字段
        std::map<std::string , std::string>options;
        //5.体
        std::string body;
    public:
        RequestInfo(std::string&);
        RequestInfo();
}RequestInfo;

/* 处理Request 的解析 */
RequestInfo::RequestInfo(std::string &s){
    
    size_t pos = s.find(' ');
    this->method = s.substr(0, pos);
    pos = s.find(' ', pos + 1);
    std::string uri = s.substr(s.find(' ') + 1, pos - s.find(' ') - 1);
    
    size_t uripos = uri.find('?');
    //如果有问号就是有选项的
    //如果没有问号就是只有url
    if(uripos == std::string::npos){
        //没有
        this->uri.path = uri;
    }else{
        this->uri.path = uri.substr(0 , uripos);
        //记录查询项
        std::string q = uri.substr(uripos+1);
        size_t andpos = std::string::npos;
        int nowpos = 0;
        do{
            
            andpos = q.find('&' , nowpos);
            size_t l = nowpos;
            size_t r = andpos;
            size_t eqpos;
            if(r != std::string::npos){
                eqpos = q.substr(l , r-l+1).find('=');//第一个等于号左侧就等于右侧
            }else{
                eqpos = q.substr(l).find('=');//第一个等于号左侧就等于右侧
            }
            this->uri.query[q.substr(l,eqpos)]= q.substr(l+eqpos+1 , r-l-eqpos-1);
            if(andpos != std::string::npos){
                nowpos = andpos+1;
            }
        }while(andpos != std::string::npos);
    }
    size_t l , r;
    l = pos+1;
    pos=s.find("\r\n" , pos+1);
    r = pos;
    this->version = s.substr(l , r-l+1);
    pos+=2;
    
    //首字段
    while(true){
        l = pos;
        pos=s.find("\r\n" , pos);
        r = pos;
        if(l == r) break;
        else pos+= 2;

        std::string tmps =s.substr(l , r-l+1);
        int tmppos = tmps.find(": ");
        this->options[tmps.substr(0 , tmppos)] = tmps.substr(tmppos+2);
    }
    this->body = s.substr(pos+2);
}

// 处理HTTP请求
std::string handleRequest(RequestInfo &reqinfo) {
    
    /* 根据选项 确定connection标志位 */
    std::string response;

    /* 设置选项 */
    int mode= 0;
    if(reqinfo.options["Connection"] == "keep-alive") mode |= 1;


    /* Get方法 */
    if (reqinfo.method == "GET") {
        /* 第一步 设置回应头 */
                    response += "HTTP/1.1 200 OK\r\n";
                    response += "Content-Type: text/html; charset=utf-8\r\n";
        if(mode&1)  response += "Connection: keep-alive\r\n";


        /* 第二步 路由 */

        //路由选择路线1 ： 视频下载
        if(reqinfo.uri.path == "/videodownload/" ){

            std::cout << "\tvideodownload" << std::endl;
            if(reqinfo.uri.query.find("info")!= reqinfo.uri.query.end()){
                std::string s = rpc::VideoDownload(reqinfo.uri.query["info"]);
                response += "Content-Length: ";
                response += std::string( std::to_string(s.length()));
                response += "\r\n\r\n";
                response += s;
            }

        //路由选择路线2 ： 音频下载
        }else if(reqinfo.uri.path == "/audiodownload/" ){
            
            std::cout << "\taudiodownload" << std::endl;
            if(reqinfo.uri.query.find("info")!= reqinfo.uri.query.end()){
                std::string s = rpc::AudioDownload(reqinfo.uri.query["info"]);
                response += "Content-Length: ";
                response += std::string( std::to_string(s.length()));
                response += "\r\n\r\n";
                response += s;
            }

        //路由选择路线 - 匹配失败
        }else{
            std::string s = "<html><head><title>Get Request</title></head><body><h1>Get Request Received!</h1></body></html>";
            response += "Content-Length: ";
            response += std::string( std::to_string(s.length()));
            response += "\r\n\r\n";
            response += s;
        }

    /* Post方法 */
    } else if (reqinfo.method  == "POST") {
        /* 第一步 设置回应头 */
                    response += "HTTP/1.1 200 OK\r\n";
                    response += "Content-Type: text/html; charset=utf-8\r\n";
        if(mode&1)  response += "Connection: keep-alive\r\n";
        

        /* 第二步 路由 */
        //路由选择路线1 ： echo
        if(reqinfo.uri.path == "/echo"){

            std::cout << "\techo post" << std::endl;
            std::string s = rpc::Del_echo(reqinfo.body);
            response += "Content-Length: ";
            response += std::string( std::to_string(s.length()));
            response += "\r\n\r\n";
            response += s;

        }
        //路由选择路线2 ： 视频上传
        else if(reqinfo.uri.path == "/videoupload"){
            std::cout << "\tvideoupload" << std::endl;
            std::string s = rpc::VideoUpload(reqinfo.body);
            response += "Content-Length: ";
            response += std::string( std::to_string(s.length()));
            response += "\r\n\r\n";
            response += s;

        //路由选择路线3 ： 视频删除
        }else if(reqinfo.uri.path == "/videoclean"){

            std::cout << "\tvideoclean" << std::endl;
            rpc::VideoClean(reqinfo.body);

        //路由选择路线4 ： 音频上传
        }else if(reqinfo.uri.path == "/audioupload"){

            std::cout << "\taudioupload" << std::endl;
            std::string s = rpc::AudioUpload(reqinfo.body);
            response += "Content-Length: ";
            response += std::string( std::to_string(s.length()));
            response += "\r\n\r\n";
            response += s;

        //路由选择路线5 ： 音频清空
        }else if(reqinfo.uri.path == "/audioclean"){

            std::cout << "\taudioclean" << std::endl;
            rpc::AudioClean(reqinfo.body);

        //路由选择路线 - 匹配失败
        }else{
            std::string s = "<html><head><title>POST Request</title></head><body><h1>POST Request Received!</h1></body></html>";
            response += "Content-Length: ";
            response += std::string( std::to_string(s.length()));
            response += "\r\n\r\n";
            response += s;
        }

    } else {
        // 处理其他请求
        response = "HTTP/1.1 404 Not Found\r\n"
                   "Content-Type: text/html; charset=utf-8\r\n"
                   "Content-Length: "
                   + std::to_string(sizeof("<html><head><title>Not Found</title></head><body><h1>404 Not Found</h1></body></html>"))
                   + "\r\n\r\n"
                   "<html><head><title>Not Found</title></head><body><h1>404 Not Found</h1></body></html>";
    }

    return response;
}

// 处理客户端信息
void* handleClient(void * arg) {
    /* 线程任务
    *   取出参数 
    *   先读入头部 头部取出对应的文本长度
    *   按照Content-Length 去读入内容  - 解决半包粘包
    */


    /* 取出参数 */
    int client_socket = *(int *) arg;
    char buffer[BUFFER_SIZE];
    int Had_readed = 0;
    int Body_Length = 0;
    int Need_read = 0;
    int Recvlen_1 = 0;
    int Recvlen_2 = 0;

    
    /* 读入头 - 取出对应的文本长度 */
    while(true){
        //通常自定义包头200左右 300 为了限定不会接受两个包
        Recvlen_1 = recv(client_socket, buffer + Had_readed, 300 , MSG_DONTWAIT);

        if(Recvlen_1 < 0){
            
            //如果是数据没有准备好就等等
            if(errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR ) continue;
            //其他的异常就退出
            break;

        }else if(Recvlen_1 == 0){
            //if(errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR ) continue;
            //如果客户端已经断开连接
            std::cout << "Web - 客户端断开1" <<std::endl;

            //记录每个端口的套接字服务了多少任务量
            //std::cout << mp2[client_socket] <<"服务了" << mp1[client_socket] <<"个任务" << std::endl; 
            //mp1[client_socket] = 0;

            epoll_ctl(epollfd, EPOLL_CTL_DEL, client_socket,NULL);
            close(client_socket);
            free(arg);
            return nullptr;

        }else{
            
            //如果读到数据了
            Had_readed+= Recvlen_1;
            
            //寻找\r\n\r\n;
            std::string request(buffer);
            std::basic_string<char>::size_type pos = request.find("\r\n\r\n",0);
            
            //没有找到继续读入
            if(pos == std::string::npos) continue;
                
            //解析
            RequestInfo reqinfo(request);

            //获取长度
            if(reqinfo.options.find("Content-Length")!= reqinfo.options.end()){
                Body_Length = stoi(reqinfo.options["Content-Length"]);
            }

            //计算剩余的还需要读入多少
            Need_read = Body_Length;
            Need_read += (pos+4);
            Need_read -= Had_readed;
            
            //找到就可以跳出了
            break;
        }
    }


    /* 把剩余的信息读取出来 */
    while(Need_read){
        //读取出来的长度
        Recvlen_2 = recv(client_socket, buffer + Had_readed, BUFFER_SIZE - Had_readed , MSG_DONTWAIT);

        if(Recvlen_2 > 0){
            
            //把数据读入
            Had_readed += Recvlen_2;
            Need_read -= Recvlen_2;

        }else if(Recvlen_2 == 0){//连接关闭

            //如果客户端已经断开连接
            std::cout << "Web - 客户端断开2" <<std::endl;
            epoll_ctl(epollfd, EPOLL_CTL_DEL, client_socket,NULL);
            close(client_socket);
            free(arg);
            return nullptr;

        }else{
            if(errno != EAGAIN) {
                perror("read 异常退出");
                break;
            }
        }
    }

    // 解析HTTP请求
    std::string request(buffer);
    RequestInfo reqinfo(request);    
    std::string response = handleRequest(reqinfo);
    
    // 回复信息
    send(client_socket, response.c_str(), response.length(), MSG_NOSIGNAL);
    
    //记录每个端口的套接字服务了多少任务量
    //mp1[client_socket]++;

    // 重新挂载节点
    struct epoll_event epollnode1;
    epollnode1.data.fd = client_socket;
    epollnode1.events =EPOLLIN|EPOLLET|EPOLLONESHOT;
    epoll_ctl(epollfd , EPOLL_CTL_MOD , client_socket , &epollnode1);
    
    // 线程池自带 回收资源
    free(arg);
    return nullptr;
}


int main() {
    //初始化锁
    pthread_mutex_init(&plock , NULL);

    // 创建TCP套接字
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd == -1) {
        std::cerr << "Create socket failed!" << std::endl;
        return -1;
    }

    //复用端口
    int opt = 1;
    setsockopt(serverfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    //监听套接字 非阻塞 防止客户端再accept之后 取出之前关闭了
    int flag = fcntl(serverfd,F_GETFL,0);
    fcntl(serverfd,F_SETFL,flag|O_NONBLOCK);
    

    // 绑定地址
    struct sockaddr_in server_address{};
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(serverfd, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        std::cerr << "Bind failed!" << std::endl;
        return -1;
    }

    // 监听端口
    if (listen(serverfd, SOMAXCONN) == -1) {
        std::cerr << "Listen failed!" << std::endl;
        return -1;
    }
    
    std::cout << "Server started. Listening on port " << PORT << "..." << std::endl;

    // 线程池开启服务
    pool.open();
    
    //EPOLL IO复用优化
    epollfd = epoll_create(EPOLL_EVENT_MAX);
    struct epoll_event epollnode;
    epollnode.data.fd = serverfd;
    epollnode.events =EPOLLIN;
    epoll_ctl(epollfd , EPOLL_CTL_ADD , serverfd , &epollnode);


    while (true) {
        int readynum = epoll_wait(epollfd,epoll_result , EPOLL_EVENT_MAX, 0);
        for(int i = 0;i<readynum;i++){
            int sockfd = epoll_result[i].data.fd;
            if(sockfd == serverfd){
                struct sockaddr_in client_address;
                socklen_t client_address_len = sizeof(client_address);
                int client_socket = accept(serverfd, (struct sockaddr *) &client_address, &client_address_len);
                if (client_socket == -1) {
                    perror("Accept failed!");//错误
                }else{
                    //tcp keepalive
                    int keepalive = 1; // 开启keepalive属性
                    int keepidle = 20; // 如该连接在20秒内没有任何数据往来,则进行探测
                    int keepinterval = 3; // 探测时发包的时间间隔为3 秒
                    int keepcount = 5; // 探测尝试的次数.如果第5次探测包就收到响应了,则后2次的不再发.
                    setsockopt(client_socket, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepalive , sizeof(keepalive ));
                    setsockopt(client_socket, SOL_TCP, TCP_KEEPIDLE, (void*)&keepidle , sizeof(keepidle ));
                    setsockopt(client_socket, SOL_TCP, TCP_KEEPINTVL, (void *)&keepinterval , sizeof(keepinterval ));
                    setsockopt(client_socket, SOL_TCP, TCP_KEEPCNT, (void *)&keepcount , sizeof(keepcount ));

                    //客户端的绑定
                    struct epoll_event epollnode1;
                    epollnode1.data.fd = client_socket;
                    epollnode1.events =EPOLLIN|EPOLLET|EPOLLONESHOT;
                    epoll_ctl(epollfd , EPOLL_CTL_ADD , client_socket , &epollnode1);
                    sockls.push_back(client_socket);
                    
                    
                    //记录每个端口的套接字服务了多少任务量
                    // std::cout << "建立连接  " << "Port : " << client_address.sin_port <<  std::endl;
                    // mp2[client_socket] = client_address.sin_port;
                }
            }else{

                /* client recv事件的任务添加*/
                int * client_socket = new int(epoll_result[i].data.fd);
                pool.addwork({&handleClient , (void*)client_socket});

            }
        }
    }


    // 关闭服务器套接字
    close(serverfd);
    for(auto sockfd:sockls){
        close(sockfd);
    }

    //释放锁
    pthread_mutex_destroy(&plock);

    return 0;
}