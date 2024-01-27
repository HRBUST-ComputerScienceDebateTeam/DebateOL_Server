// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "../../conf.hh"
#include "Audio.h"
#include <bits/stdc++.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class AudioHandler : virtual public AudioIf {
private:
    std::map< std::int32_t, std::string > audiomp[ MAX_ROOM * ( MAX_USER + 1 ) ];

public:
    AudioHandler() : audiomp() {
        // Your initialization goes here
        std::cout << "[*]audio服务开启" << std::endl;
    }
    //多个audio服务端的时候 应该配合redis
    //把多个图像同时存储到同一级缓存里 达到共享
    //取的时候可以各自进行取
    void Audio_Upload( Audio_Upload_RecvInfo& _return, const Audio_Upload_SendInfo& info ) {
        //插入
        int32_t timeinfo                = info.msec + info.sec * 1000 + info.min * 60000;
        int32_t userinfo                = info.roomId * MAX_USER + info.userId;
        audiomp[ userinfo ][ timeinfo ] = info.info;
        std::cout << "audio 上传成功："
                  << "\n\t房间号:" << info.roomId << "\n\t用户号:" << info.userId << "\n\t时间:" << timeinfo << std::endl;

        //删除
        if ( audiomp[ userinfo ].size() > 10000 ) {
            auto it = audiomp[ userinfo ].upper_bound( timeinfo );
            if ( it != audiomp[ userinfo ].end() ) {
                std::cout << "audio 删除成功："
                          << "\n\t房间号:" << info.roomId << "\n\t用户号:" << info.userId << "\n\t时间:" << it->first << std::endl;
                audiomp[ userinfo ].erase( it );
            } else {
                std::cout << "audio 删除成功："
                          << "\n\t房间号:" << info.roomId << "\n\t用户号:" << info.userId << "\n\t时间:" << it->first << std::endl;
                audiomp[ userinfo ].erase( audiomp[ userinfo ].begin() );
            }
        }

        //返回
        _return.status   = AUDIO_OK;
        _return.min      = info.min;
        _return.sec      = info.sec;
        _return.msec     = info.msec;
        _return.roomId   = info.roomId;
        _return.userId   = info.userId;
        _return.type     = Audio_Upload_RecvInfo_TypeId;
        _return.sendtime = timeinfo;
        return;
    }

    void Audio_Download( Audio_Download_RecvInfo& _return, const Audio_Download_SendInfo& info ) {
        //下载距离当前时间最近的
        int32_t timeinfo = info.msec + info.sec * 1000 + info.min * 60000;
        int32_t userinfo = info.roomId * MAX_USER + info.userId;
        // std::cout << "大小" <<   audiomp[userinfo].size() <<std::endl;
        // using namespace std;
        // for(const auto& it: audiomp[userinfo]){
        //   cout << it.first <<endl;
        // }
        if ( audiomp[ userinfo ].size() == 0 ) {  //没有元素
            _return.status   = AUDIO_NO_INFO;
            _return.min      = info.min;
            _return.sec      = info.sec;
            _return.msec     = info.msec;
            _return.roomId   = info.roomId;
            _return.userId   = info.userId;
            _return.type     = Audio_Download_RecvInfo_TypeId;
            _return.sendtime = timeinfo;
            std::cout << "audio 下载失败-没有元素："
                      << "\n房间号:" << info.roomId << "\n用户号:" << info.userId << "\n时间:" << timeinfo << std::endl;
            return;
        }

        auto it = audiomp[ userinfo ].lower_bound( timeinfo );
        if ( it == audiomp[ userinfo ].begin() ) {  //如果是最开始的
            it = audiomp[ userinfo ].end();
        }
        it--;
        std::cout << "audio 下载成功："
                  << "\n房间号:" << info.roomId << "\n用户号:" << info.userId << "\n时间:" << it->first << std::endl;
        _return.status   = AUDIO_OK;
        _return.min      = ( it->first ) / 1000 / 60;
        _return.sec      = ( it->first ) / 1000 % 60;
        _return.msec     = ( it->first ) % 1000;
        _return.roomId   = info.roomId;
        _return.userId   = info.userId;
        _return.type     = Audio_Download_RecvInfo_TypeId;
        _return.info     = it->second;
        _return.sendtime = timeinfo;
        // printf("Audio_Download\n");
        return;
    }

    void Audio_Clean( const Audio_Clean_SendInfo& info ) {
        int32_t userinfo = info.roomId * MAX_USER + info.userId;
        audiomp[ userinfo ].clear();
        return;
    }
};

int main( int argc, char** argv ) {
    ::std::shared_ptr< AudioHandler >      handler( new AudioHandler() );
    ::std::shared_ptr< TProcessor >        processor( new AudioProcessor( handler ) );
    ::std::shared_ptr< TServerTransport >  serverTransport( new TServerSocket( AUDIO_PORT ) );
    ::std::shared_ptr< TTransportFactory > transportFactory( new TBufferedTransportFactory() );
    ::std::shared_ptr< TProtocolFactory >  protocolFactory( new TBinaryProtocolFactory() );

    TSimpleServer server( processor, serverTransport, transportFactory, protocolFactory );
    server.serve();
    return 0;
}
