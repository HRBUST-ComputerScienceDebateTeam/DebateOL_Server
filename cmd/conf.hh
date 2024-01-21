//配置文件
#pragma once

//http服务器
#include <string>
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

//Room微服务
#define ROOM_IP "127.0.0.1"
#define ROOM_PORT 9005

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
#define USER_LOWACLevel          403
#define USER_TIMEOUT_JWT         405
#define USER_ERR_REQINFO         406
#define USER_LOGIN_ERRINFO       408
#define User_Reg_Havethisnum     409
#define User_Reg_Havethistel     410
#define User_Logoff_notonline    415
#define User_JWT_NOTOUTTIME      420
#define User_REJWT_NOTOUTTIME    421
#define User_REJWT_HAVEOUTTIME   422

#define USER_DAL_ERR             502

#define ROOM_ACTION_OK           200
#define ROOM_LOWACLevel          403
#define ROOM_TIMEOUT_JWT         405
#define ROOM_ERR_REQINFO         406
#define ROOM_NoSuchRoomInfo      407
#define ROOM_Create_Havethisnum  409
#define ROOM_JOINROOM_ERRPASSWD  410
#define ROOM_Changepos_Havepeo   412
#define ROOM_DAL_ERR             502


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

const int User_GetBaseInfo_SendInfo_TypeId   = 301;
const int User_GetBaseInfo_RecvInfo_TypeId   = 302;
const int User_GetSocialInfo_SendInfo_TypeId = 303;
const int User_GetSocialInfo_RecvInfo_TypeId = 304;
const int User_GetExtraInfo_SendInfo_TypeId  = 305;
const int User_GetExtraInfo_RecvInfo_TypeId  = 306;

const int User_LoginNum_SendInfo_TypeId = 310;
const int User_LoginTel_SendInfo_TypeId = 311;
const int User_Login_RecvInfo_TypeId    = 312;
const int User_Reg_SendInfo_TypeId      = 313;
const int User_Reg_RecvInfo_TypeId      = 314;

const int User_logoff_SendInfo_TypeId          = 321;
const int User_logoff_RecvInfo_TypeId          = 322;
const int User_refresh_jwt1_SendInfo_TypeId    = 323;
const int User_refresh_jwt1_RecvInfo_TypeId    = 324;
const int User_refresh_jwt2_SendInfo_TypeId    = 325;
const int User_refresh_jwt2_RecvInfo_TypeId    = 326;
const int User_friend_SendInfo_TypeId          = 331;
const int User_friend_RecvInfo_TypeId          = 332;
const int User_follow_SendInfo_TypeId          = 333;
const int User_follow_RecvInfo_TypeId          = 334;
const int User_followed_SendInfo_TypeId        = 335;
const int User_followed_RecvInfo_TypeId        = 336;
const int User_ModifyBaseInfo_SendInf_TypeId   = 341;
const int User_ModifyBaseInfo_RecvInfo_TypeId  = 342;
const int User_ModifySocialInfo_SendInfo_TypeId= 343;
const int User_ModifySocialInfo_RecvInfo_TypeId= 344;
const int User_ModifyExInfo_SendInfo_TypeId    = 345;
const int User_ModifyExInfo_RecvInfo_TypeId    = 346;


const int Room_GetBaseInfo_RecvInfo_TypeId      = 401;   
const int Room_GetBaseInfo_SendInfo_TypeId      = 402;   
const int Room_GetExInfo_RecvInfo_TypeId        = 403;
const int Room_GetExInfo_SendInfo_TypeId        = 404;
const int Room_GetURrelation_RecvInfo_TypeId    = 405; 
const int Room_GetURrelation_SendInfo_TypeId    = 406;  
const int Room_Create_RecvInfo_TypeId           = 407; 
const int Room_Create_SendInfo_TypeId           = 408;  
const int Room_Joinroom_RecvInfo_TypeId         = 409; 
const int Room_Joinroom_SendInfo_TypeId         = 410;   
const int Room_Exitroom_RecvInfo_TypeId         = 411;   
const int Room_Exitroom_SendInfo_TypeId         = 412;
const int Room_ChangePasswd_RecvInfo_TypeId     = 413;  
const int Room_ChangePasswd_SendInfo_TypeId     = 414;  
const int Room_ChangeExtraInfo_RecvInfo_TypeId  = 415;                
const int Room_ChangeExtraInfo_SendInfo_TypeId  = 416;                              
const int Room_ChangeDebatePos_RecvInfo_TypeId  = 417; 
const int Room_ChangeDebatePos_SendInfo_TypeId  = 418; 
        
         
         
       
       
              
               
          
             
   

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

const int INT_DEFAULT = -1;
const std::string STR_DEFAULT = "";

//Access level -- uu 用户关系 
enum AC_Level_uu{
    level_never_uu    =  0,
    level_self_uu     =  1,
    level_friend_uu   =  3,
    level_follow_uu   =  6,
    level_stranger_uu =  9,
    level_black_uu    =  12
};

enum AC_Level_ur{
    level_never_ur       =  0,
    level_root_ur        =  1,
    level_inroom_ur      =  3,
    level_notinroom_ur   =  4,
    level_black_ur       =  9
};
//Access level -- ur 
// enum Jwt_Level_ur{
//     level_self     =  0,
//     level_friend   =  1,
//     level_stranger =  2,
//     level_black    =  3
// };

