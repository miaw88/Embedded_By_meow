import RPi.GPIO as GPIO # Add GPIO library to a Python sketch 
import time

SW_Pin = 22
count = 0
 
GPIO.setmode(GPIO.BOARD) #Setup GPIO using GPIO.Pin 
GPIO.setup(SW_Pin, GPIO.IN, pull_up_down = GPIO.PUD_UP) 
 #Setup pin to input and Pull-Up 

while True: 
 if (GPIO.input(SW_Pin)==0): # Read Botton pin 
  count =  count + 1
  print("Count = ",count) 
  
 time.sleep(0.2)
