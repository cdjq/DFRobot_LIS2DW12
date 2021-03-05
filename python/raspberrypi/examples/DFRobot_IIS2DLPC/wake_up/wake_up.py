# -*- coding:utf-8 -*-
"""
   @file wake_up.py
   @brief 当x,y,z中某个方向的加速度大于设置好的阈值时,芯片会产生wake-up事件，通过
   @访问芯片寄存器可以知道是从哪一个方向的运动唤醒了芯片
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
#可通过板子上的拨码开关（gravity版本）或SDO引脚（Breakout版本）切换I2C地址
I2C_BUS         = 0x01             #default use I2C1
#ADDRESS_0       = 0x18             #传感器地址0
ADDRESS_1       = 0x19             #传感器地址1
acce = DFRobot_IIS2DLPC_I2C(I2C_BUS ,ADDRESS_1)

#Chip initialization
acce.begin()
#Get chip id
print('chip id :%x'%acce.get_id())
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
'''
acce.set_data_rate(acce.RATE_200HZ)

'''
  Filter settings:
      LPF         = 0x00,/<Low pass filter>/
      HPF         = 0x10,/<High pass filter>/
'''
acce.set_filter_path(acce.LPF)
'''
  Set the wake-up duration:
     dur duration(0 ~ 3)
     time = dur * (1/rate)(unit:s)
     |                                  参数与时间之间的线性关系的示例                                                        |
     |------------------------------------------------------------------------------------------------------------------------|
     |                |                     |                          |                          |                           |
     |   frequen      |Data rate = 25 Hz    |   Data rate = 100 Hz     |  Data rate = 400 Hz      |   Data rate = 800 Hz      |
     |------------------------------------------------------------------------------------------------------------------------|
     |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
     |------------------------------------------------------------------------------------------------------------------------|
'''
acce.set_wakeup_dur(dur = 1)

'''
  Set the wake-up Threshold:
  unit(g),数值是在量程之内
'''
acce.set_wakeup_threshold(0.1)

'''
Set the interrupt source of the int1 pin:
      DOUBLE_TAP = 0x08   #Double-tap recognition is routed to INT1 pad
      FREEFALL = 0x10     #Free-fall recognition is routed to INT1 pad
      WAKEUP = 0x20       #Wakeup recognition is routed to INT1 pad
      SINGLE_TAP = 0x40   #Single-tap recognition is routed to INT1 pad.
      IA6D  = 0x80        #6D recognition is routed to INT1 pad
'''
acce.set_int1_event(acce.WAKEUP)
time.sleep(0.1)

while True:
    #Motion detected
    act = acce.act_detect()
    if act == True:
      print("Wake-Up event on:")
      #唤醒的运动方向检测
      direction = acce.get_wake_up_dir() 
      if direction == acce.DIR_Z:
         print("z direction")
      elif direction == acce.DIR_Y:
         print("y direction")
      elif direction == acce.DIR_X:
         print("x  direction")
      time.sleep(0.3)