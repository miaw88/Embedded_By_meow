import RPi.GPIO as GPIO # Add GPIO library to a Python sketch 
import time

LED_pin = 32 # Ref Board 
SW_Pin = 22
state = 0
 
GPIO.setmode(GPIO.BOARD) #Setup GPIO using GPIO.Pin 
GPIO.setup(LED_pin, GPIO.OUT) #Setup pin to output 
GPIO.setup(SW_Pin, GPIO.IN, pull_up_down = GPIO.PUD_UP) 
 #Setup pin to input and Pull-Up 

while True: 
 if (GPIO.input(SW_Pin)==0): # Read Botton pin 
  state =  1 - state 
  GPIO.output(LED_pin,state) # Set LED pin to HIGH 
  print("State = %d",state)
  time.sleep(0.2)

