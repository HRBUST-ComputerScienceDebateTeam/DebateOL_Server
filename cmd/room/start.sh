#!/bin/bash

tarfile=room_server

if [ ! -f $tarfile ]
then
    make $tarfile
fi

./$tarfile
