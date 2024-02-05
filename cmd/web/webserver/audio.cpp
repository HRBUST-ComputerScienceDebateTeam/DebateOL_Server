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
// audio upload

std::string AudioUpload( const std::string& s ) {
    string ip;
    int    post;

    list< pair< string, string > > ret = down_server_info( AUDIO_NAME );
    if ( ret.size() == 0 ) {
        cout << "没有发现服务" << endl;
        return "";
    } else {
        cout << "发现服务" << endl;
        ip   = ret.front().first;
        post = stoi( ret.front().second );
    }

    std::shared_ptr< TTransport > audio_socket( new TSocket( ip, post ) );
    std::shared_ptr< TTransport > audio_transport( new TBufferedTransport( audio_socket ) );
    std::shared_ptr< TProtocol >  audio_protocol( new TBinaryProtocol( audio_transport ) );
    AudioClient                   audio_client( audio_protocol );
    audio_transport->open();
    //反序列化
    // cout <<"-----0----"<< endl;
    // cout << s <<endl;
    Audio_Upload_SendInfo sendinfo = Deserialization< Audio_Upload_SendInfo >( s );
    //  cout <<"-----1---"<< endl;
    //  cout << sendinfo.info <<endl;
    Audio_Upload_RecvInfo recvinfo;
    //  cout <<"-----2---"<< endl;
    //调用微服务
    audio_client.Audio_Upload( recvinfo, sendinfo );
    // cout <<"-----3----"<<endl;
    audio_transport->close();
    return Serialization( recvinfo );
};

// audio download
// type - room - user - min - sec - msec - sendtime;
std::string AudioDownload( const std::string& s ) {
    string ip;
    int    post;

    list< pair< string, string > > ret = down_server_info( AUDIO_NAME );
    if ( ret.size() == 0 ) {
        cout << "没有发现服务" << endl;
        return "";
    } else {
        cout << "发现服务" << endl;
        ip   = ret.front().first;
        post = stoi( ret.front().second );
    }

    std::shared_ptr< TTransport > audio_socket( new TSocket( ip, post ) );
    std::shared_ptr< TTransport > audio_transport( new TBufferedTransport( audio_socket ) );
    std::shared_ptr< TProtocol >  audio_protocol( new TBinaryProtocol( audio_transport ) );
    AudioClient                   audio_client( audio_protocol );
    audio_transport->open();
    //反序列化
    // cout <<"-----0----"<< endl;
    // cout << s <<endl;
    Audio_Download_SendInfo sendinfo = Deserialization< Audio_Download_SendInfo >( s );
    //  cout <<"-----1---"<< endl;
    //  cout << sendinfo.info <<endl;
    Audio_Download_RecvInfo recvinfo;
    //  cout <<"-----2---"<< endl;
    //调用微服务
    audio_client.Audio_Download( recvinfo, sendinfo );
    // cout <<"-----3----"<<endl;
    audio_transport->close();
    return Serialization( recvinfo );
};

void AudioClean( const std::string& s ) {
    string ip;
    int    post;

    list< pair< string, string > > ret = down_server_info( AUDIO_NAME );
    if ( ret.size() == 0 ) {
        cout << "没有发现服务" << endl;
        return;
    } else {
        cout << "发现服务" << endl;
        ip   = ret.front().first;
        post = stoi( ret.front().second );
    }

    std::shared_ptr< TTransport > audio_socket( new TSocket( ip, post ) );
    std::shared_ptr< TTransport > audio_transport( new TBufferedTransport( audio_socket ) );
    std::shared_ptr< TProtocol >  audio_protocol( new TBinaryProtocol( audio_transport ) );
    AudioClient                   audio_client( audio_protocol );
    audio_transport->open();
    //反序列化
    // cout <<"-----0----"<< endl;
    // cout << s <<endl;
    Audio_Clean_SendInfo sendinfo = Deserialization< Audio_Clean_SendInfo >( s );
    //调用微服务
    audio_client.Audio_Clean( sendinfo );
    // cout << recvinfo.time <<endl;
    audio_transport->close();
};

}  // namespace rpc
