import serial #Serial imported for Serial communication
import time #Required to use delay functions
import pyautogui

#import serial.tools.list_ports
#ports = list(serial.tools.list_ports.comports())
#for p in ports:
#    print (p)
   
ArduinoSerial = serial.Serial('COM4',9600) #Create Serial port object called arduinoSerialData
time.sleep(2) #wait for 2 seconds for the communication to get established

while 1:
    incoming = str (ArduinoSerial.readline()) #read the serial data and print it as line
    print (incoming)
    
    if 'Jump' in incoming:
        pyautogui.typewrite(['space'], 0.2)


   # if 'Duck' in incoming:
    #    pyautogui.typewrite(['down'],1)

    if 'Exit' in incoming:
        pyautogui.hotkey('alt','f4')


    incoming = "";
    
