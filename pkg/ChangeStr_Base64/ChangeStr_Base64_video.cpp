#include "../Openssl/openssl.h"
#include "../../cmd/video/videoservice/Video.h"
#include "../../cmd/video/videoservice/video_types.h"
#include "ChangeStr_Base64_video.h"



//video
Video_Upload_SendInfo ChangeStr_decodebase64(Video_Upload_SendInfo & x){
	x.info = Base64Decode(x.info);
	return x;
}

Video_Upload_RecvInfo ChangeStr_decodebase64(Video_Upload_RecvInfo & x){
	return x;
}

Video_Download_SendInfo ChangeStr_decodebase64(Video_Download_SendInfo & x){
	return x;
}

Video_Download_RecvInfo ChangeStr_decodebase64(Video_Download_RecvInfo & x){
	x.info = Base64Decode(x.info);
	return x;
}

Video_Clean_SendInfo ChangeStr_decodebase64(Video_Clean_SendInfo & x){
	return x;
}

Video_Upload_SendInfo ChangeStr_encodebase64(Video_Upload_SendInfo & x){
	x.info = Base64Encode(x.info);
	return x;
}

Video_Upload_RecvInfo ChangeStr_encodebase64(Video_Upload_RecvInfo & x){
	return x;
}

Video_Download_SendInfo ChangeStr_encodebase64(Video_Download_SendInfo & x){
	return x;
}

Video_Download_RecvInfo ChangeStr_encodebase64(Video_Download_RecvInfo & x){
	x.info = Base64Encode(x.info);
	return x;
}

Video_Clean_SendInfo ChangeStr_encodebase64(Video_Clean_SendInfo & x){
	return x;
}