## Set up Required for Raspberry Pi
- look at the picture provided in this folder. Your raspberry pi must be set up for i2c communications.
- Also, the raspberry pi will need to be set up to download the libraries, you can do one of the following: 

## Installing from PyPI
On supported GNU/Linux systems like the Raspberry Pi, you can install the driver locally from PyPI. To install for current user:

pip3 install adafruit-circuitpython-servokit
To install system-wide (this may be required in some cases):

OR

sudo pip3 install adafruit-circuitpython-servokit
To install in a virtual environment in your current project:

OR

mkdir project-name && cd project-name
python3 -m venv .venv
source .venv/bin/activate
pip3 install adafruit-circuitpython-servokit
