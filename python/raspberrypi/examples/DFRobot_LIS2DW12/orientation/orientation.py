# -*- coding:utf-8 -*-
"""
   @file orientation.py
   @brief 检测模块的朝向,传感器能检测到以下六种事件：
   @n Z轴正向朝上
   @n Z轴正向朝下
   @n Y轴正向朝上
   @n Y轴正向朝下
   @n X轴正向朝上
   @n X轴正向朝下
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
#acce = DFRobot_LIS2DW12_SPI(RASPBERRY_PIN_CS)


#如果你想要应IIC驱动此模块，打开下面三行的注释，并通过I2C连接好模块和树莓派
#可通过板子上的拨码开关（gravity版本）或SDO引脚（Breakout版本）切换I2C地址
I2C_BUS         = 0x01             #default use I2C1
#ADDRESS_0       = 0x18             #传感器地址0
ADDRESS_1       = 0x19             #传感器地址1
acce = DFRobot_LIS2DW12_I2C(I2C_BUS ,ADDRESS_1)

#Chip initialization
acce.begin()
#Get chip id
print('chip id :%x'%acce.get_id())
#Software reset to restore the value of all registers
acce.soft_reset()
'''
  Set the sensor measurement range:
              RANGE_2G     #±2g
              RANGE_4G     #±4g
              RANGE_8G     #±8g
              RANGE_16G    #±16g
'''
acce.set_range(acce.RANGE_2G)
'''
   Set power mode:
               HIGH_PERFORMANCE_14BIT                   = 0X04#High-Performance Mode
               CONT_LOWPWR4_14BIT                      = 0X03#Continuous measurement,Low-Power Mode 4(14-bit resolution)
               CONT_LOWPWR3_14BIT                      = 0X02#Continuous measurement,Low-Power Mode 3(14-bit resolution)
               CONT_LOWPWR2_14BIT                      = 0X01#Continuous measurement,Low-Power Mode 2(14-bit resolution)
               CONT_LOWPWR1_12BIT                  = 0X00#Continuous measurement,Low-Power Mode 1(12-bit resolution)
               SING_LELOWPWR4_14BIT                    = 0X0B#Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)
               SING_LELOWPWR3_14BIT                    = 0X0A#Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution
               SING_LELOWPWR2_14BIT                    = 0X09#Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)
               SING_LELOWPWR1_12BIT                = 0X08#Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)
               HIGHP_ERFORMANCELOW_NOISE_14BIT           = 0X14#High-Performance Mode,Low-noise enabled
               CONT_LOWPWRLOWNOISE4_14BIT              = 0X13#Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)
               CONT_LOWPWRLOWNOISE3_14BIT              = 0X12#Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)
               CONT_LOWPWRLOWNOISE2_14BIT              = 0X11#Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)
               CONT_LOWPWRLOWNOISE1_12BIT          = 0X10#Continuous measurement,Low-Power Mode 1(14-bit resolution,Low-noise enabled)
               SINGLE_LOWPWRLOWNOISE4_14BIT            = 0X1B#Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled
               SINGLE_LOWPWRLOWNOISE3_14BIT            = 0X1A#Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled
               SINGLE_LOWPWRLOWNOISE2_14BIT            = 0X19#Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled
               SINGLE_LOWLOWNOISEPWR1_12BIT        = 0X18#Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled
'''
acce.set_power_mode(acce.CONT_LOWPWRLOWNOISE1_12BIT)
'''
    Set the sensor data collection rate:
        RATE_OFF            #测量关闭
        RATE_1HZ6_LP_ONLY   #1.6hz
        RATE_12HZ5          #12.5hz
        RATE_25HZ           
        RATE_50HZ           
        RATE_100HZ          
        RATE_200HZ          
        RATE_400HZ          
        RATE_800HZ          
        RATE_1K6HZ          
        SETSWTRIG           #软件触发单次测量
'''
acce.set_data_rate(acce.RATE_200HZ)
'''
  Set Thresholds for 4D/6D，当转动的阈值大于指定角度时,就发生方向转变的事件
  degree:         DEGREES_80   (80°)
                  DEGREES_70   (70°)
                  DEGREES_60   (60°)
                  DEGREES_50   (50°)
'''
acce.set_6d_threshold(acce.DEGREES_60)

'''
Set the interrupt source of the int1 pin:
              DOUBLE_TAP = 0x08   #Double-tap recognition is routed to INT1 pad
              FREEFALL = 0x10     #Free-fall recognition is routed to INT1 pad
              WAKEUP = 0x20 #Wakeup recognition is routed to INT1 pad
              SINGLE_TAP = 0x40   #Single-tap recognition is routed to INT1 pad.
              IA6D  = 0x80     #6D recognition is routed to INT1 pad
'''
acce.set_int1_event(acce.IA6D)
time.sleep(0.1)

while True:
    #Get the acceleration in the three directions of xyz
    #time.sleep(0.01)
    if acce.ia_6d_detect() == True:
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
