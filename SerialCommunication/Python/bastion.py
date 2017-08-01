#!/usr/bin/env python
# -- coding: utf-8 --
# File              : bastion.py
# Description       : Serial connection script for arduino
# Author            : Furkan Karakoyunlu
# Date              : 21.05.2017
# Python version    : 3.4
# =======================================

import sys,os

try:
    import curses
except ImportError:
    raise ImportError("The library 'curses' couldn't imported")

try:
    import serial
except ImportError:
    raise ImportError("The library 'serial' couldn't imported")


def draw_screen_for_serial_connection(screen):
    # do not echo keys to the screen
    curses.noecho()
    # send keys without pressing enter
    curses.cbreak()

    try:
      serial_connection = serial.Serial('/dev/ttyACM1', 9600)
    except:
      print('Error: Cannot connected to the arduino!')
      sys.exit()

    command = ''
    k = 0

    cursor_x = 0
    cursor_y = 0

    # starting colors for curses
    curses.start_color()
    curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
    curses.init_pair(2, curses.COLOR_BLACK, curses.COLOR_WHITE)

    # looping the last pressed key k
    while (k != ord('Q')):
        # initialization
        screen.clear()
        height, width = screen.getmaxyx()

        if k == ord('w'): # forward 200
            serial_connection.write(bytes('1', 'UTF-8'))
            command = 'FORWARD 200'
        elif k == ord('s'): # backward 200
            serial_connection.write(bytes('2', 'UTF-8'))
            command = 'BACKWARD 200'
        if k == ord('W'): # forward 400
            serial_connection.write(bytes('3', 'UTF-8'))
            command = 'FORWARD 400'
        elif k == ord('S'): # backward 400
            serial_connection.write(bytes('4', 'UTF-8'))
            command = 'BACKWARD 400'
        elif k == ord('a'): # turn left
            serial_connection.write(bytes('5', 'UTF-8'))
            command = 'TURN LEFT'
        elif k == ord('d'): # turn right
            serial_connection.write(bytes('6', 'UTF-8'))
            command = 'TURN RIGHT'
        elif k == ord(' '): # stop
            serial_connection.write(bytes('0', 'UTF-8'))
            command = 'STOP'

        # Servo controls
        # SERVO 1
        elif k == ord('0'):
            serial_connection.write(bytes('7', 'UTF-8'))
            command = 'Servo 1 moving positive direction'

        elif k == ord(','):
            serial_connection.write(bytes('8', 'UTF-8'))
            command = 'Servo 1 moving negative direction'

        # SERVO 2
    	elif k == ord('n'):
    		serial_connection.write(bytes('9', 'UTF-8'))
    		command = 'Servo 2 moving positive direction'

    	elif k == ord('m'):
    		serial_connection.write(bytes('10', 'UTF-8'))
    		command = 'Servo 2 moving negative direction'

        # SERVO 3
        elif k == ord('7'):
            serial_connection.write(bytes('11', 'UTF-8'))
            command = 'Servo 3 moving positive direction'

        elif k == ord('1'):
            serial_connection.write(bytes('12', 'UTF-8'))
            command = 'Servo 3 moving negative direction'

        # SERVO 4
        elif k == ord('8'):
            serial_connection.write(bytes('13', 'UTF-8'))
            command = 'Servo 4 moving positive direction'

        elif k == ord('2'):
            serial_connection.write(bytes('14', 'UTF-8'))
            command = 'Servo 4 moving negative direction'

        # SERVO 5 (in arduino servo 6)
        elif k == ord('9'):
            serial_connection.write(bytes('17', 'UTF-8'))
            command = 'Servo 5 moving positive direction'
        elif k == ord('3'):
            serial_connection.write(bytes('18', 'UTF-8'))
            command = 'Servo 5 moving negative direction'

        # SERVO 5 ROTATOR 1
        elif k == ord('4'):
        	serial_connection.write(bytes('15', 'UTF-8'))
        	command = 'Servo 5 ROTATOR moving positive direction'

        elif k == ord('6'):
        	serial_connection.write(bytes('16', 'UTF-8'))
        	command = 'Servo 5 ROTATOR moving negative direction'
		
		# SERVO 6 ROTATOR 2
        elif k == ord('+'):
        	serial_connection.write(bytes('19', 'UTF-8'))
        	command = 'Servo 6 ROTATOR moving positive direction'

        elif k == ord('-'):
        	serial_connection.write(bytes('20', 'UTF-8'))
        	command = 'Servo 6 ROTATOR moving negative direction'



        # SERVO 8
        elif k == ord('/'):
            serial_connection.write(bytes('21', 'UTF-8'))
            command = 'Gripper (Servo 8) opening'

        elif k == ord('*'):
            serial_connection.write(bytes('22', 'UTF-8'))
            command = 'Gripper (Servo 8) closing'


        # declare the strings
        title = "Bastion The Sentinel Controller"[:width-1]
        subtitle = "Written by spootrick"[:width-1]
        keystr = "Last command: {}".format(command)[:width-1]
        helpstr = "w -> forward, s -> backward, a -> left, d -> right, space -> stop"
        statusbarstr = "Press 'Q' to exit | BASTION CONTROLLER"

        if command == '':
            keystr = "waiting for command ..."[:width-1]

        # text centering
        start_x_title = int((width // 2) - (len(title) // 2) - len(title) % 2)
        start_x_subtitle = int((width // 2) - (len(subtitle) // 2) - len(subtitle) % 2)
        start_x_keystr = int((width // 2) - (len(keystr) // 2) - len(keystr) % 2)
        start_y = int((height // 2) - 5)

        # render status bar
        screen.attron(curses.color_pair(2))
        screen.addstr(height-1, 0, statusbarstr)
        screen.addstr(height-1, len(statusbarstr), " " * (width - len(statusbarstr) - 1))
        screen.attroff(curses.color_pair(2))

        # turning on attributes for title
        screen.attron(curses.color_pair(1))
        screen.attron(curses.A_BOLD)

        # render title
        screen.addstr(start_y, start_x_title, title)

        # turning off attributes for title
        screen.attroff(curses.color_pair(1))
        screen.attroff(curses.A_BOLD)

        # printing the rest of the text
        screen.addstr(start_y + 1, start_x_subtitle, subtitle)
        screen.addstr(start_y + 3, (width // 2) - 6, '* * * * *')
        screen.addstr(start_y + 5, start_x_keystr, keystr)
        screen.addstr(start_y + 13, (width // 2) - 35 , helpstr)
        screen.move(cursor_y, cursor_x)

        # refresh screen
        screen.refresh()

        # wait for next input
        k = screen.getch()

def main():
    curses.wrapper(draw_screen_for_serial_connection)

if __name__ == "__main__":
    main()
