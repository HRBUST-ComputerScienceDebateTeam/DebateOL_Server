#pragma once
#include "../echo/echoservice/Echo.h"
//rpc.h 包含所有微服务的定义
namespace rpc{
    //处理函数
    std::string  Del_echo(const std::string &s);
};
