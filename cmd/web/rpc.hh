#pragma once
#include "../echo/echoservice/Echo.h"
#include "../video/videoservice/Video.h"
#include "../audio/audioservice/Audio.h"
#include "../user/userservice/User.h"
#include "../room/roomservice/Room.h"

//rpc.h 包含所有微服务的定义
namespace rpc{
    //处理函数
    std::string  Del_echo(const std::string &s);
    
    std::string  VideoUpload(const std::string &s);
    std::string  VideoDownload(const std::string &s);
    void  VideoClean(const std::string &s);

    std::string  AudioUpload(const std::string &s);
    std::string  AudioDownload(const std::string &s);
    void  AudioClean(const std::string &s);

    std::string User_GetBaseInfo(const std::string &s);
    std::string User_GetSocialInfo(const std::string &s);
    std::string User_GetExInfo(const std::string &s);
    std::string User_login_num(const std::string &s);
    std::string User_login_Tel(const std::string &s);
    std::string User_reg(const std::string &s);
    std::string User_logoff(const std::string &s);
    std::string User_refresh_jwt1(const std::string &s);
    std::string User_refresh_jwt2(const std::string &s);
    std::string User_ModifyBaseInfo(const std::string &s);
    std::string User_ModifySocialInfo(const std::string &s);
    std::string User_ModifyExInfo(const std::string &s);
    std::string User_follow(const std::string &s);
    std::string User_followed(const std::string &s);
    std::string User_friend(const std::string &s);

    std::string Room_ChangeDebatePos(const std::string &s );
    std::string Room_ChangeExtraInfo(const std::string &s );
    std::string Room_ChangePasswd(const std::string &s );
    std::string Room_Exitroom(const std::string &s );
    std::string Room_Joinroom(const std::string &s );
    std::string Room_Create(const std::string &s );
    std::string Room_GetURrelation(const std::string &s );
    std::string Room_GetExInfo(const std::string &s );
    std::string Room_GetBaseInfo(const std::string &s );

};
