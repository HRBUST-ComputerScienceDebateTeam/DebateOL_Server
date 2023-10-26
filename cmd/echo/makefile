#编译运行
Project_path = ./echoservice/
Thrift_path = /usr/local/include/thrift
Conf_path = ../web
CC    =  g++
CFlag = -g -Wall 
LIB   = -I$(Project_path) -I$(Thrift_path) -I$(Conf_path)
LIBS  = -std=c++11 -lthrift


#文件
server_cpp = $(Project_path)Echo_server.cpp $(Project_path)echo_types.cpp $(Project_path)Echo.cpp
client_cpp = Echo_client.cpp $(Project_path)echo_types.cpp $(Project_path)Echo.cpp


#行为
server: $(server_cpp)
	$(CC) $(CFlag) $(LIB) $(server_cpp) $(LIBS) -o ./server

client: $(client_cpp)
	$(CC) $(CFlag) $(LIB) $(client_cpp) $(LIBS) -o ./client

clean: 
	-rm ./server ./client
