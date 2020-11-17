import pycom
import time

"""
 * The main.py script runs directly after boot.py and should contain the main code to run on device.
 * - The code may be executed with the *run* command;
 * - The code will not remain on the device permanently (reboot will be wiped it);
 * - We may upload it permanently using *upload* command.
 * - The code will only work with libraries available in the firmware;
 * 
 * To remove files from device:
 * i) connect via FTP and manage files;
 * ii) format the device’s internal flash python script:
 * >>> import os
 * >>> os.mkfs('/flash')
 * 
 * //======= RESET from within a script: =======
 * //Soft reset clears the state of the MicroPython VM but leaves hardware peripherals unaffected.
 * //On REPL (Read–Eval–Print Loop):
 * >>> Ctrl+D
 * //Or run:
 * >>> import sys
 * >>> sys.exit()
 *
 * //======= HARD reset is the same as performing a power cycle to the device =======
 * //Press reset switch or run:
 * >>> import machine
 * >>> machine.reset()
 *
 """

""" To change the colour of onboard LED we need to disable the heart beat. """
pycom.heartbeat(False)

""" After *run*, to stop the script, click onto Pymakr terminal and press ctrl-c. """ 
while True:
    pycom.rgbled(0xFF0000)  # Red
    time.sleep(1)
    pycom.rgbled(0x00FF00)  # Green
    time.sleep(1)
    pycom.rgbled(0x0000FF)  # Blue
    time.sleep(1)