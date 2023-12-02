#include <iostream>
#include <random>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "./audioservice/Audio.h"
#include "../conf.hh"
#include "./audioservice/audio_types.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;


int main() {
  std::shared_ptr<TTransport> socket(new TSocket(AUDIO_IP, AUDIO_POST));
  std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  AudioClient client(protocol);

  try {
    transport->open();

    srand(time(0));
    Audio_Upload_SendInfo upload_sendinfo;
    upload_sendinfo.type = 1;
    upload_sendinfo.userId = 11;
    upload_sendinfo.roomId = 101;
    upload_sendinfo.min = 1 ;
    upload_sendinfo.sec = 1;
    upload_sendinfo.msec = 1;
    upload_sendinfo.info = "hello! uploading.. ImAudio";
    

    Audio_Upload_RecvInfo upload_recvinfo;
    client.Audio_Upload(upload_recvinfo, upload_sendinfo);
    
    cout << "upload_recvinfo.status" << upload_recvinfo.status << endl;
    cout << "upload_recvinfo.type  " << upload_recvinfo.type << endl;
    cout << "upload_recvinfo.userId" << upload_recvinfo.userId << endl;
    cout << "upload_recvinfo.roomId" << upload_recvinfo.roomId << endl;
    cout << "upload_recvinfo.min   " << upload_recvinfo.min << endl;
    cout << "upload_recvinfo.sec   " << upload_recvinfo.sec << endl;
    cout << "upload_recvinfo.msec  " << upload_recvinfo.msec << endl;
 
    transport->close();
  } catch (TException& tx) {
    cout << "ERROR: " << tx.what() << endl;
  }
}