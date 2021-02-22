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
   @https://github.com/DFRobot/DFRobot_LIS2DW12
"""

import sys
sys.path.append("../../..") # set system path to top

from DFRobot_LIS2DW12 import *
import time

#如果你想要用SPI驱动此模块，打开下面两行的注释,并通过SPI连接好模块和树莓派
#RASPBERRY_PIN_CS =  27              #Chip selection pin when SPI is selected
#acce = DFRobot_IIS2DLPC_SPI(RASPBERRY_PIN_CS)


#如果你想要应IIC驱动此模块，打开下面三行的注释，并通过I2C连接好模块和树莓树莓派
I2C_MODE         = 0x01             #default use I2C1
ADDRESS_0        = 0x19             #I2C address
acce = DFRobot_IIS2DLPC_I2C(I2C_MODE ,ADDRESS_0)



acce.begin()
print("chip id :")
print(acce.get_ID())
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
acce.set_power_mode(acce.CONT_LOWPWRLOWNOISE_12BIT)
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
  Set Thresholds for 4D/6D，当转动的阈值大于指定角度时,就发生方向转变的事件
  degree:  DEGREES_80   80°
                  DEGREES_70   70°
                  DEGREES_60   60°
                  DEGREES_50   50°
'''
acce.set_6d_threshold(acce.DEGREES_60)

'''
Set the interrupt source of the int1 pin:
        DOUBLE_TAP = 0x08 #/**< Double-tap recognition is routed to INT1 pad>*/
        FF_EVENT = 0x10 #/**< Free-fall recognition is routed to INT1 pad>*/
        WAKEUP_EVENT = 0x20 #/**<Wakeup recognition is routed to INT1 pad>*/
        SINGLE_TAP = 0x40  #/**<Single-tap recognition is routed to INT1 pad.>*/
        TNT_16D  = 0x80  #/**<6D recognition is routed to INT1 pad>*/

'''
acce.set_int1_route(acce.TNT_16D)




time.sleep(0.1)

while True:
    #Get the acceleration in the three directions of xyz
    #time.sleep(0.01)
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
