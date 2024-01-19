#!/bin/bash

tarfile=user_server

if [ ! -f $tarfile ]
then
    make $tarfile
fi

./$tarfile
