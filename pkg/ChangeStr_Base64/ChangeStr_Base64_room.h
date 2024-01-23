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


//room
Room_GetBaseInfo_SendInfo ChangeStr_encodebase64(Room_GetBaseInfo_SendInfo & x);
Room_GetBaseInfo_RecvInfo ChangeStr_encodebase64(Room_GetBaseInfo_RecvInfo & x);
Room_GetExInfo_SendInfo ChangeStr_encodebase64(Room_GetExInfo_SendInfo & x);
Room_GetExInfo_RecvInfo ChangeStr_encodebase64(Room_GetExInfo_RecvInfo & x);
Room_GetURrelation_SendInfo ChangeStr_encodebase64(Room_GetURrelation_SendInfo & x);
Room_GetURrelation_RecvInfo ChangeStr_encodebase64(Room_GetURrelation_RecvInfo & x);
Room_Create_SendInfo ChangeStr_encodebase64(Room_Create_SendInfo & x);
Room_Create_RecvInfo ChangeStr_encodebase64(Room_Create_RecvInfo & x);
Room_Joinroom_SendInfo ChangeStr_encodebase64(Room_Joinroom_SendInfo & x);
Room_Joinroom_RecvInfo ChangeStr_encodebase64(Room_Joinroom_RecvInfo & x);
Room_Exitroom_SendInfo ChangeStr_encodebase64(Room_Exitroom_SendInfo & x);
Room_Exitroom_RecvInfo ChangeStr_encodebase64(Room_Exitroom_RecvInfo & x);
Room_ChangePasswd_SendInfo ChangeStr_encodebase64(Room_ChangePasswd_SendInfo & x);
Room_ChangePasswd_RecvInfo ChangeStr_encodebase64(Room_ChangePasswd_RecvInfo & x);
Room_ChangeExtraInfo_SendInfo ChangeStr_encodebase64(Room_ChangeExtraInfo_SendInfo & x);
Room_ChangeExtraInfo_RecvInfo ChangeStr_encodebase64(Room_ChangeExtraInfo_RecvInfo & x);
Room_ChangeDebatePos_SendInfo ChangeStr_encodebase64(Room_ChangeDebatePos_SendInfo & x);
Room_ChangeDebatePos_RecvInfo ChangeStr_encodebase64(Room_ChangeDebatePos_RecvInfo & x);
Room_GetBaseInfo_SendInfo ChangeStr_decodebase64(Room_GetBaseInfo_SendInfo & x);
Room_GetBaseInfo_RecvInfo ChangeStr_decodebase64(Room_GetBaseInfo_RecvInfo & x);
Room_GetExInfo_SendInfo ChangeStr_decodebase64(Room_GetExInfo_SendInfo & x);
Room_GetExInfo_RecvInfo ChangeStr_decodebase64(Room_GetExInfo_RecvInfo & x);
Room_GetURrelation_SendInfo ChangeStr_decodebase64(Room_GetURrelation_SendInfo & x);
Room_GetURrelation_RecvInfo ChangeStr_decodebase64(Room_GetURrelation_RecvInfo & x);
Room_Create_SendInfo ChangeStr_decodebase64(Room_Create_SendInfo & x);
Room_Create_RecvInfo ChangeStr_decodebase64(Room_Create_RecvInfo & x);
Room_Joinroom_SendInfo ChangeStr_decodebase64(Room_Joinroom_SendInfo & x);
Room_Joinroom_RecvInfo ChangeStr_decodebase64(Room_Joinroom_RecvInfo & x);
Room_Exitroom_SendInfo ChangeStr_decodebase64(Room_Exitroom_SendInfo & x);
Room_Exitroom_RecvInfo ChangeStr_decodebase64(Room_Exitroom_RecvInfo & x);
Room_ChangePasswd_SendInfo ChangeStr_decodebase64(Room_ChangePasswd_SendInfo & x);
Room_ChangePasswd_RecvInfo ChangeStr_decodebase64(Room_ChangePasswd_RecvInfo & x);
Room_ChangeExtraInfo_SendInfo ChangeStr_decodebase64(Room_ChangeExtraInfo_SendInfo & x);
Room_ChangeExtraInfo_RecvInfo ChangeStr_decodebase64(Room_ChangeExtraInfo_RecvInfo & x);
Room_ChangeDebatePos_SendInfo ChangeStr_decodebase64(Room_ChangeDebatePos_SendInfo & x);
Room_ChangeDebatePos_RecvInfo ChangeStr_decodebase64(Room_ChangeDebatePos_RecvInfo & x);