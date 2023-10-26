#!/bin/bash

tarfile=http

if [ ! -f $tarfile ]
then
    make $tarfile
fi

./$tarfile
