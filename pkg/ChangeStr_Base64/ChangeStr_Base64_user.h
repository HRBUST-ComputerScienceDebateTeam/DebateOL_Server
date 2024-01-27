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

// user
User_GetBaseInfo_SendInfo      ChangeStr_encodebase64( User_GetBaseInfo_SendInfo& x );
User_GetBaseInfo_RecvInfo      ChangeStr_encodebase64( User_GetBaseInfo_RecvInfo& x );
User_GetSocialInfo_SendInfo    ChangeStr_encodebase64( User_GetSocialInfo_SendInfo& x );
User_GetSocialInfo_RecvInfo    ChangeStr_encodebase64( User_GetSocialInfo_RecvInfo& x );
User_GetExInfo_SendInfo        ChangeStr_encodebase64( User_GetExInfo_SendInfo& x );
User_GetExInfo_RecvInfo        ChangeStr_encodebase64( User_GetExInfo_RecvInfo& x );
User_reg_SendInfo              ChangeStr_encodebase64( User_reg_SendInfo& x );
User_reg_RecvInfo              ChangeStr_encodebase64( User_reg_RecvInfo& x );
User_login_Tel_SendInfo        ChangeStr_encodebase64( User_login_Tel_SendInfo& x );
User_login_num_SendInfo        ChangeStr_encodebase64( User_login_num_SendInfo& x );
User_login_RecvInfo            ChangeStr_encodebase64( User_login_RecvInfo& x );
User_logoff_SendInfo           ChangeStr_encodebase64( User_logoff_SendInfo& x );
User_logoff_RecvInfo           ChangeStr_encodebase64( User_logoff_RecvInfo& x );
User_refresh_jwt1_SendInfo     ChangeStr_encodebase64( User_refresh_jwt1_SendInfo& x );
User_refresh_jwt1_RecvInfo     ChangeStr_encodebase64( User_refresh_jwt1_RecvInfo& x );
User_refresh_jwt2_SendInfo     ChangeStr_encodebase64( User_refresh_jwt2_SendInfo& x );
User_refresh_jwt2_RecvInfo     ChangeStr_encodebase64( User_refresh_jwt2_RecvInfo& x );
User_friend_SendInfo           ChangeStr_encodebase64( User_friend_SendInfo& x );
User_friend_RecvInfo           ChangeStr_encodebase64( User_friend_RecvInfo& x );
User_follow_SendInfo           ChangeStr_encodebase64( User_follow_SendInfo& x );
User_follow_RecvInfo           ChangeStr_encodebase64( User_follow_RecvInfo& x );
User_followed_SendInfo         ChangeStr_encodebase64( User_followed_SendInfo& x );
User_followed_RecvInfo         ChangeStr_encodebase64( User_followed_RecvInfo& x );
User_ModifyBaseInfo_SendInfo   ChangeStr_encodebase64( User_ModifyBaseInfo_SendInfo& x );
User_ModifyBaseInfo_RecvInfo   ChangeStr_encodebase64( User_ModifyBaseInfo_RecvInfo& x );
User_ModifySocialInfo_SendInfo ChangeStr_encodebase64( User_ModifySocialInfo_SendInfo& x );
User_ModifySocialInfo_RecvInfo ChangeStr_encodebase64( User_ModifySocialInfo_RecvInfo& x );
User_ModifyExInfo_SendInfo     ChangeStr_encodebase64( User_ModifyExInfo_SendInfo& x );
User_ModifyExInfo_RecvInfo     ChangeStr_encodebase64( User_ModifyExInfo_RecvInfo& x );

User_GetBaseInfo_SendInfo      ChangeStr_decodebase64( User_GetBaseInfo_SendInfo& x );
User_GetBaseInfo_RecvInfo      ChangeStr_decodebase64( User_GetBaseInfo_RecvInfo& x );
User_GetSocialInfo_SendInfo    ChangeStr_decodebase64( User_GetSocialInfo_SendInfo& x );
User_GetSocialInfo_RecvInfo    ChangeStr_decodebase64( User_GetSocialInfo_RecvInfo& x );
User_GetExInfo_SendInfo        ChangeStr_decodebase64( User_GetExInfo_SendInfo& x );
User_GetExInfo_RecvInfo        ChangeStr_decodebase64( User_GetExInfo_RecvInfo& x );
User_reg_SendInfo              ChangeStr_decodebase64( User_reg_SendInfo& x );
User_reg_RecvInfo              ChangeStr_decodebase64( User_reg_RecvInfo& x );
User_login_Tel_SendInfo        ChangeStr_decodebase64( User_login_Tel_SendInfo& x );
User_login_num_SendInfo        ChangeStr_decodebase64( User_login_num_SendInfo& x );
User_login_RecvInfo            ChangeStr_decodebase64( User_login_RecvInfo& x );
User_logoff_SendInfo           ChangeStr_decodebase64( User_logoff_SendInfo& x );
User_logoff_RecvInfo           ChangeStr_decodebase64( User_logoff_RecvInfo& x );
User_refresh_jwt1_SendInfo     ChangeStr_decodebase64( User_refresh_jwt1_SendInfo& x );
User_refresh_jwt1_RecvInfo     ChangeStr_decodebase64( User_refresh_jwt1_RecvInfo& x );
User_refresh_jwt2_SendInfo     ChangeStr_decodebase64( User_refresh_jwt2_SendInfo& x );
User_refresh_jwt2_RecvInfo     ChangeStr_decodebase64( User_refresh_jwt2_RecvInfo& x );
User_friend_SendInfo           ChangeStr_decodebase64( User_friend_SendInfo& x );
User_friend_RecvInfo           ChangeStr_decodebase64( User_friend_RecvInfo& x );
User_follow_SendInfo           ChangeStr_decodebase64( User_follow_SendInfo& x );
User_follow_RecvInfo           ChangeStr_decodebase64( User_follow_RecvInfo& x );
User_followed_SendInfo         ChangeStr_decodebase64( User_followed_SendInfo& x );
User_followed_RecvInfo         ChangeStr_decodebase64( User_followed_RecvInfo& x );
User_ModifyBaseInfo_SendInfo   ChangeStr_decodebase64( User_ModifyBaseInfo_SendInfo& x );
User_ModifyBaseInfo_RecvInfo   ChangeStr_decodebase64( User_ModifyBaseInfo_RecvInfo& x );
User_ModifySocialInfo_SendInfo ChangeStr_decodebase64( User_ModifySocialInfo_SendInfo& x );
User_ModifySocialInfo_RecvInfo ChangeStr_decodebase64( User_ModifySocialInfo_RecvInfo& x );
User_ModifyExInfo_SendInfo     ChangeStr_decodebase64( User_ModifyExInfo_SendInfo& x );
User_ModifyExInfo_RecvInfo     ChangeStr_decodebase64( User_ModifyExInfo_RecvInfo& x );
