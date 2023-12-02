#编译运行
Project_path = ./audioservice/
Thrift_path = /usr/local/include/thrift
Conf_path = ../web
CC    =  g++
CFlag = -g -Wall 
LIB   = -I$(Project_path) -I$(Thrift_path) -I$(Conf_path)
LIBS  = -std=c++11 -lthrift


#文件
server_cpp = $(Project_path)Audio_server.cpp $(Project_path)audio_types.cpp $(Project_path)Audio.cpp
client_cpp = Audio_client.cpp $(Project_path)audio_types.cpp $(Project_path)Audio.cpp


#行为
audio_server: $(server_cpp)
	$(CC) $(CFlag) $(LIB) $(server_cpp) $(LIBS) -o ./audio_server

audio_client: $(client_cpp)
	$(CC) $(CFlag) $(LIB) $(client_cpp) $(LIBS) -o ./audio_client

clean: 
	-rm ./audio_server ./audio_client
