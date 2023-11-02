#pragma once
#include "../echo/echoservice/Echo.h"
#include "../video/videoservice/Video.h"
//rpc.h 包含所有微服务的定义
namespace rpc{
    //处理函数
    std::string  Del_echo(const std::string &s);
    std::string  VideoUpload(const std::string &s);
    std::string  VideoDownload(const std::string &s);
    void  VideoClean(const std::string &s);
};
