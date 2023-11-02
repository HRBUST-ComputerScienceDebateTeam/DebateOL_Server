#编译运行
Project_path = ./webserver
echo_path = ../echo/echoservice
video_path = ../video/videoservice
Thrift_path = /usr/local/include/thrift
CC    = g++
CFlag = -g -Wall 
LIB   = -I$(Project_path) -I$(Thrift_path) -I$(echo_path)  -I$(video_path) -I./
LIBS  = -std=c++11 -lthrift -lpthread


#文件
http_cpp = $(Project_path)/echo.cpp $(Project_path)/video.cpp ./main.cpp 
echo_cpp = $(echo_path)/echo_types.cpp $(echo_path)/Echo.cpp
video_cpp = $(video_path)/video_types.cpp $(video_path)/Video.cpp

#行为
http: $(http_cpp)
	$(CC) $(CFlag) $(LIB) $(json_cpp) $(echo_cpp) $(video_cpp) $(http_cpp)  $(LIBS) -o ./http

clean: 
	-rm ./http
