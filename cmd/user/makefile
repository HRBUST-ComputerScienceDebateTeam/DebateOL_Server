#大写
BigName    = User
SmallName  = user


#路径
Top_path     = ../../
CMD_path     = $(Top_path)cmd/
RPC_path     = $(CMD_path)$(SmallName)/
Ser_path     = $(RPC_path)$(SmallName)service/

#库路径
Thrift_path  = /usr/local/include/thrift
Conf_path    = $(CMD_path)

#编译相关
CC           = CC
CPP          = g++
CFlag        = -g -Wall -std=c++11
Libflag      = -lssl -lpthread -lcrypto -lthrift -lmysqlclient -lrt

#pkg
Top_path  = ../../
PKG_rootpath  = $(Top_path)pkg/
PKG_LIB   = $(shell find $(PKG_rootpath) -maxdepth 3 -type d)
# PKG_FILE  = $(foreach dir, $(PKG_LIB), $(wildcard $(dir)/*.cpp))
PKG_path  = $(foreach lib, $(PKG_LIB),  $(patsubst %, -I%, $(lib)))
PKG_FILE =  $(PKG_rootpath)DB/DB_MYSQL.cpp \
			$(PKG_rootpath)JsonChange/jsonchange.cpp \
			$(PKG_rootpath)JWT/jwt.cpp \
			$(PKG_rootpath)Openssl/openssl.cpp \
			$(PKG_rootpath)pool/threadpool.cpp \
			$(PKG_rootpath)Sidecar/sidecar.cpp \
			$(PKG_rootpath)time_wheel/time_wheel.cpp \
			$(PKG_rootpath)ChangeStr_Base64/ChangeStr_Base64_$(SmallName).cpp

DAL_FILE  = $(RPC_path)dal/dal_$(SmallName).cpp
DAL_PATH  = $(RPC_path)dal/
#文件
type_cpp   =  $(Ser_path)$(SmallName)_types.cpp $(Ser_path)$(BigName).cpp

server_cpp =  $(type_cpp) $(Ser_path)$(BigName)_server.cpp

client_cpp =  $(type_cpp) $(Ser_path)$(BigName)_client.cpp


#汇总
ALLLIB   = 	-I$(Ser_path)\
		  	-I$(Thrift_path)\
			-I$(Conf_path)\
			-I$(PKG_path)\
			-I$(DAL_PATH)



#行为
$(SmallName)_server: $(server_cpp) $(PKG_FILE) $(DAL_FILE)
	$(CPP) $(CFlag)  $(ALLLIB) $^ -o ./$(SmallName)_server $(Libflag)

$(SmallName)_client: $(client_cpp)
	$(CPP) $(CFlag)  $(ALLLIB) $^ -o ./$(SmallName)_client $(Libflag)

clean: 
	-rm ./$(SmallName)_server ./$(SmallName)_clien