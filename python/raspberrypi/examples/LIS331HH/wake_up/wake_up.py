# -*- coding:utf-8 -*-
"""
   @file wake_up.py
   @brief 使用睡眠唤醒功能
   @n 现象：使用此功能需要先让模块处于低功耗模式,此时的测量速率会很慢
   @n 当有设置好的中断事件产生,模块会进入正常模式,测量速率加快,达到省电和提供采样率的目的
   @n 在使用SPI时,片选引脚时可以通过改变RASPBERRY_PIN_CS的值修改
   @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   @licence     The MIT License (MIT)
   @author [fengli](li.feng@dfrobot.com)
   @version  V1.0
   @date  2021-01-16
   @get from https://www.dfrobot.com
   @https://github.com/DFRobot/DFRobot_LIS
"""

import sys
sys.path.append("../../..") # set system path to top

from DFRobot_LIS import *
import time

INT1 = 26                           #Interrupt pin(BCM编码)
int_pad_Flag = False                #intPad flag
def int_pad_callback(status):
  global int_pad_Flag
  int_pad_Flag = True

#如果你想要用SPI驱动此模块，打开下面两行的注释,并通过SPI连接好模块和树莓派
#RASPBERRY_PIN_CS =  27              #Chip selection pin when SPI is selected
#acce = DFRobot_LIS331HH_SPI(RASPBERRY_PIN_CS)


#如果你想要应IIC驱动此模块，打开下面三行的注释，并通过I2C连接好模块和树莓派,可通过板子上的拨码开关（gravity版本）或SDO引脚（Breakout版本）切换I2C地址
I2C_BUS         = 0x01            #default use I2C1
#ADDRESS_0       = 0x18            #传感器地址0
ADDRESS_1       = 0x19            #传感器地址1
acce = DFRobot_LIS331HH_I2C(I2C_BUS ,ADDRESS_1)

# set int_Pad to input
GPIO.setup(INT1, GPIO.IN)
#set int_Pad interrupt callback
GPIO.add_event_detect(INT1,GPIO.RISING,int_pad_callback)

#Chip initialization
acce.begin()
#Get chip id
print('chip id :%x'%acce.get_id())

'''
set range:Range(g)
          LIS331HH_6G  = 6   #±6G
          LIS331HH_12G = 12  #±12G
          LIS331HH_24G = 24  #±24G
'''
acce.set_range(acce.LIS331HH_6G)

'''
Set data measurement rate
         POWERDOWN_0HZ 
         LOWPOWER_HALFHZ 
         LOWPOWER_1HZ 
         LOWPOWER_2HZ 
         LOWPOWER_5HZ 
         LOWPOWER_10HZ 
         NORMAL_50HZ 
         NORMAL_100HZ 
         NORMAL_400HZ 
         NORMAL_1000HZ 
'''
acce.set_acquire_rate(acce.LOWPOWER_HALFHZ)
'''
   Set the threshold of interrupt source 1 interrupt
   threshold Threshold(g),范围是设置好的的测量量程
'''
acce.set_int2_th(2)

#Enable sleep wake function
acce.enable_sleep(True)

'''
Enable interrupt
Interrupt pin selection
         INT_1 = 0,/<int pad 1 >/
         INT_2,/<int pad 2>/
Interrupt event selection
             X_LOWERTHAN_TH     = 0x1<The acceleration in the x direction is less than the threshold>
             X_HIGHERTHAN_TH  = 0x2<The acceleration in the x direction is greater than the threshold>
             Y_LOWERTHAN_TH     = 0x4<The acceleration in the y direction is less than the threshold>
             Y_HIGHERTHAN_TH  = 0x8<The acceleration in the y direction is greater than the threshold>
             Z_LOWERTHAN_TH     = 0x10<The acceleration in the z direction is less than the threshold
             Z_HIGHERTHAN_TH  = 0x20<The acceleration in the z direction is greater than the threshold>
             EVENT_ERROR      = 0 <No event>
'''
acce.enable_int_event(acce.INT_2,acce.Y_HIGHERTHAN_TH)
time.sleep(1)

while True:
    #Get the acceleration in the three directions of xyz
    #测量的量程为±6g,±12g或±24g,通过set_range()函数设置
    #当有中断产生，能观察到芯片测量的频率明显变快
    x,y,z = acce.read_acce_xyz()
    print("Acceleration [X = %.2f mg,Y = %.2f mg,Z = %.2f mg]"%(x,y,z))
    if(int_pad_Flag == True):
      print("Out of sleep mode")
      int_pad_Flag = False
    time.sleep(0.1)
