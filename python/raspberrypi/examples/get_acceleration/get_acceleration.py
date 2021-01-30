# -*- coding:utf-8 -*-
"""
   @file get_acceleration.py
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
acce.contin_refresh(True)
acce.set_data_rate(acce.ODR_200HZ);
acce.set_filter_path(acce.LPF_ON_OUT)
acce.set_filter_bandwidth(acce.ODR_DIV_4)

acce.set_power_mode(acce.SING_LELOWPWR_12BIT);




time.sleep(0.1)

while True:
    #Get the acceleration in the three directions of xyz
    time.sleep(0.3)
    x = acce.read_acc_x()
    y = acce.read_acc_y()
    z = acce.read_acc_z()
    print("Acceleration [X = %.2d mg,Y = %.2d mg,Z = %.2d mg]"%(x,y,z))
