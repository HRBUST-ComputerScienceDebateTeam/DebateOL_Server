//配置文件
#pragma once

//http服务器
#define HTTP_IP "127.0.0.1"
#define HTTP_POST 8080
#define HTTP_REQ_BUFFER_SIZE 102400

//https服务器
#define HTTPS_IP "127.0.0.1"
#define HTTPS_POST 4430

//echo微服务
#define ECHO_IP "127.0.0.1"
#define ECHO_POST 9001


//VIDEO微服务
#define VIDEO_IP "127.0.0.1"
#define VIDEO_POST 9002

//AUDIO微服务
#define AUDIO_IP "127.0.0.1"
#define AUDIO_POST 9003


//状态字
#define MAX_ROOM 1000
#define MAX_USER 1000

#define VIDEO_OK 200
#define VIDEO_NO_PNG 300
#define VIDEO_WRONG_DOWNLOAD_TYPE 400


#define AUDIO_OK 200
#define AUDIO_NO_INFO 300
#define AUDIO_WRONG_DOWNLOAD_TYPE 400

//线程池的参数
#define THREAD_POOL_MAXTHREADNUM (100)
#define THREAD_POOL_MINTHREADNUM (10)
#define THREAD_POOL_MAXTASKNUM (1000)

//epoll
#define EPOLL_EVENT_MAX 1024

//typeid 

const int Video_Upload_SendInfo_TypeId = 101;
const int Video_Upload_RecvInfo_TypeId = 102;
const int Video_Download_SendInfo_TypeId = 103;
const int Video_Download_RecvInfo_TypeId = 104;
const int Video_Clean_SendInfo_TypeId = 105; 

const int Audio_Upload_SendInfo_TypeId = 201;
const int Audio_Upload_RecvInfo_TypeId = 202;
const int Audio_Download_SendInfo_TypeId = 203;
const int Audio_Download_RecvInfo_TypeId = 204;
const int Audio_Clean_SendInfo_TypeId = 205; 


