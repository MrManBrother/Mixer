#!/bin/bash

PATHTOSET=$PWD/lib
CURRPATH=$LD_LIBRARY_PATH

if [[ $LD_LIBRARY_PATH == *"$PATHTOSET"* ]]
then
    dumm=0
else
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PATHTOSET
fi
