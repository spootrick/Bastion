import serial
import sys

print("""

/  |                            /  |    /  |
$$ |____    ______    _______  _$$ |_   $$/   ______   _______
$$      \  /      \  /       |/ $$   |  /  | /      \ /       \
$$$$$$$  | $$$$$$  |/$$$$$$$/ $$$$$$/   $$ |/$$$$$$  |$$$$$$$  |
$$ |  $$ | /    $$ |$$      \   $$ | __ $$ |$$ |  $$ |$$ |  $$ |
$$ |__$$ |/$$$$$$$ | $$$$$$  |  $$ |/  |$$ |$$ \__$$ |$$ |  $$ |
$$    $$/ $$    $$ |/     $$/   $$  $$/ $$ |$$    $$/ $$ |  $$ |
$$$$$$$/   $$$$$$$/ $$$$$$$/     $$$$/  $$/  $$$$$$/  $$/   $$/
                                                    The Sentinel

Type "h" for help.

""")

try:
  serial_connection = serial.Serial('/dev/ttyACM0', 9600)
except:
  print('Error: Cannot connected to the arduino!')
  sys.exit()

while 1:
  n = input('Enter a command: ')
  command = str(n)

  if command == "h":
    print("""

Bastion Help Page
-------------------------
w - move forward
s - move backward
a - turn left
d - turn right

Press "space" for stop!

""")

  elif command == "w":
    serial_connection.write(bytes('1', 'UTF-8'))
    print("Moving forward.. ")
  elif command == "s":
    serial_connection.write(bytes('2', 'UTF-8'))
    print("Moving backward.. ")
  elif command == " ":
    serial_connection.write(bytes('0', 'UTF-8'))
    print("Stop!")
  elif command == "a":
    serial_connection.write(bytes('3', 'UTF-8'))
    print("Turning left..")
  elif command == "d":
    serial_connection.write(bytes('4', 'UTF-8'))
    print("Turning right..")
  elif command == "q":
    print("exit!")
    sys.exit()
  else:
    print("Typed wrong command! Press h for help.")
