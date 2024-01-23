#include "../Openssl/openssl.h"
#include "../../cmd/echo/echoservice/Echo.h"
#include "../../cmd/echo/echoservice/echo_types.h"
#include "./ChangeStr_Base64_echo.h"

Echo_SendInfo ChangeStr_decodebase64(Echo_SendInfo & x){
	x.info = Base64Decode(x.info);
	return x;
}

Echo_RecvInfo ChangeStr_decodebase64(Echo_RecvInfo & x){
	x.info = Base64Decode(x.info);
	x.time = Base64Decode(x.time);
	return x;
}

Echo_SendInfo ChangeStr_encodebase64(Echo_SendInfo & x){
	x.info = Base64Encode(x.info);
	return x;
}

Echo_RecvInfo ChangeStr_encodebase64(Echo_RecvInfo & x){
	x.info = Base64Encode(x.info);
	x.time = Base64Encode(x.time);
	return x;
}
