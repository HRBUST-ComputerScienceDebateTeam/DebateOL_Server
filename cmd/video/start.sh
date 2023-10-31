#!/bin/bash

tarfile=server

if [ ! -f $tarfile ]
then
    make $tarfile
fi

./$tarfile
