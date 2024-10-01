#Set up Raspberry pi: 

first make sure you enable raspberry pi settings for remote GPIO connection. 

Follow remoteGPIOsettings picture then enableRemoteGPIO picture. To keep enable pigpiod follow the last picture or below: 

Enabling remote GPIO settings a different way: 
#type in the following to raspberry pi command prompt to enable remote GPIO

sudo raspi-confi

#click on interfacing options -> remote gpio -> yes
#figure out your raspberry pi IP address using ifconfig on command prompt or wifi settings on top right. 
----------------------------------------------------------------------

#type this to start pigpiod which is a daemon of pigpio: 
sudo systemctl start pigpiod

#type this to enable from start up: 
sudo systemctl enable pigpiod

#thats it from raspberry pi side.
-------------------------------------------------------------------------

After doing that, make sure the connections for raspberry pi side are complete (gpio17 to led to resistor to ground)
enable the virtual environment which already has the libraries installed. 


-------------------------------------------------------------------------

********switch the part of the code that says factory with the ip address of your raspberry PI *********
-------------------------------------------------------------------------
you can run your code at this point. 

*NOTE: according to the documentation, sometimes you will need to create a HAT to be able to access/read the pins depending on what is connected to it (certain boards). 
*NOTE: Working with wifi/ethernet connections you may want to establish a static connection.
*NOTE: you can connect multiple raspberry pis this way to allow communication between them (works off of sockets)