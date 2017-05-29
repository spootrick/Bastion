# Realtime Raspberry Pi 3 Camera Module Image Processing
This repo contains files for image processing by using opencv python library with raspberry pi camera module.

The process is as follow:
* Run `stream.py` on Raspberry Pi 3.
* Run `colorTracking.py` on client side. Don't forget to change IP address in the script.
```
cv2.VideoCapture('http://ip-address:8000/stream.mjpg')
```
