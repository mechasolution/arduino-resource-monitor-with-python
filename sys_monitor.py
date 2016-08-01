import psutil as ps
import serial
import time
import datetime

ser = serial.Serial()
ser.port = 'COM32'
ser.baudrate = 115200
ser.open()
while (True):
    if(ser.inWaiting() > 0):
        break
while (True):
    now = datetime.datetime.now()
    hour = bytes([now.hour])
    minute = bytes([now.minute])
    cpu_p = int(ps.cpu_percent())
    mem_p = int(ps.virtual_memory().percent)
    disk_p = int(ps.disk_usage('/').percent)
    ser.write(str.encode("h"))
    ser.write(hour)
    ser.write(str.encode("m"))
    ser.write(minute)
    ser.write(str.encode("C"))
    ser.write(bytes([cpu_p]))
    ser.write(str.encode("M"))
    ser.write(bytes([mem_p]))
    ser.write(str.encode("D"))
    ser.write(bytes([disk_p]))
    time.sleep(2)
