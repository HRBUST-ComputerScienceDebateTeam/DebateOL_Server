// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.
#include <time.h>
#include <iostream>
#include "Echo.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class EchoHandler : virtual public EchoIf {
 public:
  EchoHandler() {
    // Your initialization goes here
  }
  std::string gettime(){
    time_t timep;
    time(&timep);
    std::string rets = ctime(&timep);
    return rets;
  }
  

  void Echo_Send(Echo_RecvInfo& _return, const Echo_SendInfo& info) {
    std::string now = gettime();
    std::cout <<"Echo_Send - " << now << std::endl; 
    _return.id = info.id;
    _return.info = info.info;
    _return.time = now;
  }

};

int main(int argc, char **argv) {
  int port = 9001;
  ::std::shared_ptr<EchoHandler> handler(new EchoHandler());
  ::std::shared_ptr<TProcessor> processor(new EchoProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

