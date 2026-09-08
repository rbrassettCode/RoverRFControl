import serial
import threading

PORT_IN  = "COM4"  # STM32
PORT_OUT = "COM3"  # Arduino (or wherever you want to send it)
BAUD     = 9600

def forward():
    ser_in  = serial.Serial(PORT_IN, BAUD, timeout=1)
    ser_out = serial.Serial(PORT_OUT, BAUD, timeout=1)

    try:
        while True:
            line = ser_in.readline()
            if line:
                print(line.decode("utf-8").strip())  # confirm in terminal
                ser_out.write(line)                   # forward to Arduino
    except KeyboardInterrupt:
        ser_in.close()
        ser_out.close()

forward()