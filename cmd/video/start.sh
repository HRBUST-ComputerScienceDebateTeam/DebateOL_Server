#!/bin/bash

tarfile=video_server

if [ ! -f $tarfile ]
then
    make $tarfile
fi

./$tarfile
