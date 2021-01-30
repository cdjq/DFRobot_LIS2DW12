# -*- coding:utf-8 -*-
"""
   @file DFRobot_IIS2DLPC.py
   @brief Get the acceleration in x, y, z directions
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

#acce = DFRobot_IIS2DLPC_SPI(RASPBERRY_PIN_CS)
#
acce = DFRobot_IIS2DLPC_I2C(I2C_MODE ,ADDRESS_0)
# clear screen

acce.begin()
print("chip id :")
print(acce.getID())
acce.soft_reset()

acce.contin_refresh(True)
acce.set_power_mode(acce.CONT_LOWPWR_4);
acce.set_data_rate(DFRobot_IIS2DLPC::ODR_100HZ);
'''
  @brief Set the measurement range
  @param range:Range(g)
               RANGE_2G     #/**<±2g>*/
               RANGE_4G     #/**<±4g>*/
               RANGE_8G     #/**<±8g>*/
               RANGE_16G    #/**< ±16g>*/
'''
acce.set_range(acce.RANGE_2G)
cce.setFrDur(0x06);

acce.set_int1_route(DFRobot_IIS2DLPC::WAKEUP_EVENT);
acce.latchInterrupt(True);


time.sleep(0.1)

while True:
    #Get the acceleration in the three directions of xyz
    time.sleep(0.3)
    free_fall = free_fall_detect()
    if free_fall == True:
      print("free fall detected");
