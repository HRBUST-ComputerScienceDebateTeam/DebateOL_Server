#指定所有的服务
ALL_Server   = audio echo user video room

#路径
Top_path        = ../../
CMD_path        = $(Top_path)cmd/
RPC_path        = $(CMD_path)web/
SRC_path        = $(CMD_path)ServiceRegistry/
Ser_path        = $(RPC_path)webserver/
ALL_Server_path   = $(foreach sername, $(ALL_Server),$(shell echo -I$(CMD_path)$(sername)/$(sername)service/ ) )
ALL_Server_DAL_path   = $(foreach sername, $(ALL_Server),$(shell echo -I$(CMD_path)$(sername)/dal/ ) )

#库路径
Thrift_path  = /usr/local/include/thrift
Conf_path    = $(CMD_path)

#编译相关
CC           = CC
CPP          = g++
CFlag        = -g -Wall -std=c++11
Libflag      = -lssl -lpthread -lcrypto -lthrift -lmysqlclient

#pkg
Top_path  = ../../
PKG_rootpath  = $(Top_path)pkg/
PKG_LIB   = $(shell find $(PKG_rootpath) -maxdepth 3 -type d)

PKG_FILE  = $(foreach dir, $(PKG_LIB), $(wildcard $(dir)/*.cpp))
PKG_path  = $(foreach lib, $(PKG_LIB),  $(patsubst %, -I%, $(lib)))



#每个微服务的两个文件 通用 
TypeCpp1 = $(foreach sername, $(ALL_Server),  $(shell echo $(CMD_path)$(sername)/$(sername)service/$(sername)_types.cpp ))
TypeCpp2 = $(foreach sername, $(ALL_Server),  $(shell echo $(CMD_path)$(sername)/$(sername)service/$(shell echo $(sername) | sed 's/\b\(.\)/\u\1/g').cpp ))
#微服务客户端
Rpcclientfile  = $(wildcard $(Ser_path)*.cpp)

#dalcpp
dalcppfile  = $(foreach dalpath, $(ALL_Server_DAL_path),$(wildcard $(dalpath)*.cpp) )


#汇总
ALLLIB   = 	-I$(Ser_path)\
		  	-I$(Thrift_path)\
			-I$(Conf_path)\
			-I$(PKG_path)\
			-I$(ALL_Server_path)\
			-I$(ALL_Server_DAL_path)\
			-I$(SRC_path)\l
			-I./

ALLFILE  =  $(TypeCpp1) $(TypeCpp2)\
			$(Rpcclientfile)\
 			$(PKG_FILE)

#行为
web_server:$(ALLFILE) main.cpp
	$(CPP) $(CFlag) $(ALLLIB) $^  -o ./web_server $(Libflag)

clean: 
	-rm ./web_server

# g++ -g -Wall -std=c++11 
# -I../../cmd/web/webserver/ 
# -I/usr/local/include/thrift 
# -I../../cmd/ 
# -I   
# -I../../pkg/    
# -I../../pkg/JsonChange    
# -I../../pkg/Openssl    
# -I../../pkg/pool    
# -I../../pkg/JWT 
# -I
# -I../../cmd/audio/audioservice/  
# -I../../cmd/echo/echoservice/  
# -I../../cmd/user/userservice/  
# -I../../cmd/video/videoservice/  
# -I./ 
# ../../cmd/audio/audioservice/audio_types.cpp 
# ../../cmd/echo/echoservice/echo_types.cpp 
# ../../cmd/user/userservice/user_types.cpp 
# ../../cmd/video/videoservice/video_types.cpp 
# ../../cmd/audio/audioservice/Audio.cpp 
# ../../cmd/echo/echoservice/Echo.cpp 
# ../../cmd/user/userservice/User.cpp 
# ../../cmd/video/videoservice/Video.cpp 
# webserver/audio.cpp 
# webserver/echo.cpp 
# webserver/video.cpp 
# ../../pkg/JsonChange/jsonchange.cpp 
# ../../pkg/Openssl/openssl.cpp 
# ../../pkg/pool/threadpool.cpp 
# ../../pkg/JWT/jwt.cpp main.cpp  
# -o ./web_server -lssl -lpthread -lcrypto -lthrift