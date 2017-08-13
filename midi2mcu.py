#!/usr/bin/env python

"""Contains an example of midi input, and a separate example of midi output.
By default it runs the output example.
python midi.py --output
python midi.py --input
"""

import sys
import os
import serial

import pygame
import pygame.midi
from pygame.locals import *

try:  # Ensure set available for output example
    set
except NameError:
    from sets import Set as set


def print_device_info():
    pygame.midi.init()
    _print_device_info()
    pygame.midi.quit()

def _print_device_info():
    for i in range( pygame.midi.get_count() ):
        r = pygame.midi.get_device_info(i)
        (interf, name, input, output, opened) = r

        in_out = ""
        if input:
            in_out = "(input)"
        if output:
            in_out = "(output)"

        print ("%2i: interface :%s:, name :%s:, opened :%s:  %s" %
               (i, interf, name, opened, in_out))
        



def input_main(device_id = None):
    pygame.init()
    pygame.fastevent.init()
    event_get = pygame.fastevent.get
    event_post = pygame.fastevent.post

    pygame.midi.init()

    _print_device_info()


    if device_id is None:
        input_id = pygame.midi.get_default_input_id()
    else:
        input_id = device_id

    print ("using input_id :%s:" % input_id)
    i = pygame.midi.Input( input_id )

    pygame.display.set_mode((1,1))



    going = True
    while going:
        events = event_get()
        for e in events:
            if e.type in [QUIT]:
                going = False
            if e.type in [KEYDOWN]:
                going = False
            if e.type in [pygame.midi.MIDIIN]:
                print (e)

        if i.poll():
            midi_events = i.read(10)

#            print midi_events[0][0]

            if (port.isOpen()):
                print "[%d, %d, %d]" % (midi_events[0][0][0], midi_events[0][0][1], midi_events[0][0][2])
                for j in range(3):
                    port.write(chr(midi_events[0][0][j]))
                    
                    
            # convert them into pygame events.
#            midi_evs = pygame.midi.midis2events(midi_events, i.device_id)
#            for m_e in midi_evs:
#                print "EVENT:  "
#                event_post( m_e )


    del i
    pygame.midi.quit()


def main(mode='output', device_id=None):
    """Run a Midi example
    Arguments:
    mode - if 'output' run a midi keyboard output example
              'input' run a midi event logger input example
              'list' list available midi devices
           (default 'output')
    device_id - midi device number; if None then use the default midi input or
                output device for the system
    """

    input_main(device_id)

if __name__ == '__main__':
    # configure the serial connections (the parameters differs on the device you are connecting to)
    port = serial.Serial(port = "/dev/tty.usbmodem1471061", baudrate = 2000000, writeTimeout = 0)
    port.close()
    port.open()

    #find midi device
    try:
        device_id = int( sys.argv[-1] )
    except:
        device_id = None

        input_main(device_id)
