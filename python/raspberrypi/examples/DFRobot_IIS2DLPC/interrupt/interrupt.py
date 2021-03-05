# -*- coding:utf-8 -*-
"""
   @file interrupt.py
   @brief  Interrupt detection of free fall,当有自由落体事件产生会在int1产生中断信号
   @n 检测到有自由落体运动产生，会在终端打印显示
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

INT1 = 26                           #Interrupt pin
int_pad_Flag = False                 #intPad flag
def int_pad_callback(status):
  global int_pad_Flag
  int_pad_Flag = True

#如果你想要用SPI驱动此模块，打开下面两行的注释,并通过SPI连接好模块和树莓派
#RASPBERRY_PIN_CS =  27              #Chip selection pin when SPI is selected
#acce = DFRobot_IIS2DLPC_SPI(RASPBERRY_PIN_CS)

#如果你想要应IIC驱动此模块，打开下面三行的注释，并通过I2C连接好模块和树莓派
#可通过板子上的拨码开关（gravity版本）或SDO引脚（Breakout版本）切换I2C地址
I2C_BUS         = 0x01             #default use I2C1
#ADDRESS_0       = 0x18             #传感器地址0
ADDRESS_1       = 0x19             #传感器地址1
acce = DFRobot_IIS2DLPC_I2C(I2C_BUS ,ADDRESS_1)

# set int_Pad to input
GPIO.setup(INT1, GPIO.IN)
#set int_Pad interrupt callback
GPIO.add_event_detect(INT1,GPIO.RISING,int_pad_callback)

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
acce.set_power_mode(acce.CONT_LOWPWR4_14BIT);
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
acce.set_data_rate(acce.RATE_100HZ);
'''
  Set the measurement range：
               RANGE_2G     #/**<±2g>*/
               RANGE_4G     #/**<±4g>*/
               RANGE_8G     #/**<±8g>*/
               RANGE_16G    #/**< ±16g>*/
'''
acce.set_range(acce.RANGE_2G)
'''
  设置自由落体时间,也可以称作自由落体样本个数，只有产生足够多的自由落体样本，才会产生自由落体事件:
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
acce.set_free_fall_Dur(dur = 6)
'''
  Set the interrupt source of the int1 pin:
              DOUBLE_TAP = 0x08   #Double-tap recognition is routed to INT1 pad
              FREEFALL = 0x10     #Free-fall recognition is routed to INT1 pad
              WAKEUP = 0x20 #Wakeup recognition is routed to INT1 pad
              SINGLE_TAP = 0x40   #Single-tap recognition is routed to INT1 pad.
              IA6D  = 0x80     #6D recognition is routed to INT1 pad


'''
acce.set_int1_event(acce.FREEFALL)
#lock interrupt
acce.lock_interrupt(True);


time.sleep(0.1)

while True:
  if(int_pad_Flag == True):
    #Free fall event is detected
    free_fall = acce.free_fall_detect()
    if free_fall == True:
      print("free fall detected")
      time.sleep(0.3)
    int_pad_Flag = False
