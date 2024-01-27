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

// video
Video_Upload_SendInfo   ChangeStr_encodebase64( Video_Upload_SendInfo& x );
Video_Upload_RecvInfo   ChangeStr_encodebase64( Video_Upload_RecvInfo& x );
Video_Download_SendInfo ChangeStr_encodebase64( Video_Download_SendInfo& x );
Video_Download_RecvInfo ChangeStr_encodebase64( Video_Download_RecvInfo& x );
Video_Clean_SendInfo    ChangeStr_encodebase64( Video_Clean_SendInfo& x );
Video_Upload_SendInfo   ChangeStr_decodebase64( Video_Upload_SendInfo& x );
Video_Upload_RecvInfo   ChangeStr_decodebase64( Video_Upload_RecvInfo& x );
Video_Download_SendInfo ChangeStr_decodebase64( Video_Download_SendInfo& x );
Video_Download_RecvInfo ChangeStr_decodebase64( Video_Download_RecvInfo& x );
Video_Clean_SendInfo    ChangeStr_decodebase64( Video_Clean_SendInfo& x );