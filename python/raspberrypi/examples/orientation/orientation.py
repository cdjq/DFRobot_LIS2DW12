# -*- coding:utf-8 -*-
"""
   @file orientation.py
   @brief Detect the movement of the module in six directions. When the module turns from another direction to a certain direction, an event will be triggered and then detected
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


acce.set_6d_threshold(acce.DEGREES_60);
acce.set_int1_route(acce.TNT_16D);




time.sleep(0.1)

while True:
    #Get the acceleration in the three directions of xyz
    time.sleep(0.3)
    if acce.ia6d_detect() == True:
      '''
        X_DOWN = 0 #/**<X is now down>*/
        X_UP  = 1 #/**<X is now up>*/
        Y_DOWN = 2 #/**<Y is now down>*/
        Y_UP = 3  #/**<Y is now up>*/
        Z_DOWN = 4  #/**<Z is now down>*/
        Z_UP = 5  #/**<Z is now up>*/
      '''
      orient = acce.get_orient()
      if orient == acce.X_DOWN:
        print("X is now down")
      elif orient == acce.X_UP:
        print("X is now up")
      elif orient == acce.Y_DOWN:
        print("Y is now down")
      elif orient == acce.Y_UP:
        print("Y is now up")
      elif orient == acce.Z_DOWN:
        print("Z is now down")
      elif orient == acce.Z_UP:
        print("Z is now up")
