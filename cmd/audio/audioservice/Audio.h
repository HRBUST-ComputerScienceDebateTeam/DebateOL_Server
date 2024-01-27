/**
 * Autogenerated by Thrift Compiler (0.19.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Audio_H
#define Audio_H

#include "audio_types.h"
#include <memory>
#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4250 )  // inheriting methods via dominance
#endif

class AudioIf {
public:
    virtual ~AudioIf() {}
    virtual void Audio_Upload( Audio_Upload_RecvInfo& _return, const Audio_Upload_SendInfo& info )       = 0;
    virtual void Audio_Download( Audio_Download_RecvInfo& _return, const Audio_Download_SendInfo& info ) = 0;
    virtual void Audio_Clean( const Audio_Clean_SendInfo& info )                                         = 0;
};

class AudioIfFactory {
public:
    typedef AudioIf Handler;

    virtual ~AudioIfFactory() {}

    virtual AudioIf* getHandler( const ::apache::thrift::TConnectionInfo& connInfo ) = 0;
    virtual void     releaseHandler( AudioIf* /* handler */ )                        = 0;
};

class AudioIfSingletonFactory : virtual public AudioIfFactory {
public:
    AudioIfSingletonFactory( const ::std::shared_ptr< AudioIf >& iface ) : iface_( iface ) {}
    virtual ~AudioIfSingletonFactory() {}

    virtual AudioIf* getHandler( const ::apache::thrift::TConnectionInfo& ) override {
        return iface_.get();
    }
    virtual void releaseHandler( AudioIf* /* handler */ ) override {}

protected:
    ::std::shared_ptr< AudioIf > iface_;
};

class AudioNull : virtual public AudioIf {
public:
    virtual ~AudioNull() {}
    void Audio_Upload( Audio_Upload_RecvInfo& /* _return */, const Audio_Upload_SendInfo& /* info */ ) override {
        return;
    }
    void Audio_Download( Audio_Download_RecvInfo& /* _return */, const Audio_Download_SendInfo& /* info */ ) override {
        return;
    }
    void Audio_Clean( const Audio_Clean_SendInfo& /* info */ ) override {
        return;
    }
};

typedef struct _Audio_Audio_Upload_args__isset {
    _Audio_Audio_Upload_args__isset() : info( false ) {}
    bool info : 1;
} _Audio_Audio_Upload_args__isset;

class Audio_Audio_Upload_args {
public:
    Audio_Audio_Upload_args( const Audio_Audio_Upload_args& );
    Audio_Audio_Upload_args& operator=( const Audio_Audio_Upload_args& );
    Audio_Audio_Upload_args() noexcept {}

    virtual ~Audio_Audio_Upload_args() noexcept;
    Audio_Upload_SendInfo info;

    _Audio_Audio_Upload_args__isset __isset;

    void __set_info( const Audio_Upload_SendInfo& val );

    bool operator==( const Audio_Audio_Upload_args& rhs ) const {
        if ( !( info == rhs.info ) )
            return false;
        return true;
    }
    bool operator!=( const Audio_Audio_Upload_args& rhs ) const {
        return !( *this == rhs );
    }

    bool operator<( const Audio_Audio_Upload_args& ) const;

    uint32_t read( ::apache::thrift::protocol::TProtocol* iprot );
    uint32_t write( ::apache::thrift::protocol::TProtocol* oprot ) const;
};

class Audio_Audio_Upload_pargs {
public:
    virtual ~Audio_Audio_Upload_pargs() noexcept;
    const Audio_Upload_SendInfo* info;

    uint32_t write( ::apache::thrift::protocol::TProtocol* oprot ) const;
};

typedef struct _Audio_Audio_Upload_result__isset {
    _Audio_Audio_Upload_result__isset() : success( false ) {}
    bool success : 1;
} _Audio_Audio_Upload_result__isset;

class Audio_Audio_Upload_result {
public:
    Audio_Audio_Upload_result( const Audio_Audio_Upload_result& ) noexcept;
    Audio_Audio_Upload_result& operator=( const Audio_Audio_Upload_result& ) noexcept;
    Audio_Audio_Upload_result() noexcept {}

    virtual ~Audio_Audio_Upload_result() noexcept;
    Audio_Upload_RecvInfo success;

    _Audio_Audio_Upload_result__isset __isset;

    void __set_success( const Audio_Upload_RecvInfo& val );

    bool operator==( const Audio_Audio_Upload_result& rhs ) const {
        if ( !( success == rhs.success ) )
            return false;
        return true;
    }
    bool operator!=( const Audio_Audio_Upload_result& rhs ) const {
        return !( *this == rhs );
    }

    bool operator<( const Audio_Audio_Upload_result& ) const;

    uint32_t read( ::apache::thrift::protocol::TProtocol* iprot );
    uint32_t write( ::apache::thrift::protocol::TProtocol* oprot ) const;
};

typedef struct _Audio_Audio_Upload_presult__isset {
    _Audio_Audio_Upload_presult__isset() : success( false ) {}
    bool success : 1;
} _Audio_Audio_Upload_presult__isset;

class Audio_Audio_Upload_presult {
public:
    virtual ~Audio_Audio_Upload_presult() noexcept;
    Audio_Upload_RecvInfo* success;

    _Audio_Audio_Upload_presult__isset __isset;

    uint32_t read( ::apache::thrift::protocol::TProtocol* iprot );
};

typedef struct _Audio_Audio_Download_args__isset {
    _Audio_Audio_Download_args__isset() : info( false ) {}
    bool info : 1;
} _Audio_Audio_Download_args__isset;

class Audio_Audio_Download_args {
public:
    Audio_Audio_Download_args( const Audio_Audio_Download_args& ) noexcept;
    Audio_Audio_Download_args& operator=( const Audio_Audio_Download_args& ) noexcept;
    Audio_Audio_Download_args() noexcept {}

    virtual ~Audio_Audio_Download_args() noexcept;
    Audio_Download_SendInfo info;

    _Audio_Audio_Download_args__isset __isset;

    void __set_info( const Audio_Download_SendInfo& val );

    bool operator==( const Audio_Audio_Download_args& rhs ) const {
        if ( !( info == rhs.info ) )
            return false;
        return true;
    }
    bool operator!=( const Audio_Audio_Download_args& rhs ) const {
        return !( *this == rhs );
    }

    bool operator<( const Audio_Audio_Download_args& ) const;

    uint32_t read( ::apache::thrift::protocol::TProtocol* iprot );
    uint32_t write( ::apache::thrift::protocol::TProtocol* oprot ) const;
};

class Audio_Audio_Download_pargs {
public:
    virtual ~Audio_Audio_Download_pargs() noexcept;
    const Audio_Download_SendInfo* info;

    uint32_t write( ::apache::thrift::protocol::TProtocol* oprot ) const;
};

typedef struct _Audio_Audio_Download_result__isset {
    _Audio_Audio_Download_result__isset() : success( false ) {}
    bool success : 1;
} _Audio_Audio_Download_result__isset;

class Audio_Audio_Download_result {
public:
    Audio_Audio_Download_result( const Audio_Audio_Download_result& );
    Audio_Audio_Download_result& operator=( const Audio_Audio_Download_result& );
    Audio_Audio_Download_result() noexcept {}

    virtual ~Audio_Audio_Download_result() noexcept;
    Audio_Download_RecvInfo success;

    _Audio_Audio_Download_result__isset __isset;

    void __set_success( const Audio_Download_RecvInfo& val );

    bool operator==( const Audio_Audio_Download_result& rhs ) const {
        if ( !( success == rhs.success ) )
            return false;
        return true;
    }
    bool operator!=( const Audio_Audio_Download_result& rhs ) const {
        return !( *this == rhs );
    }

    bool operator<( const Audio_Audio_Download_result& ) const;

    uint32_t read( ::apache::thrift::protocol::TProtocol* iprot );
    uint32_t write( ::apache::thrift::protocol::TProtocol* oprot ) const;
};

typedef struct _Audio_Audio_Download_presult__isset {
    _Audio_Audio_Download_presult__isset() : success( false ) {}
    bool success : 1;
} _Audio_Audio_Download_presult__isset;

class Audio_Audio_Download_presult {
public:
    virtual ~Audio_Audio_Download_presult() noexcept;
    Audio_Download_RecvInfo* success;

    _Audio_Audio_Download_presult__isset __isset;

    uint32_t read( ::apache::thrift::protocol::TProtocol* iprot );
};

typedef struct _Audio_Audio_Clean_args__isset {
    _Audio_Audio_Clean_args__isset() : info( false ) {}
    bool info : 1;
} _Audio_Audio_Clean_args__isset;

class Audio_Audio_Clean_args {
public:
    Audio_Audio_Clean_args( const Audio_Audio_Clean_args& ) noexcept;
    Audio_Audio_Clean_args& operator=( const Audio_Audio_Clean_args& ) noexcept;
    Audio_Audio_Clean_args() noexcept {}

    virtual ~Audio_Audio_Clean_args() noexcept;
    Audio_Clean_SendInfo info;

    _Audio_Audio_Clean_args__isset __isset;

    void __set_info( const Audio_Clean_SendInfo& val );

    bool operator==( const Audio_Audio_Clean_args& rhs ) const {
        if ( !( info == rhs.info ) )
            return false;
        return true;
    }
    bool operator!=( const Audio_Audio_Clean_args& rhs ) const {
        return !( *this == rhs );
    }

    bool operator<( const Audio_Audio_Clean_args& ) const;

    uint32_t read( ::apache::thrift::protocol::TProtocol* iprot );
    uint32_t write( ::apache::thrift::protocol::TProtocol* oprot ) const;
};

class Audio_Audio_Clean_pargs {
public:
    virtual ~Audio_Audio_Clean_pargs() noexcept;
    const Audio_Clean_SendInfo* info;

    uint32_t write( ::apache::thrift::protocol::TProtocol* oprot ) const;
};

class Audio_Audio_Clean_result {
public:
    Audio_Audio_Clean_result( const Audio_Audio_Clean_result& ) noexcept;
    Audio_Audio_Clean_result& operator=( const Audio_Audio_Clean_result& ) noexcept;
    Audio_Audio_Clean_result() noexcept {}

    virtual ~Audio_Audio_Clean_result() noexcept;

    bool operator==( const Audio_Audio_Clean_result& /* rhs */ ) const {
        return true;
    }
    bool operator!=( const Audio_Audio_Clean_result& rhs ) const {
        return !( *this == rhs );
    }

    bool operator<( const Audio_Audio_Clean_result& ) const;

    uint32_t read( ::apache::thrift::protocol::TProtocol* iprot );
    uint32_t write( ::apache::thrift::protocol::TProtocol* oprot ) const;
};

class Audio_Audio_Clean_presult {
public:
    virtual ~Audio_Audio_Clean_presult() noexcept;

    uint32_t read( ::apache::thrift::protocol::TProtocol* iprot );
};

class AudioClient : virtual public AudioIf {
public:
    AudioClient( std::shared_ptr< ::apache::thrift::protocol::TProtocol > prot ) {
        setProtocol( prot );
    }
    AudioClient( std::shared_ptr< ::apache::thrift::protocol::TProtocol > iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol > oprot ) {
        setProtocol( iprot, oprot );
    }

private:
    void setProtocol( std::shared_ptr< ::apache::thrift::protocol::TProtocol > prot ) {
        setProtocol( prot, prot );
    }
    void setProtocol( std::shared_ptr< ::apache::thrift::protocol::TProtocol > iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol > oprot ) {
        piprot_ = iprot;
        poprot_ = oprot;
        iprot_  = iprot.get();
        oprot_  = oprot.get();
    }

public:
    std::shared_ptr< ::apache::thrift::protocol::TProtocol > getInputProtocol() {
        return piprot_;
    }
    std::shared_ptr< ::apache::thrift::protocol::TProtocol > getOutputProtocol() {
        return poprot_;
    }
    void Audio_Upload( Audio_Upload_RecvInfo& _return, const Audio_Upload_SendInfo& info ) override;
    void send_Audio_Upload( const Audio_Upload_SendInfo& info );
    void recv_Audio_Upload( Audio_Upload_RecvInfo& _return );
    void Audio_Download( Audio_Download_RecvInfo& _return, const Audio_Download_SendInfo& info ) override;
    void send_Audio_Download( const Audio_Download_SendInfo& info );
    void recv_Audio_Download( Audio_Download_RecvInfo& _return );
    void Audio_Clean( const Audio_Clean_SendInfo& info ) override;
    void send_Audio_Clean( const Audio_Clean_SendInfo& info );
    void recv_Audio_Clean();

protected:
    std::shared_ptr< ::apache::thrift::protocol::TProtocol > piprot_;
    std::shared_ptr< ::apache::thrift::protocol::TProtocol > poprot_;
    ::apache::thrift::protocol::TProtocol*                   iprot_;
    ::apache::thrift::protocol::TProtocol*                   oprot_;
};

class AudioProcessor : public ::apache::thrift::TDispatchProcessor {
protected:
    ::std::shared_ptr< AudioIf > iface_;
    virtual bool dispatchCall( ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext ) override;

private:
    typedef void ( AudioProcessor::*ProcessFunction )( int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void* );
    typedef std::map< std::string, ProcessFunction > ProcessMap;
    ProcessMap                                       processMap_;
    void process_Audio_Upload( int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext );
    void process_Audio_Download( int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext );
    void process_Audio_Clean( int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext );

public:
    AudioProcessor( ::std::shared_ptr< AudioIf > iface ) : iface_( iface ) {
        processMap_[ "Audio_Upload" ]   = &AudioProcessor::process_Audio_Upload;
        processMap_[ "Audio_Download" ] = &AudioProcessor::process_Audio_Download;
        processMap_[ "Audio_Clean" ]    = &AudioProcessor::process_Audio_Clean;
    }

    virtual ~AudioProcessor() {}
};

class AudioProcessorFactory : public ::apache::thrift::TProcessorFactory {
public:
    AudioProcessorFactory( const ::std::shared_ptr< AudioIfFactory >& handlerFactory ) noexcept : handlerFactory_( handlerFactory ) {}

    ::std::shared_ptr< ::apache::thrift::TProcessor > getProcessor( const ::apache::thrift::TConnectionInfo& connInfo ) override;

protected:
    ::std::shared_ptr< AudioIfFactory > handlerFactory_;
};

class AudioMultiface : virtual public AudioIf {
public:
    AudioMultiface( std::vector< std::shared_ptr< AudioIf > >& ifaces ) : ifaces_( ifaces ) {}
    virtual ~AudioMultiface() {}

protected:
    std::vector< std::shared_ptr< AudioIf > > ifaces_;
    AudioMultiface() {}
    void add( ::std::shared_ptr< AudioIf > iface ) {
        ifaces_.push_back( iface );
    }

public:
    void Audio_Upload( Audio_Upload_RecvInfo& _return, const Audio_Upload_SendInfo& info ) override {
        size_t sz = ifaces_.size();
        size_t i  = 0;
        for ( ; i < ( sz - 1 ); ++i ) {
            ifaces_[ i ]->Audio_Upload( _return, info );
        }
        ifaces_[ i ]->Audio_Upload( _return, info );
        return;
    }

    void Audio_Download( Audio_Download_RecvInfo& _return, const Audio_Download_SendInfo& info ) override {
        size_t sz = ifaces_.size();
        size_t i  = 0;
        for ( ; i < ( sz - 1 ); ++i ) {
            ifaces_[ i ]->Audio_Download( _return, info );
        }
        ifaces_[ i ]->Audio_Download( _return, info );
        return;
    }

    void Audio_Clean( const Audio_Clean_SendInfo& info ) override {
        size_t sz = ifaces_.size();
        size_t i  = 0;
        for ( ; i < ( sz - 1 ); ++i ) {
            ifaces_[ i ]->Audio_Clean( info );
        }
        ifaces_[ i ]->Audio_Clean( info );
    }
};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class AudioConcurrentClient : virtual public AudioIf {
public:
    AudioConcurrentClient( std::shared_ptr< ::apache::thrift::protocol::TProtocol > prot, std::shared_ptr< ::apache::thrift::async::TConcurrentClientSyncInfo > sync ) : sync_( sync ) {
        setProtocol( prot );
    }
    AudioConcurrentClient( std::shared_ptr< ::apache::thrift::protocol::TProtocol > iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol > oprot,
                           std::shared_ptr< ::apache::thrift::async::TConcurrentClientSyncInfo > sync )
        : sync_( sync ) {
        setProtocol( iprot, oprot );
    }

private:
    void setProtocol( std::shared_ptr< ::apache::thrift::protocol::TProtocol > prot ) {
        setProtocol( prot, prot );
    }
    void setProtocol( std::shared_ptr< ::apache::thrift::protocol::TProtocol > iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol > oprot ) {
        piprot_ = iprot;
        poprot_ = oprot;
        iprot_  = iprot.get();
        oprot_  = oprot.get();
    }

public:
    std::shared_ptr< ::apache::thrift::protocol::TProtocol > getInputProtocol() {
        return piprot_;
    }
    std::shared_ptr< ::apache::thrift::protocol::TProtocol > getOutputProtocol() {
        return poprot_;
    }
    void    Audio_Upload( Audio_Upload_RecvInfo& _return, const Audio_Upload_SendInfo& info ) override;
    int32_t send_Audio_Upload( const Audio_Upload_SendInfo& info );
    void    recv_Audio_Upload( Audio_Upload_RecvInfo& _return, const int32_t seqid );
    void    Audio_Download( Audio_Download_RecvInfo& _return, const Audio_Download_SendInfo& info ) override;
    int32_t send_Audio_Download( const Audio_Download_SendInfo& info );
    void    recv_Audio_Download( Audio_Download_RecvInfo& _return, const int32_t seqid );
    void    Audio_Clean( const Audio_Clean_SendInfo& info ) override;
    int32_t send_Audio_Clean( const Audio_Clean_SendInfo& info );
    void    recv_Audio_Clean( const int32_t seqid );

protected:
    std::shared_ptr< ::apache::thrift::protocol::TProtocol >              piprot_;
    std::shared_ptr< ::apache::thrift::protocol::TProtocol >              poprot_;
    ::apache::thrift::protocol::TProtocol*                                iprot_;
    ::apache::thrift::protocol::TProtocol*                                oprot_;
    std::shared_ptr< ::apache::thrift::async::TConcurrentClientSyncInfo > sync_;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif
