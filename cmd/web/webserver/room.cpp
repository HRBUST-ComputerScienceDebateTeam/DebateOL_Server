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


#define RPC_DEFINE_FOR_SENDINFO(x) x##_SendInfo
#define RPC_DEFINE_FOR_RECVINFO(x) x##_RecvInfo

namespace rpc{
std::string Room_ChangeDebatePos(const std::string &s ){
    std::shared_ptr<TTransport> room_socket(new TSocket(ROOM_IP, ROOM_PORT));
    std::shared_ptr<TTransport> room_transport(new TBufferedTransport(room_socket));
    std::shared_ptr<TProtocol> room_protocol(new TBinaryProtocol(room_transport));
    RoomClient room_client(room_protocol);
    room_transport->open();
    //反序列化
    // cout <<"-----0----"<< endl;
    // cout << s <<endl;
    RPC_DEFINE_FOR_SENDINFO(Room_ChangeDebatePos) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(Room_ChangeDebatePos)>(s);
    //  cout <<"-----1---"<< endl;
    //  cout << sendinfo.info <<endl;
    RPC_DEFINE_FOR_RECVINFO(Room_ChangeDebatePos) recvinfo;
    //  cout <<"-----2---"<< endl;  
    //调用微服务
    room_client.Room_ChangeDebatePos(recvinfo, sendinfo);
    // cout <<"-----3----"<<endl;
    room_transport->close();
    return Serialization(recvinfo);
}
std::string Room_ChangeExtraInfo(const std::string &s ){
    std::shared_ptr<TTransport> room_socket(new TSocket(ROOM_IP, ROOM_PORT));
    std::shared_ptr<TTransport> room_transport(new TBufferedTransport(room_socket));
    std::shared_ptr<TProtocol> room_protocol(new TBinaryProtocol(room_transport));
    RoomClient room_client(room_protocol);
    room_transport->open();
    //反序列化
    // cout <<"-----0----"<< endl;
    // cout << s <<endl;
    RPC_DEFINE_FOR_SENDINFO(Room_ChangeExtraInfo) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(Room_ChangeExtraInfo)>(s);
    //  cout <<"-----1---"<< endl;
    //  cout << sendinfo.info <<endl;
    RPC_DEFINE_FOR_RECVINFO(Room_ChangeExtraInfo) recvinfo;
    //  cout <<"-----2---"<< endl;  
    //调用微服务
    room_client.Room_ChangeExtraInfo(recvinfo, sendinfo);
    // cout <<"-----3----"<<endl;
    room_transport->close();
    return Serialization(recvinfo);
}
std::string Room_ChangePasswd(const std::string &s ){
    std::shared_ptr<TTransport> room_socket(new TSocket(ROOM_IP, ROOM_PORT));
    std::shared_ptr<TTransport> room_transport(new TBufferedTransport(room_socket));
    std::shared_ptr<TProtocol> room_protocol(new TBinaryProtocol(room_transport));
    RoomClient room_client(room_protocol);
    room_transport->open();
    //反序列化
    // cout <<"-----0----"<< endl;
    // cout << s <<endl;
    RPC_DEFINE_FOR_SENDINFO(Room_ChangePasswd) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(Room_ChangePasswd)>(s);
    //  cout <<"-----1---"<< endl;
    //  cout << sendinfo.info <<endl;
    RPC_DEFINE_FOR_RECVINFO(Room_ChangePasswd) recvinfo;
    //  cout <<"-----2---"<< endl;  
    //调用微服务
    room_client.Room_ChangePasswd(recvinfo, sendinfo);
    // cout <<"-----3----"<<endl;
    room_transport->close();
    return Serialization(recvinfo);
}
std::string Room_Exitroom(const std::string &s ){
    std::shared_ptr<TTransport> room_socket(new TSocket(ROOM_IP, ROOM_PORT));
    std::shared_ptr<TTransport> room_transport(new TBufferedTransport(room_socket));
    std::shared_ptr<TProtocol> room_protocol(new TBinaryProtocol(room_transport));
    RoomClient room_client(room_protocol);
    room_transport->open();
    //反序列化
    // cout <<"-----0----"<< endl;
    // cout << s <<endl;
    RPC_DEFINE_FOR_SENDINFO(Room_Exitroom) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(Room_Exitroom)>(s);
    //  cout <<"-----1---"<< endl;
    //  cout << sendinfo.info <<endl;
    RPC_DEFINE_FOR_RECVINFO(Room_Exitroom) recvinfo;
    //  cout <<"-----2---"<< endl;  
    //调用微服务
    room_client.Room_Exitroom(recvinfo, sendinfo);
    // cout <<"-----3----"<<endl;
    room_transport->close();
    return Serialization(recvinfo);
}
std::string Room_Joinroom(const std::string &s ){
    std::shared_ptr<TTransport> room_socket(new TSocket(ROOM_IP, ROOM_PORT));
    std::shared_ptr<TTransport> room_transport(new TBufferedTransport(room_socket));
    std::shared_ptr<TProtocol> room_protocol(new TBinaryProtocol(room_transport));
    RoomClient room_client(room_protocol);
    room_transport->open();
    //反序列化
    // cout <<"-----0----"<< endl;
    // cout << s <<endl;
    RPC_DEFINE_FOR_SENDINFO(Room_Exitroom) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(Room_Exitroom)>(s);
    //  cout <<"-----1---"<< endl;
    //  cout << sendinfo.info <<endl;
    RPC_DEFINE_FOR_RECVINFO(Room_Exitroom) recvinfo;
    //  cout <<"-----2---"<< endl;  
    //调用微服务
    room_client.Room_Exitroom(recvinfo, sendinfo);
    // cout <<"-----3----"<<endl;
    room_transport->close();
    return Serialization(recvinfo);
}
std::string Room_Create(const std::string &s ){
    std::shared_ptr<TTransport> room_socket(new TSocket(ROOM_IP, ROOM_PORT));
    std::shared_ptr<TTransport> room_transport(new TBufferedTransport(room_socket));
    std::shared_ptr<TProtocol> room_protocol(new TBinaryProtocol(room_transport));
    RoomClient room_client(room_protocol);
    room_transport->open();
    //反序列化
    // cout <<"-----0----"<< endl;
    // cout << s <<endl;
    RPC_DEFINE_FOR_SENDINFO(Room_Create) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(Room_Create)>(s);
    //  cout <<"-----1---"<< endl;
    //  cout << sendinfo.info <<endl;
    RPC_DEFINE_FOR_RECVINFO(Room_Create) recvinfo;
    //  cout <<"-----2---"<< endl;  
    //调用微服务
    room_client.Room_Create(recvinfo, sendinfo);
    // cout <<"-----3----"<<endl;
    room_transport->close();
    return Serialization(recvinfo);
}
std::string Room_GetURrelation(const std::string &s ){
    std::shared_ptr<TTransport> room_socket(new TSocket(ROOM_IP, ROOM_PORT));
    std::shared_ptr<TTransport> room_transport(new TBufferedTransport(room_socket));
    std::shared_ptr<TProtocol> room_protocol(new TBinaryProtocol(room_transport));
    RoomClient room_client(room_protocol);
    room_transport->open();
    //反序列化
    // cout <<"-----0----"<< endl;
    // cout << s <<endl;
    RPC_DEFINE_FOR_SENDINFO(Room_GetURrelation) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(Room_GetURrelation)>(s);
    //  cout <<"-----1---"<< endl;
    //  cout << sendinfo.info <<endl;
    RPC_DEFINE_FOR_RECVINFO(Room_GetURrelation) recvinfo;
    //  cout <<"-----2---"<< endl;  
    //调用微服务
    room_client.Room_GetURrelation(recvinfo, sendinfo);
    // cout <<"-----3----"<<endl;
    room_transport->close();
    return Serialization(recvinfo);
}
std::string Room_GetExInfo(const std::string &s ){
    std::shared_ptr<TTransport> room_socket(new TSocket(ROOM_IP, ROOM_PORT));
    std::shared_ptr<TTransport> room_transport(new TBufferedTransport(room_socket));
    std::shared_ptr<TProtocol> room_protocol(new TBinaryProtocol(room_transport));
    RoomClient room_client(room_protocol);
    room_transport->open();
    //反序列化
    // cout <<"-----0----"<< endl;
    // cout << s <<endl;
    RPC_DEFINE_FOR_SENDINFO(Room_GetExInfo) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(Room_GetExInfo)>(s);
    //  cout <<"-----1---"<< endl;
    //  cout << sendinfo.info <<endl;
    RPC_DEFINE_FOR_RECVINFO(Room_GetExInfo) recvinfo;
    //  cout <<"-----2---"<< endl;  
    //调用微服务
    room_client.Room_GetExInfo(recvinfo, sendinfo);
    // cout <<"-----3----"<<endl;
    room_transport->close();
    return Serialization(recvinfo);
}
std::string Room_GetBaseInfo(const std::string &s ){
    std::shared_ptr<TTransport> room_socket(new TSocket(ROOM_IP, ROOM_PORT));
    std::shared_ptr<TTransport> room_transport(new TBufferedTransport(room_socket));
    std::shared_ptr<TProtocol> room_protocol(new TBinaryProtocol(room_transport));
    RoomClient room_client(room_protocol);
    room_transport->open();
    //反序列化
    // cout <<"-----0----"<< endl;
    // cout << s <<endl;
    RPC_DEFINE_FOR_SENDINFO(Room_GetBaseInfo) sendinfo = Deserialization<RPC_DEFINE_FOR_SENDINFO(Room_GetBaseInfo)>(s);
    //  cout <<"-----1---"<< endl;
    //  cout << sendinfo.info <<endl;
    RPC_DEFINE_FOR_RECVINFO(Room_GetBaseInfo) recvinfo;
    //  cout <<"-----2---"<< endl;  
    //调用微服务
    room_client.Room_GetBaseInfo(recvinfo, sendinfo);
    // cout <<"-----3----"<<endl;
    room_transport->close();
    return Serialization(recvinfo);
}

}
