import pycom
import time
import machine
from machine import ADC

pycom.heartbeat(False)

# =========================================== ADC Calibration Begin: ===========================================
# ESP32 ADC is not calibrated from factory, hence, must calibrate each time to use it.

#Firstly measure the internal voltage reference:
def calibration_procedure_step_1(adc, sleepsecs):
    #The following code will connect the internal 1.1v reference to P22:
    #adc = ADC()
    #Connects internal 1.1v to external GPIO P22
    adc.vref_to_pin('P22')
    #Now the voltage reference is externally accessible, allowing to measure it with voltmeter (e.g. 1120mv).
    time.sleep(sleepsecs) #Sleep *sleepsecs* seconds before reset
    #Reset module to disconnect 1.1v reference from P22.
    machine.reset()

#Afterwards, calibrate ADC with value of internal reference:
def calibration_procedure_step_2(adc, pin='P22', vref=1120):
    #adc = ADC()
    #Called without any arguments, returns current calibrated voltage (mv) of 1.1v reference.
    print("VREF = {}mv".format(adc.vref()))
    #Otherwise, update the calibrated value (in millivolts) of internal 1.1v reference.
    # Set calibration to 1120mv
    adc.vref(vref)
    #Then check calibration by reading a known voltage source
    #    pin is a keyword-only string argument (valid pins: P13 to P20).
    #    attn is the attenuation level (supported values: ADC.ATTN_0DB, ADC.ATTN_2_5DB, ADC.ATTN_6DB, ADC.ATTN_11DB).
    # NB: ADC pin input range is 0-1.1V. This maximum value can be increased up to 3.3V using the 
    # highest attenuation of 11dB (do not exceed the maximum of 3.3V, to avoid damaging the device).
    adc_pin = adc.channel(pin=pin, attn=ADC.ATTN_11DB)
    print("Pin16 voltage measure = {} mv".format(adc_pin.voltage()))
    return adc_pin16
# =========================================== ADC Calibration End ===========================================

# Light measurment from a Pin
def read_light_sensor(adc_pin):
    print("")
    print("Reading LDR Sensor...")
    value = adc_pin()
    print("ADC value = %d" % (value))
    # LoPy has 1.1 V input range for ADC
    light = value
    print("light = %5.1f" % (light))
    return light


""" To stop the script, click onto the Pymakr terminal, and press ctrl-c on your keyboard. """ 
#Create an ADC object (associate a channel with a pin)
adc = ADC(0)
#General procedure for reading an adc pin: create channel, read and print
#adc_pin16 = adc.channel(pin='P13') #Create analog pin on gpio P16
#adc_pin16() #Read pin13
#print("P16 reading value = {}".format(adc_pin16.value()))

#Calibate ADC...
#Step 1: expose internal vref and reboot afterwards
calibration_procedure_step_1(adc)

#Step 2: update calibrated vref with previoulsy read value 
vref = 1120
adc_pin16 = calibration_procedure_step_2(adc, vref)

#Now create channel and read and print LDR sensor
read_light_sensor(adc_pin16)

