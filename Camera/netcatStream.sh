#!/bin/bash

# the ip of my local linux machine => 192.168.1.36 port => 5777
# -n no preview 
# -b bitrate for 10MBits/s it would be 10000000
# -vf vertical flip -hf horizontal flip
# -t 0 no time limit
# -o - output to the stdout
raspivid -vf -hf -n -w 640 -h 480 -o - -t 0 -b 10000000 | nc 192.168.1.36 5777
