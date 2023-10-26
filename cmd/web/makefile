#编译运行
Project_path = ./webserver
echo_path = ../echo/echoservice/
Thrift_path = /usr/local/include/thrift
CC    = g++
CFlag = -g -Wall 
LIB   = -I$(Project_path) -I$(Thrift_path) -I$(echo_path) -I./
LIBS  = -std=c++11 -lthrift -lpthread


#文件
http_cpp = $(Project_path)/echo.cpp ./main.cpp 
echo_cpp = $(echo_path)echo_types.cpp $(echo_path)Echo.cpp

#行为
http: $(http_cpp)
	$(CC) $(CFlag) $(LIB) $(json_cpp) $(echo_cpp) $(http_cpp)  $(LIBS) -o ./http

clean: 
	-rm ./http
