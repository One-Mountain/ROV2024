import pygame 
from gpiozero.pins.pigpio import PiGPIOFactory
from gpiozero import Device 
import gpiozero
#import adafruit_servokit 
#from adafruit_servokit import ServoKit
#from adafruit_pca9685 import PCA9685
#import busio 
import time

pygame.init()
factory = PiGPIOFactory(host = "192.168.1.23") #raspberry pi IP Address here
bus = 1
address = 0x40
'''   
GPIOZero doesn't support I2C yet, there could be a work around using SMBbus or busio
or even using a Device class from gpiozero. Implementation of that should go here
'''
Device.pin_factory = factory
gpiozero.PinInfo
#i2c = busio.I2C(scl=3,sda=5)

#gpiozero.PinInfo(interfaces="i2c"
#adafruit_servokit.I2C
#factory.connection.i2c_open(0,0x53)
#kit = ServoKit(channels=16)


SPEEDCOEFFICIENT = 10
def main():
    joysticks = {}
    #starting angles/speeds
    #motor 1
    fph = 90 #middle?
    #motor 2
    fsh = 90
    #motor 3
    bph = 90
    #motor 4
    bsh = 90
    done = False
    while not done:
        # Event processing step.
        # Possible joystick events: JOYAXISMOTION, JOYBALLMOTION, JOYBUTTONDOWN,
        # JOYBUTTONUP, JOYHATMOTION, JOYDEVICEADDED, JOYDEVICEREMOVED
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True  # Flag that we are done so we exit this loop.

            if event.type == pygame.JOYBUTTONDOWN:
                print("Controller button pressed.")

            if event.type == pygame.JOYBUTTONUP:
                print("Joystick button released.")

            # Handle hotplugging
            if event.type == pygame.JOYDEVICEADDED:
                # This event will be generated when the program starts for every
                # joystick, filling up the list without needing to create them manually.
                joy = pygame.joystick.Joystick(event.device_index)
                joysticks[joy.get_instance_id()] = joy
                print(f"Joystick {joy.get_instance_id()} connencted")

            if event.type == pygame.JOYDEVICEREMOVED:
                del joysticks[event.instance_id]
                print(f"Joystick {event.instance_id} disconnected")
        for joystick in joysticks.values(): 
            Lupdown = joystick.get_axis(1) #left joystick up/down neg is up
            if abs(Lupdown) <= 0.05: 
                Lupdown = 0
            fph -= Lupdown*SPEEDCOEFFICIENT
            fsh -= Lupdown*SPEEDCOEFFICIENT
            bph -= Lupdown*SPEEDCOEFFICIENT
            bsh -= Lupdown*SPEEDCOEFFICIENT

            Lleftright = joystick.get_axis(0) #left joystick left/right
            if abs(Lleftright) <=0.05: 
                Lleftright = 0
            fph += Lleftright *SPEEDCOEFFICIENT
            bsh += Lleftright *SPEEDCOEFFICIENT
            fsh -= Lleftright *SPEEDCOEFFICIENT
            bph -= Lleftright *SPEEDCOEFFICIENT

            Rupdown = joystick.get_axis(3) #right joystick up/down neg is up
            if abs(Rupdown) <= 0.05: 
                Rupdown = 0
            fph -= Rupdown *SPEEDCOEFFICIENT
            fsh -= Rupdown *SPEEDCOEFFICIENT
            bph += Rupdown *SPEEDCOEFFICIENT
            bsh += Rupdown *SPEEDCOEFFICIENT

            Rleftright = joystick.get_axis(2) #right joystick left/right 
            if abs(Rleftright) <= 0.05: 
                Rleftright = 0
            fph += Rleftright *SPEEDCOEFFICIENT
            bph += Rleftright *SPEEDCOEFFICIENT
            fsh -= Rleftright *SPEEDCOEFFICIENT
            bsh -= Rleftright *SPEEDCOEFFICIENT
            
            fph = min(max(0, fph), 180)
            fsh = min(max(0, fsh), 180)
            bph = min(max(0, bph), 180)
            bsh = min(max(0, bsh), 180)
            print(f"Motor fph has: {round(fph,1)}")
            print(f"Motor fsh has: {round(fsh,1)}")
            print(f"Motor bph has: {round(bph,1)}")
            print(f"Motor bsh has: {round(bsh,1)}")
            print(" ")
            print(" ")
            print(" ")
            print(" ")
            time.sleep(0.5)
            #kit.servo[0].angle = min(max(0,fph), 180) # servo 0 is fph
            #kit.servo[1].angle = min(max(0,fsh), 180) # servo 0 is fsh
            #kit.servo[2].angle = min(max(0,bph), 180) # servo 0 is bph
            #kit.servo[3].angle = min(max(0,bsh), 180) # servo 0 is bsh


if __name__ == "__main__":
    main()
    # If you forget this line, the program will 'hang'
    # on exit if running from IDLE.
    pygame.quit()