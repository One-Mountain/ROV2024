from gpiozero import LED
from gpiozero.pins.pigpio import PiGPIOFactory
from time import sleep

factory = PiGPIOFactory(host = "192.168.1.23") #raspberry pi IP Address here
myLed = LED(17, pin_factory=factory)

def blinks(): 
    while True: 
        myLed.on()
        sleep(1)
        myLed.off()
        sleep(1)

if __name__ == "__main__":
    print("starting")
    try:
        blinks()
    except KeyboardInterrupt:
        print("ending")