#编译运行
Project_path = ./videoservice/
Thrift_path = /usr/local/include/thrift
Conf_path = ../web
CC    =  g++
CFlag = -g -Wall 
LIB   = -I$(Project_path) -I$(Thrift_path) -I$(Conf_path)
LIBS  = -std=c++11 -lthrift


#文件
server_cpp = $(Project_path)Video_server.cpp $(Project_path)video_types.cpp $(Project_path)Video.cpp
client_cpp = Video_client.cpp $(Project_path)video_types.cpp $(Project_path)Video.cpp


#行为
server: $(server_cpp)
	$(CC) $(CFlag) $(LIB) $(server_cpp) $(LIBS) -o ./server

client: $(client_cpp)
	$(CC) $(CFlag) $(LIB) $(client_cpp) $(LIBS) -o ./client

clean: 
	-rm ./server ./client
