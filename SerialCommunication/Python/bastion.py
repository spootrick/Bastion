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

""")

try:
  serial_connection = serial.Serial('/dev/ttyACM0', 115200)
except:
  print('Error: Cannot connected to the arduino!')
  sys.exit()

while 1:
  n = input('Enter a command: (type h for help)')
  command = str(n)

  if command == "h":
    print("""
Bastion Help Page
-------------------------
w - move forward
s - move backward

space - stop

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
  elif command == "q":
    print("exit!")
    sys.exit()
  else:
    print("Typed wrong command! Press h for help.")


