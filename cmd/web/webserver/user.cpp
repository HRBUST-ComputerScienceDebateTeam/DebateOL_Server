//本质上是微服务的客户端
#include <cstdio>
#include <iostream>
#include <random>
#include <string>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include "../rpc.hh"
#include "../json.hh"
#include "../../conf.hh"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;


namespace rpc{
    std::string User_GetBaseInfo(const std::string &s);
    std::string User_GetSocialInfo(const std::string &s);
    std::string User_GetExInfo(const std::string &s);
    std::string User_login_num(const std::string &s);
    std::string User_login_Tel(const std::string &s){
        std::shared_ptr<TTransport> user_socket(new TSocket(USER_IP, USER_PORT));
        std::shared_ptr<TTransport> user_transport(new TBufferedTransport(user_socket));
        std::shared_ptr<TProtocol> user_protocol(new TBinaryProtocol(user_transport));
        UserClient user_client(user_protocol);
        user_transport->open();
        //反序列化
        // cout <<"-----0----"<< endl;
        // cout << s <<endl;
        User_login_Tel_SendInfo sendinfo = Deserialization<User_login_Tel_SendInfo>(s);
        //  cout <<"-----1---"<< endl;
        //  cout << sendinfo.info <<endl;
        User_login_RecvInfo recvinfo;
        //  cout <<"-----2---"<< endl;  
        //调用微服务
        user_client.User_login_Tel(recvinfo, sendinfo);
        // cout <<"-----3----"<<endl;
        user_transport->close();
        return Serialization(recvinfo);
    }
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

}
