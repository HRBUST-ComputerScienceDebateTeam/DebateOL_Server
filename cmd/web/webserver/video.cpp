//本质上是微服务的客户端
#include "../../conf.hh"
#include "../json.hh"
#include "../rpc.hh"
#include <cstdio>
#include <iostream>
#include <random>
#include <string>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

namespace rpc {
// video upload
std::string VideoUpload( const std::string& s ) {
    std::shared_ptr< TTransport > video_socket( new TSocket( VIDEO_IP, VIDEO_PORT ) );
    std::shared_ptr< TTransport > video_transport( new TBufferedTransport( video_socket ) );
    std::shared_ptr< TProtocol >  video_protocol( new TBinaryProtocol( video_transport ) );
    VideoClient                   video_client( video_protocol );
    video_transport->open();
    //反序列化
    // cout <<"-----0----"<< endl;
    // cout << s <<endl;
    Video_Upload_SendInfo sendinfo = Deserialization< Video_Upload_SendInfo >( s );
    //  cout <<"-----1---"<< endl;
    //  cout << sendinfo.info <<endl;
    Video_Upload_RecvInfo recvinfo;
    //  cout <<"-----2---"<< endl;
    //调用微服务
    video_client.Video_Upload( recvinfo, sendinfo );
    // cout <<"-----3----"<<endl;
    video_transport->close();
    return Serialization( recvinfo );
};

// video download
// type - room - user - min - sec - msec - sendtime;
std::string VideoDownload( const std::string& s ) {
    std::shared_ptr< TTransport > video_socket( new TSocket( VIDEO_IP, VIDEO_PORT ) );
    std::shared_ptr< TTransport > video_transport( new TBufferedTransport( video_socket ) );
    std::shared_ptr< TProtocol >  video_protocol( new TBinaryProtocol( video_transport ) );
    VideoClient                   video_client( video_protocol );
    video_transport->open();
    //反序列化
    // cout <<"-----0----"<< endl;
    // cout << s <<endl;
    Video_Download_SendInfo sendinfo = Deserialization< Video_Download_SendInfo >( s );
    //  cout <<"-----1---"<< endl;
    //  cout << sendinfo.info <<endl;
    Video_Download_RecvInfo recvinfo;
    //  cout <<"-----2---"<< endl;
    //调用微服务
    video_client.Video_Download( recvinfo, sendinfo );
    // cout <<"-----3----"<<endl;
    video_transport->close();
    return Serialization( recvinfo );
};

void VideoClean( const std::string& s ) {
    std::shared_ptr< TTransport > video_socket( new TSocket( VIDEO_IP, VIDEO_PORT ) );
    std::shared_ptr< TTransport > video_transport( new TBufferedTransport( video_socket ) );
    std::shared_ptr< TProtocol >  video_protocol( new TBinaryProtocol( video_transport ) );
    VideoClient                   video_client( video_protocol );
    video_transport->open();
    //反序列化
    // cout <<"-----0----"<< endl;
    // cout << s <<endl;
    Video_Clean_SendInfo sendinfo = Deserialization< Video_Clean_SendInfo >( s );
    //调用微服务
    video_client.Video_Clean( sendinfo );
    // cout << recvinfo.time <<endl;
    video_transport->close();
};

}  // namespace rpc
