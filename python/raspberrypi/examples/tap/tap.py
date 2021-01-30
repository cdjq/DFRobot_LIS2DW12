# -*- coding:utf-8 -*-
"""
   @file tap.py
   @brief Single click and double click detection
   @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   @licence     The MIT License (MIT)
   @author [fengli](li.feng@dfrobot.com)
   @version  V1.0
   @date  2021-01-16
   @get from https://www.dfrobot.com
   @https://github.com/DFRobot/DFRobot_IIS2DLPC
"""

import sys
sys.path.append("../..") # set system path to top

from DFRobot_IIS2DLPC import *
import time

# peripheral params
RASPBERRY_PIN_CS = 27              #Chip selection pin
I2C_MODE         = 0x01            # default use I2C1
ADDRESS_0        = 0x19

acce = DFRobot_IIS2DLPC_SPI(RASPBERRY_PIN_CS)
#
#acce = DFRobot_IIS2DLPC_I2C(I2C_MODE ,ADDRESS_0)
# clear screen

acce.begin()
print("chip id :")
print(acce.get_ID())
acce.soft_reset()
'''
    @brief Set the measurement range
    @param range:Range(g)
                 RANGE_2G     #/**<±2g>*/
                 RANGE_4G     #/**<±4g>*/
                 RANGE_8G     #/**<±8g>*/
                 RANGE_16G    #/**< ±16g>*/
'''
acce.set_range(acce.RANGE_2G)
acce.set_power_mode(acce.SING_LELOWPWR_12BIT)
acce.set_data_rate(acce.ODR_200HZ)


#Enable click detection in the X direction
acce.enable_tap_detection_on_z(True)
#Enable click detection in Y direction
acce.enable_tap_detection_on_y(True)
#Enable click detection in the Z direction
acce.enable_tap_detection_on_x(True)
#The threshold setting in the X direction is similar to the sensitivity of detection, the larger the value, the less sensitive (0~31)
acce.set_tap_threshold_on_x(4)
#The threshold setting in the Y direction is similar to the sensitivity of detection, the larger the value, the less sensitive (0~31)
acce.set_tap_threshold_on_z(4)
#The threshold setting in the Z direction is similar to the sensitivity of detection, the larger the value, the less sensitive (0~31)
acce.set_tap_threshold_on_z(4)

acce.set_tap_dur(7)
acce.set_tap_mode(acce.BOTH_SINGLE_DOUBLE);

acce.set_int1_route(acce.DOUBLE_TAP);
time.sleep(0.1)

while True:
    #Get the acceleration in the three directions of xyz
    time.sleep(0.3)
    event = acce.tap_detect()
    direction = acce.get_tap_direction()
    if event == acce.SINGLE_TAP:
      print ("Tap Detected :")
    elif event == acce.DOUBLE_TAP:
      print ("Double Tap Detected :")
    
    if direction == acce.DIR_X_UP:
      print("Click it in the positive direction of x")
    elif orient == acce.DIR_X_DOWN:
      print("Click it in the negative direction of x")
    elif orient == acce.DIR_Y_UP:
      print("Click it in the positive direction of y")
    elif orient == acce.DIR_Y_DOWN:
      print("Click it in the negative direction of y")
    elif orient == acce.DIR_Z_UP:
      print("Click it in the positive direction of z")
    elif orient == acce.DIR_Z_DOWN:
      print("Click it in the negative direction of z")
      

        