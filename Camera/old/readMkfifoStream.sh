#!/bin/bash

if [ -p fifo264 ]
then
	rm fifo264
fi
mkfifo fifo264
# port 5777
nc -l -v -p 5777 > fifo264
