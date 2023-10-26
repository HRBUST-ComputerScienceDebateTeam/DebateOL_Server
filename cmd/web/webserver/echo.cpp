//本质上是微服务的客户端
#include <iostream>
#include <random>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include "../conf.hh"
#include "../rpc.hh"
#include "../json.hh"


using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;


namespace rpc{
    std::shared_ptr<TTransport> echo_socket(new TSocket(ECHO_IP, ECHO_POST));
    std::shared_ptr<TTransport> echo_transport(new TBufferedTransport(echo_socket));
    std::shared_ptr<TProtocol> echo_protocol(new TBinaryProtocol(echo_transport));
    EchoClient echo_client(echo_protocol);
    std::string  Del_echo(const std::string &s ){
        echo_transport->open();
        //反序列化
        Echo_SendInfo sendinfo = Deserialization<Echo_SendInfo>(s);
        
        Echo_RecvInfo recvinfo;
        echo_client.Echo_Send(recvinfo, sendinfo);
        echo_transport->close();
        return Serialization(recvinfo);
    };
}

