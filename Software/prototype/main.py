# A program that reads the values from a phototransistor via a ADC
# Author: Kris Miedema
# Date 12/10/21
# Based on 
#   Derek Schuurman
#   Lab 4: Program to continuously read A/D converter and log data

import Adafruit_MCP3008
import signal
from datetime import datetime

# Constants
SAMPLE_TIME = 0.010
A2D_CHANNEL = 0
FILENAME = 'datalog.csv'

# SPI pin assignments
CLK = 25
MISO = 24
MOSI = 23
CS = 18

# Instantiate a new A/D object
a2d = Adafruit_MCP3008.MCP3008(clk=CLK, cs=CS, miso=MISO, mosi=MOSI)

# Open a data logging file
f = open(FILENAME,'w')

# timer signal callback
def handler(signum, frame):
    ''' Timer signal handler
    '''
    value = a2d.read_adc(A2D_CHANNEL)
    time = datetime.now().time()
    f.write('{},{}\n'.format(time,value))

# Setup interval timer signal every sample time
signal.signal(signal.SIGALRM, handler)
signal.setitimer(signal.ITIMER_REAL, 1, SAMPLE_TIME)

print('Press Ctrl-C to quit...')
try:
    while True:
        signal.pause()
except KeyboardInterrupt:
    signal.setitimer(signal.ITIMER_REAL, 0, 0)
    # Cancel inteval timer
    f.close()
    print('Done')
