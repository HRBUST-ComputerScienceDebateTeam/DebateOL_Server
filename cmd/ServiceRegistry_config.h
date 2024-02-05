#pragma once
#ifndef SRCCONFIG
#define SRCCONFIG

//配置抽离
const int SRCenter_pool_thread_max   = 100;
const int SRCenter_pool_thread_min   = 10;
const int SRCenter_pool_queue_max    = 10000;
const int SRCenter_epoll_event_num   = 1024;
const int SRCenter_event_buffer_size = 1005;
const int SRCenter_heart_outtime     = 120;
const int SRCenter_heart_jgtime      = 30;  // 30s

// type
const int REG_REQ  = 1;  //服务端注册请求
const int REG_RESP = 2;  //服务端注册回复

const int Down_REQ   = 3;  //客户端下载请求
const int Down_RESP  = 4;  //客户端下载回复
const int Heart_REQ  = 5;  //客户端下载请求
const int Heart_RESP = 6;  //客户端下载回复

// status
const int status_OK  = 200;
const int status_ERR = 400;

//协议结构体
class ServiceRegistry_Info_REQ {
public:
    int Infolen;

public:
    int  type;
    char servername[ 100 ];
    char ip[ 20 ];
    char port[ 10 ];
    // string servername;
    // string ip;
    // string port;
};

//应答结构体
class ServiceRegistry_Info_RESP {
public:
    int Infolen;  //返回信息长度

public:
    int  type;    //类型
    int  status;  //状态码
    char respinfo[ 1000 ];
};

//服务中心地址定义
const int   center_reg_port = 5590;
const char* center_reg_ip   = "127.0.0.1";

#endif