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
#include "../../../pkg/ChangeStr_Base64/ChangeStr_Base64_user.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;


#define RPC_DEFINE_FOR_SENDINFO(x) x##_SendInfo
#define RPC_DEFINE_FOR_RECVINFO(x) x##_RecvInfo

namespace rpc{
    std::string User_GetBaseInfo(const std::string &s){
        std::shared_ptr<TTransport> user_socket(new TSocket(USER_IP, USER_PORT));
        std::shared_ptr<TTransport> user_transport(new TBufferedTransport(user_socket));
        std::shared_ptr<TProtocol> user_protocol(new TBinaryProtocol(user_transport));
        UserClient user_client(user_protocol);
        user_transport->open();
        //反序列化
        // cout <<"-----0----"<< endl;
        // cout << s <<endl;
        RPC_DEFINE_FOR_SENDINFO(User_GetBaseInfo) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(User_GetBaseInfo)>(s);
        sendinfo = ChangeStr_decodebase64(sendinfo);
        //  cout <<"-----1---"<< endl;
        //  cout << sendinfo.info <<endl;
        RPC_DEFINE_FOR_RECVINFO(User_GetBaseInfo) recvinfo;
        //  cout <<"-----2---"<< endl;  
        //调用微服务
        recvinfo = ChangeStr_encodebase64(recvinfo);
        user_client.User_GetBaseInfo(recvinfo, sendinfo);
        // cout <<"-----3----"<<endl;
        user_transport->close();
        return Serialization(recvinfo);
    }
    std::string User_GetSocialInfo(const std::string &s){
        std::shared_ptr<TTransport> user_socket(new TSocket(USER_IP, USER_PORT));
        std::shared_ptr<TTransport> user_transport(new TBufferedTransport(user_socket));
        std::shared_ptr<TProtocol> user_protocol(new TBinaryProtocol(user_transport));
        UserClient user_client(user_protocol);
        user_transport->open();
        //反序列化
        // cout <<"-----0----"<< endl;
        // cout << s <<endl;
        RPC_DEFINE_FOR_SENDINFO(User_GetSocialInfo) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(User_GetSocialInfo)>(s);
        sendinfo = ChangeStr_decodebase64(sendinfo);
        //  cout <<"-----1---"<< endl;
        //  cout << sendinfo.info <<endl;
        RPC_DEFINE_FOR_RECVINFO(User_GetSocialInfo) recvinfo;
        //  cout <<"-----2---"<< endl;  
        //调用微服务
        recvinfo = ChangeStr_encodebase64(recvinfo);
        user_client.User_GetSocialInfo(recvinfo, sendinfo);
        // cout <<"-----3----"<<endl;
        user_transport->close();
        return Serialization(recvinfo);
    }
    std::string User_GetExInfo(const std::string &s){
        std::shared_ptr<TTransport> user_socket(new TSocket(USER_IP, USER_PORT));
        std::shared_ptr<TTransport> user_transport(new TBufferedTransport(user_socket));
        std::shared_ptr<TProtocol> user_protocol(new TBinaryProtocol(user_transport));
        UserClient user_client(user_protocol);
        user_transport->open();
        //反序列化
        // cout <<"-----0----"<< endl;
        // cout << s <<endl;
        RPC_DEFINE_FOR_SENDINFO(User_GetExInfo) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(User_GetExInfo)>(s);
        sendinfo = ChangeStr_decodebase64(sendinfo);
        //  cout <<"-----1---"<< endl;
        //  cout << sendinfo.info <<endl;
        RPC_DEFINE_FOR_RECVINFO(User_GetExInfo) recvinfo;
        //  cout <<"-----2---"<< endl;  
        //调用微服务
        user_client.User_GetExInfo(recvinfo, sendinfo);
        recvinfo = ChangeStr_encodebase64(recvinfo);
        // cout <<"-----3----"<<endl;
        user_transport->close();
        return Serialization(recvinfo);
    }
    std::string User_login_num(const std::string &s){
        std::shared_ptr<TTransport> user_socket(new TSocket(USER_IP, USER_PORT));
        std::shared_ptr<TTransport> user_transport(new TBufferedTransport(user_socket));
        std::shared_ptr<TProtocol> user_protocol(new TBinaryProtocol(user_transport));
        UserClient user_client(user_protocol);
        user_transport->open();
        //反序列化
        // cout <<"-----0----"<< endl;
        // cout << s <<endl;
        RPC_DEFINE_FOR_SENDINFO(User_login_num) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(User_login_num)>(s);
        sendinfo = ChangeStr_decodebase64(sendinfo);
        //  cout <<"-----1---"<< endl;
        //  cout << sendinfo.info <<endl;
        User_login_RecvInfo recvinfo;
        //  cout <<"-----2---"<< endl;  
        //调用微服务
        user_client.User_login_num(recvinfo, sendinfo);
        recvinfo = ChangeStr_encodebase64(recvinfo);
        // cout <<"-----3----"<<endl;
        user_transport->close();
        return Serialization(recvinfo);
    }
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
        sendinfo = ChangeStr_decodebase64(sendinfo);
        //  cout <<"-----1---"<< endl;
        //  cout << sendinfo.info <<endl;
        User_login_RecvInfo recvinfo;
        //  cout <<"-----2---"<< endl;  
        //调用微服务
        user_client.User_login_Tel(recvinfo, sendinfo);
        recvinfo = ChangeStr_encodebase64(recvinfo);
        // cout <<"-----3----"<<endl;
        user_transport->close();
        return Serialization(recvinfo);
    }
    std::string User_reg(const std::string &s){
        std::shared_ptr<TTransport> user_socket(new TSocket(USER_IP, USER_PORT));
        std::shared_ptr<TTransport> user_transport(new TBufferedTransport(user_socket));
        std::shared_ptr<TProtocol> user_protocol(new TBinaryProtocol(user_transport));
        UserClient user_client(user_protocol);
        user_transport->open();
        //反序列化
        // cout <<"-----0----"<< endl;
        // cout << s <<endl;
        RPC_DEFINE_FOR_SENDINFO(User_reg) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(User_reg)>(s);
        sendinfo = ChangeStr_decodebase64(sendinfo);
        //  cout <<"-----1---"<< endl;
        //  cout << sendinfo.info <<endl;
        RPC_DEFINE_FOR_RECVINFO(User_reg) recvinfo;
        //  cout <<"-----2---"<< endl;  
        //调用微服务
        user_client.User_reg(recvinfo, sendinfo);
        recvinfo = ChangeStr_encodebase64(recvinfo);
        // cout <<"-----3----"<<endl;
        user_transport->close();
        return Serialization(recvinfo);
    }
    std::string User_logoff(const std::string &s){
        std::shared_ptr<TTransport> user_socket(new TSocket(USER_IP, USER_PORT));
        std::shared_ptr<TTransport> user_transport(new TBufferedTransport(user_socket));
        std::shared_ptr<TProtocol> user_protocol(new TBinaryProtocol(user_transport));
        UserClient user_client(user_protocol);
        user_transport->open();
        //反序列化
        // cout <<"-----0----"<< endl;
        // cout << s <<endl;
        RPC_DEFINE_FOR_SENDINFO(User_logoff) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(User_logoff)>(s);
        sendinfo = ChangeStr_decodebase64(sendinfo);
        //  cout <<"-----1---"<< endl;
        //  cout << sendinfo.info <<endl;
        RPC_DEFINE_FOR_RECVINFO(User_logoff) recvinfo;
        //  cout <<"-----2---"<< endl;  
        //调用微服务
        user_client.User_logoff(recvinfo, sendinfo);
        recvinfo = ChangeStr_encodebase64(recvinfo);
        // cout <<"-----3----"<<endl;
        user_transport->close();
        return Serialization(recvinfo);
    }
    std::string User_refresh_jwt1(const std::string &s){
        std::shared_ptr<TTransport> user_socket(new TSocket(USER_IP, USER_PORT));
        std::shared_ptr<TTransport> user_transport(new TBufferedTransport(user_socket));
        std::shared_ptr<TProtocol> user_protocol(new TBinaryProtocol(user_transport));
        UserClient user_client(user_protocol);
        user_transport->open();
        //反序列化
        // cout <<"-----0----"<< endl;
        // cout << s <<endl;
        RPC_DEFINE_FOR_SENDINFO(User_refresh_jwt1) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(User_refresh_jwt1)>(s);
        sendinfo = ChangeStr_decodebase64(sendinfo);
        //  cout <<"-----1---"<< endl;
        //  cout << sendinfo.info <<endl;
        RPC_DEFINE_FOR_RECVINFO(User_refresh_jwt1) recvinfo;
        //  cout <<"-----2---"<< endl;  
        //调用微服务
        recvinfo = ChangeStr_encodebase64(recvinfo);
        user_client.User_refresh_jwt1(recvinfo, sendinfo);
        // cout <<"-----3----"<<endl;
        user_transport->close();
        return Serialization(recvinfo);
    }
    std::string User_refresh_jwt2(const std::string &s){
        std::shared_ptr<TTransport> user_socket(new TSocket(USER_IP, USER_PORT));
        std::shared_ptr<TTransport> user_transport(new TBufferedTransport(user_socket));
        std::shared_ptr<TProtocol> user_protocol(new TBinaryProtocol(user_transport));
        UserClient user_client(user_protocol);
        user_transport->open();
        //反序列化
        // cout <<"-----0----"<< endl;
        // cout << s <<endl;
        RPC_DEFINE_FOR_SENDINFO(User_refresh_jwt2) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(User_refresh_jwt2)>(s);
        sendinfo = ChangeStr_decodebase64(sendinfo);
        //  cout <<"-----1---"<< endl;
        //  cout << sendinfo.info <<endl;
        RPC_DEFINE_FOR_RECVINFO(User_refresh_jwt2) recvinfo;
        //  cout <<"-----2---"<< endl;  
        //调用微服务
        recvinfo = ChangeStr_encodebase64(recvinfo);
        user_client.User_refresh_jwt2(recvinfo, sendinfo);
        // cout <<"-----3----"<<endl;
        user_transport->close();
        return Serialization(recvinfo);
    }
    std::string User_ModifyBaseInfo(const std::string &s){
        std::shared_ptr<TTransport> user_socket(new TSocket(USER_IP, USER_PORT));
        std::shared_ptr<TTransport> user_transport(new TBufferedTransport(user_socket));
        std::shared_ptr<TProtocol> user_protocol(new TBinaryProtocol(user_transport));
        UserClient user_client(user_protocol);
        user_transport->open();
        //反序列化
        // cout <<"-----0----"<< endl;
        // cout << s <<endl;
        RPC_DEFINE_FOR_SENDINFO(User_ModifyBaseInfo) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(User_ModifyBaseInfo)>(s);
        sendinfo = ChangeStr_decodebase64(sendinfo);
        //  cout <<"-----1---"<< endl;
        //  cout << sendinfo.info <<endl;
        RPC_DEFINE_FOR_RECVINFO(User_ModifyBaseInfo) recvinfo;
        //  cout <<"-----2---"<< endl;  
        //调用微服务
        recvinfo = ChangeStr_encodebase64(recvinfo);
        user_client.User_ModifyBaseInfo(recvinfo, sendinfo);
        // cout <<"-----3----"<<endl;
        user_transport->close();
        return Serialization(recvinfo);
    }
    std::string User_ModifySocialInfo(const std::string &s){
        std::shared_ptr<TTransport> user_socket(new TSocket(USER_IP, USER_PORT));
        std::shared_ptr<TTransport> user_transport(new TBufferedTransport(user_socket));
        std::shared_ptr<TProtocol> user_protocol(new TBinaryProtocol(user_transport));
        UserClient user_client(user_protocol);
        user_transport->open();
        //反序列化
        // cout <<"-----0----"<< endl;
        // cout << s <<endl;
        RPC_DEFINE_FOR_SENDINFO(User_ModifySocialInfo) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(User_ModifySocialInfo)>(s);
        sendinfo = ChangeStr_decodebase64(sendinfo);
        //  cout <<"-----1---"<< endl;
        //  cout << sendinfo.info <<endl;
        RPC_DEFINE_FOR_RECVINFO(User_ModifySocialInfo) recvinfo;
        //  cout <<"-----2---"<< endl;  
        //调用微服务
        recvinfo = ChangeStr_encodebase64(recvinfo);
        user_client.User_ModifySocialInfo(recvinfo, sendinfo);
        // cout <<"-----3----"<<endl;
        user_transport->close();
        return Serialization(recvinfo);
    }
    std::string User_ModifyExInfo(const std::string &s){
        std::shared_ptr<TTransport> user_socket(new TSocket(USER_IP, USER_PORT));
        std::shared_ptr<TTransport> user_transport(new TBufferedTransport(user_socket));
        std::shared_ptr<TProtocol> user_protocol(new TBinaryProtocol(user_transport));
        UserClient user_client(user_protocol);
        user_transport->open();
        //反序列化
        // cout <<"-----0----"<< endl;
        // cout << s <<endl;
        RPC_DEFINE_FOR_SENDINFO(User_ModifyExInfo) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(User_ModifyExInfo)>(s);
        sendinfo = ChangeStr_decodebase64(sendinfo);
        //  cout <<"-----1---"<< endl;
        //  cout << sendinfo.info <<endl;
        RPC_DEFINE_FOR_RECVINFO(User_ModifyExInfo) recvinfo;
        //  cout <<"-----2---"<< endl;  
        //调用微服务
        recvinfo = ChangeStr_encodebase64(recvinfo);
        user_client.User_ModifyExInfo(recvinfo, sendinfo);
        // cout <<"-----3----"<<endl;
        user_transport->close();
        return Serialization(recvinfo);
    }
    std::string User_follow(const std::string &s){
        std::shared_ptr<TTransport> user_socket(new TSocket(USER_IP, USER_PORT));
        std::shared_ptr<TTransport> user_transport(new TBufferedTransport(user_socket));
        std::shared_ptr<TProtocol> user_protocol(new TBinaryProtocol(user_transport));
        UserClient user_client(user_protocol);
        user_transport->open();
        //反序列化
        // cout <<"-----0----"<< endl;
        // cout << s <<endl;
        RPC_DEFINE_FOR_SENDINFO(User_follow) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(User_follow)>(s);
        sendinfo = ChangeStr_decodebase64(sendinfo);
        //  cout <<"-----1---"<< endl;
        //  cout << sendinfo.info <<endl;
        RPC_DEFINE_FOR_RECVINFO(User_follow) recvinfo;
        //  cout <<"-----2---"<< endl;  
        //调用微服务
        user_client.User_follow(recvinfo, sendinfo);
        recvinfo = ChangeStr_encodebase64(recvinfo);
        // cout <<"-----3----"<<endl;
        user_transport->close();
        return Serialization(recvinfo);
    }
    std::string User_followed(const std::string &s){
        std::shared_ptr<TTransport> user_socket(new TSocket(USER_IP, USER_PORT));
        std::shared_ptr<TTransport> user_transport(new TBufferedTransport(user_socket));
        std::shared_ptr<TProtocol> user_protocol(new TBinaryProtocol(user_transport));
        UserClient user_client(user_protocol);
        user_transport->open();
        //反序列化
        // cout <<"-----0----"<< endl;
        // cout << s <<endl;
        RPC_DEFINE_FOR_SENDINFO(User_followed) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(User_followed)>(s);
        sendinfo = ChangeStr_decodebase64(sendinfo);
        //  cout <<"-----1---"<< endl;
        //  cout << sendinfo.info <<endl;
        RPC_DEFINE_FOR_RECVINFO(User_followed) recvinfo;
        //  cout <<"-----2---"<< endl;  
        //调用微服务
        user_client.User_followed(recvinfo, sendinfo);
        recvinfo = ChangeStr_encodebase64(recvinfo);
        // cout <<"-----3----"<<endl;
        user_transport->close();
        return Serialization(recvinfo);
    }
    std::string User_friend(const std::string &s){
        std::shared_ptr<TTransport> user_socket(new TSocket(USER_IP, USER_PORT));
        std::shared_ptr<TTransport> user_transport(new TBufferedTransport(user_socket));
        std::shared_ptr<TProtocol> user_protocol(new TBinaryProtocol(user_transport));
        UserClient user_client(user_protocol);
        user_transport->open();
        //反序列化
        // cout <<"-----0----"<< endl;
        // cout << s <<endl;
        RPC_DEFINE_FOR_SENDINFO(User_friend) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(User_friend)>(s);
        sendinfo = ChangeStr_decodebase64(sendinfo);
        //  cout <<"-----1---"<< endl;
        //  cout << sendinfo.info <<endl;
        RPC_DEFINE_FOR_RECVINFO(User_friend) recvinfo;
        //  cout <<"-----2---"<< endl;  
        //调用微服务
        user_client.User_friend(recvinfo, sendinfo);
        recvinfo = ChangeStr_encodebase64(recvinfo);
        // cout <<"-----3----"<<endl;
        user_transport->close();
        return Serialization(recvinfo);
    }

}
