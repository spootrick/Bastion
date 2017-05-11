# Raspberry Pi Camera Module Live Image Processing
This repo contains files for image processing by using opencv python library with raspberry pi camera module.

The process is as follow:
* Create a named pipe (mkfifo) on client side by running `readMkfifoStream.sh` script.
* Run `colorTracking.py` python script on client side.
* Run `netcatStream.sh` on raspberry side.

# netcat
It is a simple tool for TCP&UDP connections.

# Named Pipe
FIFO based unix pipe. It can be created by typing `mkfifo file_name`
