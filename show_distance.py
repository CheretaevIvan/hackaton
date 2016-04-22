import socket
import time
import pyupm_i2clcd

ID = 1
MAX_DISTANCE = 100
MAX_COUNT = 15
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
lcd = pyupm_i2clcd.Jhd1313m1(6, 0x3E, 0x62)
with open('/dev/ttymcu0', 'w+t') as f:
    countIn = 0
    countOut = 0
    result = ''
    while True:
        f.write('get_distance\n') # Send command to MCU
        f.flush()
        line = f.readline() # Read response from MCU, -1 = ERROR
        value = int(line.strip('\n\r\t '))
        lcd.clear()
        if value < MAX_DISTANCE:
            countIn += 1
        else:
            countOut += 1
        if countIn > MAX_COUNT:
            result = 'ID: %d, has object', (ID,)
            lcd.setColor(255, 0, 0) # RED
            countIn = 0
            countOut = 0
        if countOut > MAX_COUNT:
            countIn = 0
            countOut = 0
            result = 'ID: %d, empty', (ID,)
            lcd.setColor(0, 255, 0) # GREEN
        sock.sendto(result,('255.255.255.255',11719))
        lcd.write(result)
        time.sleep(0.2)