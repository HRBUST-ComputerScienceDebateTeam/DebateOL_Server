//配置文件
#pragma once

//http服务器
#define HTTP_IP "127.0.0.1"
#define HTTP_PORT 8080
#define HTTP_REQ_BUFFER_SIZE 102400

//https服务器
#define HTTPS_IP "127.0.0.1"
#define HTTPS_PORT 4430

//echo微服务
#define ECHO_IP "127.0.0.1"
#define ECHO_PORT 9001


//VIDEO微服务
#define VIDEO_IP "127.0.0.1"
#define VIDEO_PORT 9002

//AUDIO微服务
#define AUDIO_IP "127.0.0.1"
#define AUDIO_PORT 9003

//USER微服务
#define USER_IP "127.0.0.1"
#define USER_PORT 9004


//状态字
#define MAX_ROOM 1000
#define MAX_USER 1000

#define VIDEO_OK 200
#define VIDEO_NO_PNG 300
#define VIDEO_WRONG_DOWNLOAD_TYPE 400

#define AUDIO_OK 200
#define AUDIO_NO_INFO 300
#define AUDIO_WRONG_DOWNLOAD_TYPE 400

#define USER_ACTION_OK           200
#define USER_WRONG_DOWNLOAD_TYPE 400
#define USER_LOWLEVEL_JWT        403
#define USER_TIMEOUT_JWT         405
#define USER_ERR_REQINFO         406
#define USER_LOGIN_ERRINFO       408
#define User_Reg_Havethisnum     409
#define User_Reg_Havethistel     410
#define USER_DAL_ERR             502


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

const int User_GetBaseInfo_SendInfo_TypeId = 301;
const int User_GetBaseInfo_RecvInfo_TypeId = 302;
const int User_GetSocialInfo_SendInfo_TypeId = 303;
const int User_GetSocialInfo_RecvInfo_TypeId = 304;
const int User_GetExtraInfo_SendInfo_TypeId = 305;
const int User_GetExtraInfo_RecvInfo_TypeId = 306;

const int User_LoginNum_SendInfo_TypeId = 310;
const int User_LoginTel_SendInfo_TypeId = 311;
const int User_Login_RecvInfo_TypeId    = 312;

const int User_Reg_TypeId = 313;



//时间
const int time_hour   = 60*60;
const int time_minute = 60   ;
const int time_second = 1    ;
const int jwt_time         = 10*time_minute;
const int refresh_jwt_time =  2*time_hour  ;


//密码加密：
// 1. 登陆申请提交的是 base64 + sha256 的passwd
// 2. 盐是            base64 + sha256 的存入数据库
// 3. 数据库中的密码 是上述两个相加 之后 sha256 存入数据库
//数据库
const int No_such_uid     = -1;
const int No_such_usernum = -2;
const int No_such_tel     = -3;
const int No_such_username= -4;

//Access level -- uu 用户关系 
enum AC_Level_uu{
    level_self     =  0,
    level_friend   =  3,
    level_follow   =  6,
    level_stranger =  9,
    level_black    =  12
};

//Access level -- ur 
// enum Jwt_Level_ur{
//     level_self     =  0,
//     level_friend   =  1,
//     level_stranger =  2,
//     level_black    =  3
// };

