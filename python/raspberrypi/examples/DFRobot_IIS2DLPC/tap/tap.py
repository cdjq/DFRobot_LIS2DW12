# -*- coding:utf-8 -*-
"""
   @file tap.py
   @brief Single tap and double tap detection,点击模块，或者点击模块附件的桌面都可以触发点击事件
   @n 可以通过set_tap_mode()函数选择只检测单击，或单击和双击同时检测
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
    Set the sensor data collection rate:
        RATE_OFF            #测量关闭
        RATE_1HZ6           #1.6hz,仅在低功耗模式下使用
        RATE_12HZ5          #12.5hz
        RATE_25HZ           
        RATE_50HZ           
        RATE_100HZ          
        RATE_200HZ          
        RATE_400HZ          
        RATE_800HZ          
        RATE_1600HZ          
        SETSWTRIG           #软件触发单次测量
'''
acce.set_data_rate(acce.RATE_800HZ)

#Enable tap detection in the X direction
acce.enable_tap_detection_on_z(True)
#Enable tap detection in Y direction
acce.enable_tap_detection_on_y(True)
#Enable tap detection in the Z direction
acce.enable_tap_detection_on_x(True)
#The threshold setting in the X direction is similar to the sensitivity of detection, the larger the value, the less sensitive (0~31)
acce.set_tap_threshold_on_x(0.5)
#The threshold setting in the Y direction is similar to the sensitivity of detection, the larger the value, the less sensitive (0~31)
acce.set_tap_threshold_on_y(0.5)
#The threshold setting in the Z direction is similar to the sensitivity of detection, the larger the value, the less sensitive (0~31)
acce.set_tap_threshold_on_z(0.5)
'''
   双击的两次点击之间的间隔时间：
   dur duration(0 ~ 15)
   time = dur * (1/rate)(unit:s)
   |                                    参数与时间之间的线性关系的示例                                                        |
   |------------------------------------------------------------------------------------------------------------------------|
   |                |                     |                          |                          |                           |
   |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
   |------------------------------------------------------------------------------------------------------------------------|
   |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
   |------------------------------------------------------------------------------------------------------------------------|
'''
acce.set_tap_dur(dur = 3)

'''
  Set the tap detection mode:
      ONLY_SINGLE   //检测单击
      BOTH_SINGLE_DOUBLE //检测单击和双击
'''
acce.set_tap_mode(acce.BOTH_SINGLE_DOUBLE)

'''
  Set the interrupt source of the int1 pin:
          DOUBLE_TAP(Double tap)
          FREEFALL(Free fall)
          WAKEUP(wake)
          SINGLE_TAP(single-tap)
          IA6D(Orientation change check)
'''
acce.set_int1_event(acce.DOUBLE_TAP)
time.sleep(0.1)

while True:
    tap = False
    #点击检测
    event = acce.tap_detect()
    #点击的源头检测
    direction = acce.get_tap_direction()
    if event == acce.S_TAP:
      print ("Tap Detected :")
      tap = True
    elif event == acce.D_TAP:
      print ("Double Tap Detected :")
      tap = True
    if tap == True:
      if direction == acce.DIR_X_UP:
        print("tap it in the positive direction of x")
      elif direction == acce.DIR_X_DOWN:
        print("tap it in the negative direction of x")
      elif direction == acce.DIR_Y_UP:
        print("tap it in the positive direction of y")
      elif direction == acce.DIR_Y_DOWN:
        print("tap it in the negative direction of y")
      elif direction == acce.DIR_Z_UP:
        print("tap it in the positive direction of z")
      elif direction == acce.DIR_Z_DOWN:
        print("tap it in the negative direction of z")
      tap = False
      

        