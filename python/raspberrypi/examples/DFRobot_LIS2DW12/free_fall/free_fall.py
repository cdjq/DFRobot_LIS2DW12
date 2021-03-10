# -*- coding:utf-8 -*-
"""
   @file free_fall.py
   @brief  Sensor module free fall detection,通过set_free_fall_Dur()函数设置自由落体时间,调节检测的灵敏度,自由落体时间越短,自由落体时间越容易发生
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
#Choose whether to continuously let the chip collect data
acce.contin_refresh(True)

'''
   Set power mode:
       HIGH_PERFORMANCE_14BIT           #High-Performance Mode
       CONT_LOWPWR4_14BIT               #Continuous measurement,Low-Power Mode 4(14-bit resolution)
       CONT_LOWPWR3_14BIT               #Continuous measurement,Low-Power Mode 3(14-bit resolution)
       CONT_LOWPWR2_14BIT               #Continuous measurement,Low-Power Mode 2(14-bit resolution)
       CONT_LOWPWR1_12BIT               #Continuous measurement,Low-Power Mode 1(12-bit resolution)
       SING_LELOWPWR4_14BIT             #Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)
       SING_LELOWPWR3_14BIT             #Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution
       SING_LELOWPWR2_14BIT             #Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)
       SING_LELOWPWR1_12BIT             #Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)
       HIGHP_ERFORMANCELOW_NOISE_14BIT  #High-Performance Mode,Low-noise enabled
       CONT_LOWPWRLOWNOISE4_14BIT       #Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)
       CONT_LOWPWRLOWNOISE3_14BIT       #Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)
       CONT_LOWPWRLOWNOISE2_14BIT       #Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)
       CONT_LOWPWRLOWNOISE1_12BIT       #Continuous measurement,Low-Power Mode 1(14-bit resolution,Low-noise enabled)
       SINGLE_LOWPWRLOWNOISE4_14BIT     #Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled
       SINGLE_LOWPWRLOWNOISE3_14BIT     #Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled
       SINGLE_LOWPWRLOWNOISE2_14BIT     #Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled
       SINGLE_LOWPWRLOWNOISE1_12BIT     #Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled
'''
acce.set_power_mode(acce.CONT_LOWPWR4_14BIT);
'''
    Set the sensor data collection rate:
        RATE_OFF            #测量关闭
        RATE_1HZ6           #1.6hz,仅在低功耗模式下使用
        RATE_12HZ5          #12.5hz
        RATE_25HZ           
        RATE_50HZ           
        RATE_100HZ          
        RATE_200HZ          
        RATE_400HZ          #仅在High-Performance mode下使用
        RATE_800HZ          #仅在High-Performance mode下使用
        RATE_1600HZ         #仅在High-Performance mode下使用
        SETSWTRIG           #软件触发单次测量
'''
acce.set_data_rate(acce.RATE_100HZ);
'''
   Set the measurement range
               RANGE_2G     #±2g
               RANGE_4G     #±4g
               RANGE_8G     #±8g
               RANGE_16G    #±16g
'''
acce.set_range(acce.RANGE_2G)
'''
  设置自由落体时间,也可以称作自由落体样本个数，只有产生足够多的自由落体样本，才会产生自由落体事件:
     dur duration(0 ~ 31)
     time = dur * (1/rate)(unit:s)
     |                                    参数与时间之间的线性关系的示例                                                        |
     |------------------------------------------------------------------------------------------------------------------------|
     |                |                     |                          |                          |                           |
     |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
     |------------------------------------------------------------------------------------------------------------------------|
     |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
     |------------------------------------------------------------------------------------------------------------------------|
'''
acce.set_free_fall_Dur(dur = 0x06)

'''
  Set the interrupt source of the int1 pin:
          DOUBLE_TAP(Double click)
          FREEFALL(Free fall)
          WAKEUP(wake)
          SINGLE_TAP(single-Click)
          IA6D(Orientation change check)
'''
acce.set_int1_event(acce.FREEFALL)
time.sleep(0.1)

while True:
    #Free fall event is detected
    free_fall = acce.free_fall_detected()
    if free_fall == True:
      print("free fall detected")
      time.sleep(0.3)
