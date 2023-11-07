#!/bin/bash

tarfile=echo_server

if [ ! -f $tarfile ]
then
    make $tarfile
fi

./$tarfile
