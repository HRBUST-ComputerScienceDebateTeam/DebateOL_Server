#include <iostream>
#include <random>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "./echoservice/Echo.h"
#include "../conf.hh"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;


int main() {
  std::shared_ptr<TTransport> socket(new TSocket(ECHO_IP, ECHO_PORT));
  std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  EchoClient client(protocol);

  try {
    transport->open();

    srand(time(0));
    Echo_SendInfo sendinfo;
    sendinfo.id = rand()%100;
    sendinfo.info = "你好 _ hello server";

    Echo_RecvInfo recvinfo;
    client.Echo_Send(recvinfo, sendinfo);
    cout <<"现在服务器时间: " << recvinfo.time <<endl;
    cout <<recvinfo.id <<" " << recvinfo.info <<endl;

    transport->close();
  } catch (TException& tx) {
    cout << "ERROR: " << tx.what() << endl;
  }
}