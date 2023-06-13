import RPi.GPIO as GPIO # Add GPIO library to a Python sketch
import time
import time # Add time library to a Python sketch 
LED_pin = 32 # Ref Board 
SW_Pin = 22 
GPIO.setmode(GPIO.BOARD) #Setup GPIO using GPIO.Pin 
GPIO.setup(LED_pin, GPIO.OUT) #Setup pin to output 
GPIO.setup(SW_Pin, GPIO.IN, pull_up_down = GPIO.PUD_UP) 
 #Setup pin to input and Pull-Up 

while True: 
 if (GPIO.input(SW_Pin)==1): # Read Botton pin 
  GPIO.output(LED_pin,GPIO.LOW) # Set LED pin to LOW 
  print("Input = 0, LOW") 
 else: 
  GPIO.output(LED_pin,GPIO.HIGH) # Set LED pin to HIGH 
  print("Input = 1, HIGH")
 time.sleep(0.2)

