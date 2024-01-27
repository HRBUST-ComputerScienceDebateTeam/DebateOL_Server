#include "ChangeStr_Base64_audio.h"
#include "../../cmd/audio/audioservice/Audio.h"
#include "../../cmd/audio/audioservice/audio_types.h"
#include "../Openssl/openssl.h"

// audio
Audio_Upload_SendInfo ChangeStr_decodebase64( Audio_Upload_SendInfo& x ) {
    x.info = Base64Decode( x.info );
    return x;
}

Audio_Upload_RecvInfo ChangeStr_decodebase64( Audio_Upload_RecvInfo& x ) {
    return x;
}

Audio_Download_SendInfo ChangeStr_decodebase64( Audio_Download_SendInfo& x ) {
    return x;
}

Audio_Download_RecvInfo ChangeStr_decodebase64( Audio_Download_RecvInfo& x ) {
    x.info = Base64Decode( x.info );
    return x;
}

Audio_Clean_SendInfo ChangeStr_decodebase64( Audio_Clean_SendInfo& x ) {
    return x;
}

Audio_Upload_SendInfo ChangeStr_encodebase64( Audio_Upload_SendInfo& x ) {
    x.info = Base64Encode( x.info );
    return x;
}

Audio_Upload_RecvInfo ChangeStr_encodebase64( Audio_Upload_RecvInfo& x ) {
    return x;
}

Audio_Download_SendInfo ChangeStr_encodebase64( Audio_Download_SendInfo& x ) {
    return x;
}

Audio_Download_RecvInfo ChangeStr_encodebase64( Audio_Download_RecvInfo& x ) {
    x.info = Base64Encode( x.info );
    return x;
}

Audio_Clean_SendInfo ChangeStr_encodebase64( Audio_Clean_SendInfo& x ) {
    return x;
}
