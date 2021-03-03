# -*- coding:utf-8 -*-
"""
   @file get_acceleration.py
   @brief Get the acceleration in x, y, z directions
   @n 在使用SPI时,片选引脚时可以通过改变RASPBERRY_PIN_CS的值修改
   @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   @licence     The MIT License (MIT)
   @author [fengli](li.feng@dfrobot.com)
   @version  V1.0
   @date  2021-01-16
   @get from https://www.dfrobot.com
   @https://github.com/DFRobot/DFRobot_LIS2DW12
"""

import sys
sys.path.append("../../..") # set system path to top

from DFRobot_LIS2DW12 import *
import time

#如果你想要用SPI驱动此模块，打开下面两行的注释,并通过SPI连接好模块和树莓派
#RASPBERRY_PIN_CS =  27              #Chip selection pin when SPI is selected
#acce = DFRobot_IIS2DLPC_SPI(RASPBERRY_PIN_CS)

#如果你想要应IIC驱动此模块，打开下面三行的注释，并通过I2C连接好模块和树莓派
I2C_BUS         = 0x01             #default use I2C1
ADDRESS         = 0x19             #I2C address
acce = DFRobot_IIS2DLPC_I2C(I2C_BUS ,ADDRESS)


acce.begin()
print("chip id :")
print(acce.get_id())
#Software reset to restore the value of all registers
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
#Choose whether to continuously let the chip collect data
acce.contin_refresh(True)
'''
    Set the sensor data collection rate:
    ODR_OFF            = 0X00
    ODR_1HZ6_LP_ONLY   = 0X01
    ODR_12HZ5          = 0X02
    ODR_25HZ           = 0X03
    ODR_50HZ           = 0X04
    ODR_100HZ          = 0X05
    ODR_200HZ          = 0X06
    ODR_400HZ          = 0X07
    ODR_800HZ          = 0X08
    ODR_1K6HZ          = 0X09
    SETSWTRIG          = 0X12
    SETPINTRIG         = 0X22
'''
acce.set_data_rate(acce.ODR_200HZ)

'''
  Filter settings:
      LPF_ON_OUT        = 0x00,/<Low pass filter>/
      HIGH_PASS_ON_OUT   = 0x10,/<High pass filter>/
'''
acce.set_filter_path(acce.LPF_ON_OUT)

'''
   Set bandwidth
        ODR_DIV_2     = 0,/<ODR/2 (up to ODR = 800 Hz, 400 Hz when ODR = 1600 Hz)>/
        ODR_DIV_4     = 1,/<ODR/4 (High Power/Low power)>*
        ODR_DIV_10    = 2,/<ODR/10 (HP/LP)>/
        ODR_DIV_20    = 3,/< ODR/20 (HP/LP)>/
'''
acce.set_filter_bandwidth(acce.ODR_DIV_4)
'''
   Set power mode:
                 HIGH_PERFORMANCE                   = 0X04 #High-Performance Mode
                 CONT_LOWPWR_4                      = 0X03#Continuous measurement,Low-Power Mode 4(14-bit resolution)
                 CONT_LOWPWR_3                      = 0X02#Continuous measurement,Low-Power Mode 3(14-bit resolution)
                 CONT_LOWPWR_2                      = 0X01#Continuous measurement,Low-Power Mode 2(14-bit resolution)
                 CONT_LOWPWR_12BIT                  = 0X00#Continuous measurement,Low-Power Mode 1(12-bit resolution)
                 SING_LELOWPWR_4                    = 0X0B#Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)
                 SING_LELOWPWR_3                    = 0X0A#Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution
                 SING_LELOWPWR_2                    = 0X09#Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)
                 SING_LELOWPWR_12BIT                = 0X08#Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)
                 HIGHP_ERFORMANCELOW_NOISE           = 0X14#High-Performance Mode,Low-noise enabled
                 CONT_LOWPWRLOWNOISE_4              = 0X13#Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)
                 CONT_LOWPWRLOWNOISE_3              = 0X12#Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)
                 CONT_LOWPWRLOWNOISE_2              = 0X11#Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)
                 CONT_LOWPWRLOWNOISE_12BIT          = 0X10#Continuous measurement,Low-Power Mode 1(14-bit resolution,Low-noise enabled)
                 SINGLE_LOWPWRLOWNOISE_4            = 0X1B#Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled
                 SINGLE_LOWPWRLOWNOISE_3            = 0X1A#Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled
                 SINGLE_LOWPWRLOWNOISE_2            = 0X19#Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled
                 SINGLE_LOWLOWNOISEPWR_12BIT        = 0X18#Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled
'''
acce.set_power_mode(acce.CONT_LOWPWRLOWNOISE_2);
time.sleep(0.1)

while True:
    #Get the acceleration in the three directions of xyz
    time.sleep(0.3)
    x = acce.read_acc_x()
    y = acce.read_acc_y()
    z = acce.read_acc_z()
    print("Acceleration [X = %.2d mg,Y = %.2d mg,Z = %.2d mg]"%(x,y,z))
