#include "../Openssl/openssl.h"
#include "../../cmd/echo/echoservice/Echo.h"
#include "../../cmd/echo/echoservice/echo_types.h"
#include "../../cmd/video/videoservice/Video.h"
#include "../../cmd/video/videoservice/video_types.h"
#include "../../cmd/room/roomservice/Room.h"
#include "../../cmd/room/roomservice/room_types.h"
#include "../../cmd/user/userservice/User.h"
#include "../../cmd/user/userservice/user_types.h"
#include "../../cmd/audio/audioservice/Audio.h"
#include "../../cmd/audio/audioservice/audio_types.h"

Echo_SendInfo ChangeStr_encodebase64(Echo_SendInfo & x);
Echo_RecvInfo ChangeStr_encodebase64(Echo_RecvInfo & x);
Echo_SendInfo ChangeStr_decodebase64(Echo_SendInfo & x);
Echo_RecvInfo ChangeStr_decodebase64(Echo_RecvInfo & x);