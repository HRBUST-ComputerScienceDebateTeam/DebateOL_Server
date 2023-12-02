#!/bin/bash

tarfile=audio_server

if [ ! -f $tarfile ]
then
    make $tarfile
fi

./$tarfile
