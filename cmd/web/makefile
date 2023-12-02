#编译运行
Project_path = ./webserver
echo_path = ../echo/echoservice
video_path = ../video/videoservice
audio_path = ../audio/audioservice
Thrift_path = /usr/local/include/thrift
CC    = g++
CFlag = -g -Wall 
LIB   = -I$(Project_path) -I$(Thrift_path) -I$(echo_path)  -I$(video_path)  -I$(audio_path) -I./
FLAGS  = -std=c++11 -lthrift -lpthread


#文件
http_cpp = $(Project_path)/echo.cpp\
		 $(Project_path)/video.cpp \
		 $(Project_path)/audio.cpp \
		 ./main.cpp 
echo_cpp = $(echo_path)/echo_types.cpp $(echo_path)/Echo.cpp
video_cpp = $(video_path)/video_types.cpp $(video_path)/Video.cpp
audio_cpp = $(audio_path)/audio_types.cpp $(audio_path)/Audio.cpp

#行为
web_server: $(echo_cpp) $(video_cpp) $(audio_cpp) $(http_cpp)
	$(CC) $(CFlag) $(LIB) $(json_cpp) $(echo_cpp) $(video_cpp) $(audio_cpp) $(http_cpp)  $(FLAGS) -o ./web_server

clean: 
	-rm ./web_server
