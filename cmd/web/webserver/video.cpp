//本质上是微服务的客户端
#include "../../../pkg/Sidecar/sidecar.h"
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
    string ip;
    int    post;

    list< pair< string, string > > ret = down_server_info( VIDEO_NAME );
    if ( ret.size() == 0 ) {
        cout << "没有发现服务" << endl;
        return "";
    } else {
        cout << "发现服务" << endl;
        ip   = ret.front().first;
        post = stoi( ret.front().second );
    }

    std::shared_ptr< TTransport > video_socket( new TSocket( ip, post ) );
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
    string ip;
    int    post;

    list< pair< string, string > > ret = down_server_info( VIDEO_NAME );
    if ( ret.size() == 0 ) {
        cout << "没有发现服务" << endl;
        return "";
    } else {
        cout << "发现服务" << endl;
        ip   = ret.front().first;
        post = stoi( ret.front().second );
    }

    std::shared_ptr< TTransport > video_socket( new TSocket( ip, post ) );
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
    string ip;
    int    post;

    list< pair< string, string > > ret = down_server_info( VIDEO_NAME );
    if ( ret.size() == 0 ) {
        cout << "没有发现服务" << endl;
        return;
    } else {
        cout << "发现服务" << endl;
        ip   = ret.front().first;
        post = stoi( ret.front().second );
    }

    std::shared_ptr< TTransport > video_socket( new TSocket( ip, post ) );
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
