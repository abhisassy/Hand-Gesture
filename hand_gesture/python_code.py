import serial #Serial imported for Serial communication
import time #Required to use delay functions
import pyautogui
import win32
import wmi


#import serial.tools.list_ports
#ports = list(serial.tools.list_ports.comports())
#for p in ports:
#    print (p)
   
ArduinoSerial = serial.Serial('COM4',9600) #Create Serial port object called arduinoSerialData
time.sleep(2) #wait for 2 seconds for the communication to get established
count =0
while 1:
    incoming = str (ArduinoSerial.readline()) #read the serial data and print it as line
    print (incoming)
    
    if 'Play/Pause' in incoming:
        pyautogui.press('space')

    if 'Rewind' in incoming:
        pyautogui.press('left')  

    if 'Forward' in incoming:
        pyautogui.press('right') 

    if 'Vup' in incoming:
        pyautogui.press('up')
        

    if 'Vdown' in incoming:
        pyautogui.press('down')

    if 'Exit' in incoming:
        pyautogui.hotkey('win','d')

    if 'fullscreen' in incoming:
        pyautogui.press('f')

    if 'lightup' in incoming:
        wmi.WMI(namespace='wmi').WmiMonitorBrightnessMethods()[0].WmiSetBrightness(80, 0)

    if 'lightdown' in incoming:
         wmi.WMI(namespace='wmi').WmiMonitorBrightnessMethods()[0].WmiSetBrightness(0, 0)
        
    if 'start' in incoming:
        pyautogui.alert('GESTURES ON')
    if 'stop' in incoming:
        pyautogui.alert('GESTURES OFF')

    if 'tab' in incoming:
        pyautogui.keyDown('alt');
        pyautogui.press('tab');
        
    if 'lefttab' in incoming:
        pyautogui.press('left')
    if 'righttab' in incoming:
        pyautogui.press('right')
    if 'release' in incoming:
        pyautogui.keyUp('alt')
    incoming = "";
    
