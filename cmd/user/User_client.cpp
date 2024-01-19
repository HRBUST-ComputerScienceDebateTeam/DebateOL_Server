#include <iostream>
#include <random>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "./userservice/User.h"
#include "../conf.hh"
#include "./userservice/user_types.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;


int main() {
  std::shared_ptr<TTransport> socket(new TSocket(USER_IP, USER_PORT));
  std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  UserClient client(protocol);

  try {
    transport->open();
    //
 
    transport->close();
  } catch (TException& tx) {
    cout << "ERROR: " << tx.what() << endl;
  }
}