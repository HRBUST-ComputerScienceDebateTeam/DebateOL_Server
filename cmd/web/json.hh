#pragma once
#include "./rpc.hh"
#include <iostream>
#include <random>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

// json.h 中包含序列化反序列化工具

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

template < typename ThriftStruct > std::string ThriftToString( const ThriftStruct& ts ) {
    using namespace apache::thrift::transport;  // NOLINT
    using namespace apache::thrift::protocol;   // NOLINT

    TMemoryBuffer*                buffer = new TMemoryBuffer();
    std::shared_ptr< TTransport > trans( buffer );

    TJSONProtocol protocol( trans );
    ts.write( &protocol );

    uint8_t* buf;
    uint32_t size;
    buffer->getBuffer( &buf, &size );
    return std::string( ( char* )buf, ( unsigned int )size );  // NOLINT
}

//反序列化
template < typename ThriftStruct > bool StringToThrift( const std::string& buff, ThriftStruct* ts ) {
    // using namespace apache::thrift::transport;  // NOLINT
    // using namespace apache::thrift::protocol;  // NOLINT
    TMemoryBuffer* buffer = new TMemoryBuffer;
    buffer->write( ( const uint8_t* )buff.data(), buff.size() );
    std::shared_ptr< TTransport > trans( buffer );
    TJSONProtocol                 protocol( trans );
    ts->read( &protocol );
    return true;
}

// 序列化
template < typename ThriftStruct > std::string Serialization( const ThriftStruct& ts ) {
    uint8_t*                         buf_ptr;
    uint32_t                         sz;
    std::shared_ptr< TMemoryBuffer > mem_buf( new TMemoryBuffer );
    std::shared_ptr< TJSONProtocol > bin_proto( new TJSONProtocol( mem_buf ) );
    ts.write( bin_proto.get() );
    mem_buf->getBuffer( &buf_ptr, &sz );
    return ThriftToString< ThriftStruct >( ts );
}

// 反序列化
template < typename ThriftStruct > ThriftStruct Deserialization( const string& s ) {
    ThriftStruct TS_ret;
    StringToThrift< ThriftStruct >( s, &TS_ret );
    return TS_ret;
}

template std::string   Serialization( const Echo_RecvInfo& );
template Echo_SendInfo Deserialization( const std::string& );
