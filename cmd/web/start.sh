#!/bin/bash

tarfile=web_server

if [ ! -f $tarfile ]
then
    make $tarfile
fi

./$tarfile
