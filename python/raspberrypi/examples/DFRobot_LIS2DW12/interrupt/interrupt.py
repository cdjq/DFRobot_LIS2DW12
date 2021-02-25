# -*- coding:utf-8 -*-
"""
   @file interrupt.py
   @brief  当传感器发生自由落体事件时，会在int1脚产生中断
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
#acce = DFRobot_LIS2DW12_SPI(RASPBERRY_PIN_CS)


#如果你想要应IIC驱动此模块，打开下面三行的注释，并通过I2C连接好模块和树莓树莓派
I2C_BUS         = 0x01             #default use I2C1
ADDRESS         = 0x19             #I2C address
acce = DFRobot_LIS2DW12_I2C(I2C_BUS ,ADDRESS)

#set int_Pad interrupt callback
acce.attach_interrupt(INT1, int_pad_callback,RPIGPIO.RISING) 

acce.begin()
print("chip id :")
print(acce.get_id())
#Software reset to restore the value of all registers
acce.soft_reset()
#Choose whether to continuously let the chip collect data
acce.contin_refresh(True)
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
acce.set_power_mode(acce.CONT_LOWPWR_4);
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
acce.set_data_rate(acce.ODR_100HZ);
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
  @brief 设置自由落体时间
  @param dur  Free fall duration (0~31), the larger the value, the longer the free fall time is needed to be detected
  @n 1 LSB = 1 * 1/ODR (measurement frequency)
  @n example
  |                           High-pass filter cut-off frequency configuration                             |
  |--------------------------------------------------------------------------------------------------------|
  |                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
  |   dur          |Data rate = 25 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 800 Hz  |
  |--------------------------------------------------------------------------------------------------------|
  |  n             |n*(1s/25)= n*40ms|  n*(1s/100)= n*10ms  |  n*(1s/400)= 2.5*nms |  n*(1s/800)= n*1.25ms |
  |--------------------------------------------------------------------------------------------------------|
'''
acce.set_ff_Dur(0x06)
'''
Set the interrupt source of the int1 pin:
        DOUBLE_TAP = 0x08 #/**< Double-tap recognition is routed to INT1 pad>*/
        FF_EVENT = 0x10 #/**< Free-fall recognition is routed to INT1 pad>*/
        WAKEUP_EVENT = 0x20 #/**<Wakeup recognition is routed to INT1 pad>*/
        SINGLE_TAP = 0x40  #/**<Single-tap recognition is routed to INT1 pad.>*/
        TNT_16D  = 0x80  #/**<6D recognition is routed to INT1 pad>*/

'''
acce.set_int1_route(acce.FF_EVENT)
#latch interrupt
acce.latch_interrupt(True);


time.sleep(0.1)

while True:
  if(int_pad_Flag == True):
    #Free fall event is detected
    free_fall = acce.free_fall_detect()
    if free_fall == True:
      print("free fall detected")
      time.sleep(0.3)
    int_pad_Flag = False
