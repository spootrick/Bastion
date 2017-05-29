# ====================================
# -*- coding: utf-8 -*-
# project name:     Bastion The Sentinel
# file name:        colorTracking.py
# python version:   3.4
# description:      tracking multiple colors at the same time with
#                   raspberry pi camera module with opencv python
#                   library
# ====================================

try:
    import cv2
except ImportError:
    raise ImportError('Could not import cv2 library')

try:
    import numpy as np
except ImportError:
    raise ImportError('Could not import numpy library')


# capturing through raspberry pi camera
cap = cv2.VideoCapture('http://192.168.43.46:8000/stream.mjpg')

# on kaplumbaa network use below ip address
# cap = cv2.VideoCapture('http://192.168.1.25:8000/stream.mjpg')

while 1:
    # reading the video capture
    _, img = cap.read()

    # converting frame(img, i.e BGR) to HSV
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    # defining the range of red
    red_lower = np.array([136, 87, 111], np.uint8)
    red_upper = np.array([180, 255, 255], np.uint8)

    # defining the range of blue
    blue_lower = np.array([99, 115, 150], np.uint8)
    blue_upper = np.array([110, 255, 255], np.uint8)

    # defining the range of yellow
    yellow_lower = np.array([22, 60, 200], np.uint8)
    yellow_upper = np.array([60, 255, 255], np.uint8)

    # finding the range of red, blue and yellow in image
    red = cv2.inRange(hsv, red_lower, red_upper)
    blue = cv2.inRange(hsv, blue_lower, blue_upper)
    yellow = cv2.inRange(hsv, yellow_lower, yellow_upper)

    # Morphological transformation, Dilation
    kernal = np.ones((5, 5), "uint8")

    red = cv2.dilate(red, kernal)
    res_0 = cv2.bitwise_and(img, img, mask = red)

    blue = cv2.dilate(blue, kernal)
    res_1 = cv2.bitwise_and(img, img, mask = blue)

    yellow = cv2.dilate(yellow, kernal)
    res_2 = cv2.bitwise_and(img, img, mask = yellow)

    # Tracking the RED color
    (_, contours, hierarchy) = cv2.findContours(red, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        if (area > 300):
            x, y, w, h = cv2.boundingRect(contour)
            img = cv2.rectangle(img, (x, y), (x + w, y + h), (0, 0, 255), 2)
            label_red = "red: {}, {}".format(x, y)
            cv2.putText(img, label_red, (x, y), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255))

    # Tracking the BLUE color
    (_, contours, hierarchy) = cv2.findContours(blue, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        if (area > 300):
            x, y, w, h = cv2.boundingRect(contour)
            img = cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 0), 2)
            label_blue = "blue: {}, {}".format(x, y)
            cv2.putText(img, label_blue, (x, y), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 0, 0))

    # Tracking the YELLOW color
    (_, contours, hierarchy) = cv2.findContours(yellow, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        if (area > 300):
            x, y, w, h = cv2.boundingRect(contour)
            img = cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 255), 2)
            label_yellow = "yellow: {}, {}".format(x, y)
            cv2.putText(img, label_yellow, (x, y), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 255))


    # show main window
    cv2.imshow("Bastion Color tracking", img)

    # show red mask window
    cv2.imshow("mask_red", red)
    # show red mask
    cv2.imshow("mask red", res_0)

    # show blue mask window
    cv2.imshow("mask blue", res_1)
    # show blue mask
    # cv2.imshow("mask_blue", blue)

    # show yellow mask window
    cv2.imshow("mask yellow", res_2)
    # show yellow mask
    # cv2.imshow("mask_yellow", yellow)

    # show converted hsv image
    cv2.imshow("hsv", hsv)

    if cv2.waitKey(10) & 0xFF == ord('q'):
        cap.release()
        cv2.destroyAllWindows()
        break
