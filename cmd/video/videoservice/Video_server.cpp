// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "Video.h"
#include <cstdint>
#include <queue>
#include <sys/types.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include "../../conf.hh"
#include <bits/stdc++.h>
#include <utility>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class VideoHandler : virtual public VideoIf {
 private:
  std::map<std::int32_t , std::string>videomp[MAX_ROOM*(MAX_USER+1)];
 public:
  VideoHandler() :videomp(){
    // Your initialization goes here
    std::cout << "[*]video服务开启"<<std::endl;
  }
  //多个video服务端的时候 应该配合redis 
  //把多个图像同时存储到同一级缓存里 达到共享
  //取的时候可以各自进行取
  void Video_Upload(Video_Upload_RecvInfo& _return, const Video_Upload_SendInfo& info) {
    //插入
    int32_t timeinfo = info.msec + info.sec*1000+ info.min*60000;
    int32_t userinfo = info.roomId*MAX_USER + info.userId;
    videomp[userinfo][timeinfo] = info.info;
    std::cout << "[↑]video 上传成功：" << "\t房间号:"<<  info.roomId << "\t用户号:" << info.userId << "\t时间:" << timeinfo <<std::endl;

    // 时间调试
    // time_t now = time(nullptr);
    // char* curr_time = ctime(&now); 
    // std::cout << curr_time <<std::endl;
    // std::cout << info.min << " " <<info.sec <<" " <<info.msec ;
    
    //删除
    if(videomp[userinfo].size() > 10000){
      auto it = videomp[userinfo].upper_bound(timeinfo);
      if(it != videomp[userinfo].end()){
        std::cout << "[-]video 删除成功：" << "\t房间号:"<<  info.roomId << "\t用户号:" << info.userId << "\t时间:" << it->first <<std::endl;
        videomp[userinfo].erase(it);
      }else{
        std::cout << "[-]video 删除成功：" << "\t房间号:"<<  info.roomId << "\t用户号:" << info.userId << "\t时间:" << it->first <<std::endl;
        videomp[userinfo].erase(videomp[userinfo].begin());
      }
    }
    
    //返回
    _return.status = VIDEO_OK;
    _return.min = info.min;
    _return.sec = info.sec;
    _return.msec = info.msec;
    _return.roomId = info.roomId;
    _return.userId = info.userId;
    _return.type = Video_Upload_RecvInfo_TypeId;
    _return.sendtime = info.sendtime;
    return;
  }

  void Video_Download(Video_Download_RecvInfo& _return, const Video_Download_SendInfo& info) {
    //下载距离当前时间最近的
    int32_t timeinfo = info.msec + info.sec*1000+ info.min*60000;
    int32_t userinfo = info.roomId*MAX_USER + info.userId;
    // std::cout << "大小" <<   videomp[userinfo].size() <<std::endl;
    // using namespace std;
    // for(const auto& it: videomp[userinfo]){
    //   cout << it.first <<endl;
    // }
    if(videomp[userinfo].size() == 0){//没有元素      
      _return.status = VIDEO_NO_PNG;
      _return.min = info.min;
      _return.sec = info.sec;
      _return.msec = info.msec;
      _return.roomId = info.roomId;
      _return.userId = info.userId;
      _return.type = Video_Download_RecvInfo_TypeId;
      _return.sendtime = info.sendtime;
      std::cout << "[↓]video 下载失败-没有元素：" << "\t房间号:"<<  info.roomId << "\t用户号:" << info.userId << "\t时间:" << timeinfo <<std::endl;
      return;
    }

    auto it = videomp[userinfo].lower_bound(timeinfo);
    if(it == videomp[userinfo].begin()){//如果是最开始的
      it = videomp[userinfo].end();
    }
    it--;
    std::cout << "[↓]video 下载成功：" << "\t房间号:"<<  info.roomId << "\t用户号:" << info.userId << "\t时间:" << it->first <<std::endl;
    _return.status = VIDEO_OK;
    _return.min = (it->first)/1000/60;
    _return.sec = (it->first)/1000%60;
    _return.msec = (it->first)%1000;
    _return.roomId = info.roomId;
    _return.userId = info.userId;
    _return.type = Video_Download_RecvInfo_TypeId; 
    _return.info = it->second;
    _return.sendtime = info.sendtime;
    return;
  }
  
  void Video_Clean(const Video_Clean_SendInfo& info) {
    int32_t userinfo = info.roomId*MAX_USER + info.userId;
    videomp[userinfo].clear();
    return;
  }

};

int main(int argc, char **argv) {
  int port = VIDEO_PORT;
  ::std::shared_ptr<VideoHandler> handler(new VideoHandler());
  ::std::shared_ptr<TProcessor> processor(new VideoProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

