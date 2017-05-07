import serial
import sys

print("""

This is a demo for serial connection
type 1 to 9 for make led to blink

type 0 for exit the program.

""")

try:
  serial_connection = serial.Serial('/dev/ttyACM0', 9600)
except:
  print('Error: Cannot connected to the arduino!')
  sys.exit()

while 1:
  n = input('Enter number to blink: ')
  number_to_flash = str(n)
  
  if number_to_flash == "0":
    print("exit!")
    sys.exit()
  else:
    serial_connection.write(bytes(number_to_flash, 'UTF-8'))


