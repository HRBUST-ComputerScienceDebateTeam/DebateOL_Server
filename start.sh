#!/bin/bash
frp_path="./frp"
echo_server_path="./cmd/echo"
video_server_path="./cmd/video"
web_server_path="./cmd/web"


#frp
konsole --hold  --workdir $frp_path -e fish -c "./start.sh" &
if [ $? -eq 0 ]; then
    echo "open frpc success"
else
    echo "open frpc fail"
fi

#web
konsole --hold --workdir $web_server_path -e fish -c "./start.sh" &
if [ $? -eq 0 ]; then
    echo "open web_server success"
else
    echo "open web_server fail"
fi

#video
konsole --hold --workdir $video_server_path -e fish -c "./start.sh" &
if [ $? -eq 0 ]; then
    echo "open video_server success"
else
    echo "open video_server fail"
fi


#echo
konsole --hold --workdir $echo_server_path -e fish -c "./start.sh" &
if [ $? -eq 0 ]; then
    echo "open echo_server success"
else
    echo "open echo_server fail"
fi