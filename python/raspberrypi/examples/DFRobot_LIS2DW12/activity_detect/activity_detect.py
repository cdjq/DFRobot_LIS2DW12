# -*- coding:utf-8 -*-
"""
   @file activity_detect.py
   @brief Motion detection,可以检测到模块是否在移动
   @n 使用此功能,需先进入低功耗模式,然后调用setActMode(),使芯片进入睡眠模式,此种状态下测量速率为12.5hz
   @n 当检测到某个方向的加速度变化大于阈值时测量速率会提升到设置的正常速率，阈值大小通过setWakeUpThreshold()函数设置
   @n 但如果停止运动即三个方向加速度的变化小于阈值芯片会在一段时间后进入进入睡模式,这个持续的时间由setWakeUpDur()函数设置
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


#如果你想要应IIC驱动此模块，打开下面三行的注释，并通过I2C连接好模块和树莓树莓派
#可通过板子上的拨码开关（gravity版本）或SDO引脚（Breakout版本）切换I2C地址
I2C_BUS         = 0x01             #default use I2C1
#ADDRESS_0       = 0x18             #传感器地址0
ADDRESS_1       = 0x19             #传感器地址1
acce = DFRobot_LIS2DW12_I2C(I2C_BUS ,ADDRESS_1)

#Chip initialization
acce.begin()
#Get chip id
print('chip id :%x'%acce.get_id())

'''
  Set the sensor measurement range:
              RANGE_2G     #±2g
              RANGE_4G     #±4g
              RANGE_8G     #±8g
              RANGE_16G    #±16g
'''
acce.set_range(acce.RANGE_2G)

'''
  Filter settings:
      LPF     #Low pass filter
      HPF     #High pass filter
'''
acce.set_filter_path(acce.LPF)

'''
   Set bandwidth
        RATE_DIV_2  #RATE/2 (up to RATE = 800 Hz, 400 Hz when RATE = 1600 Hz)
        RATE_DIV_4  #RATE/4 (High Power/Low power)
        RATE_DIV_10 #RATE/10 (HP/LP)
        RATE_DIV_20 #RATE/20 (HP/LP)
'''
acce.set_filter_bandwidth(acce.RATE_DIV_4)

'''
      唤醒持续时间,在setActMode()函数使用eDetectAct的检测模式时,芯片在被唤醒后,会持续一段时
    间以正常速率采集数据,然后便会继续休眠,以12.5hz的频率采集数据
     dur duration(0 ~ 3)
     time = dur * (1/rate)(unit:s)
     |                                    参数与时间之间的线性关系的示例                                                        |
     |------------------------------------------------------------------------------------------------------------------------|
     |                |                     |                          |                          |                           |
     |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
     |------------------------------------------------------------------------------------------------------------------------|
     |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
     |------------------------------------------------------------------------------------------------------------------------|
'''
acce.set_wakeup_dur(dur = 6)

#Set wakeup threshold,当加速度的变化大于此值时,会触发eWakeUp事件,unit:mg
#数值是在量程之内
acce.set_wakeup_threshold(2)

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
acce.set_power_mode(acce.CONT_LOWPWRLOWNOISE1_12BIT)

'''
    Set the mode of motion detection:
                 NO_DETECTION      #No detection
                 DETECT_ACT        #设置此模式,芯片的速率会降为12.5hz,并且在eWakeUp事件产生后,变为正常测量频率
                 DETECT_STATMOTION #此模式,仅能检测芯片是否处于睡眠模式,而不改变测量频率和电源模式,一直以正常测量频率测量数据
'''
acce.set_act_mode(acce.DETECT_ACT)

'''
  Set the interrupt source of the int1 pin:
          DOUBLE_TAP(Double click)
          FREEFALL(Free fall)
          WAKEUP(wake)
          SINGLE_TAP(single-Click)
          IA6D(Orientation change check)
'''
acce.set_int1_event(acce.WAKEUP)

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
acce.set_data_rate(acce.RATE_200HZ)
time.sleep(0.1)

while True:
    #Motion detected
    act = acce.act_detected()
    if act == True:
      print("Activity Detected")
    time.sleep(0.3)