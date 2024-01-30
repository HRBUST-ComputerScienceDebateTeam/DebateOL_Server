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
// audio upload
std::string AudioUpload( const std::string& s ) {
    std::shared_ptr< TTransport > audio_socket( new TSocket( AUDIO_IP, AUDIO_PORT ) );
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
    std::shared_ptr< TTransport > audio_socket( new TSocket( AUDIO_IP, AUDIO_PORT ) );
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
    std::shared_ptr< TTransport > audio_socket( new TSocket( AUDIO_IP, AUDIO_PORT ) );
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
