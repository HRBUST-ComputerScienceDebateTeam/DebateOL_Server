#include "../../cmd/audio/audioservice/Audio.h"
#include "../../cmd/audio/audioservice/audio_types.h"
#include "../../cmd/echo/echoservice/Echo.h"
#include "../../cmd/echo/echoservice/echo_types.h"
#include "../../cmd/room/roomservice/Room.h"
#include "../../cmd/room/roomservice/room_types.h"
#include "../../cmd/user/userservice/User.h"
#include "../../cmd/user/userservice/user_types.h"
#include "../../cmd/video/videoservice/Video.h"
#include "../../cmd/video/videoservice/video_types.h"
#include "../Openssl/openssl.h"

// audio
Audio_Upload_SendInfo   ChangeStr_encodebase64( Audio_Upload_SendInfo& x );
Audio_Upload_RecvInfo   ChangeStr_encodebase64( Audio_Upload_RecvInfo& x );
Audio_Download_SendInfo ChangeStr_encodebase64( Audio_Download_SendInfo& x );
Audio_Download_RecvInfo ChangeStr_encodebase64( Audio_Download_RecvInfo& x );
Audio_Clean_SendInfo    ChangeStr_encodebase64( Audio_Clean_SendInfo& x );
Audio_Upload_SendInfo   ChangeStr_decodebase64( Audio_Upload_SendInfo& x );
Audio_Upload_RecvInfo   ChangeStr_decodebase64( Audio_Upload_RecvInfo& x );
Audio_Download_SendInfo ChangeStr_decodebase64( Audio_Download_SendInfo& x );
Audio_Download_RecvInfo ChangeStr_decodebase64( Audio_Download_RecvInfo& x );
Audio_Clean_SendInfo    ChangeStr_decodebase64( Audio_Clean_SendInfo& x );