# -*- coding:utf-8 -*-
"""
   @file interrupt.py
   @brief 中断检测
   @n本示例中使能eZHigherThanTh中断事件，即当Z方向的加速度大于程序所设置的阈值时，在我们
   @n设置的中断引脚int1/int2上可以检测到中断电平，通过检测中断引脚上的电平变化即可判断是
   @n否发生该中断事件。可设置的中断事件有以下6个： eXHigherThanTh, eXLowerThanTh, 
   @n eYHigherThanTh, eYLowerThanTh, eZHigherThanTh,eZLowerThanTh,关于每个中断事件的详细
   @n解释请看函数enableInterruptEvent()注释
   @n 在使用SPI时,片选引脚时可以通过改变宏RASPBERRY_PIN_CS的值修改
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

INT1 = 26                           #Interrupt pin
int_pad_Flag = False                 #intPad flag
def int_pad_callback(status):
  global int_pad_Flag
  int_pad_Flag = True

#如果你想要用SPI驱动此模块，打开下面两行的注释,并通过SPI连接好模块和树莓派
#RASPBERRY_PIN_CS =  27              #Chip selection pin when SPI is selected
#acce = DFRobot_H3LIS200DL_SPI(RASPBERRY_PIN_CS)


#如果你想要应IIC驱动此模块，打开下面三行的注释，并通过I2C连接好模块和树莓派,可通过板子上的拨码开关（gravity版本）或SDO引脚（Breakout版本）切换I2C地址
I2C_BUS         = 0x01            #default use I2C1
#ADDRESS_0       = 0x18            #传感器地址0
ADDRESS_1       = 0x19            #传感器地址1
acce = DFRobot_H3LIS200DL_I2C(I2C_BUS ,ADDRESS_1)

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
             H3LIS200DL_100G   # ±100g
             H3LIS200DL_200G   # ±200g
'''
acce.set_range(acce.H3LIS200DL_100G)

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
acce.set_acquire_rate(acce.NORMAL_50HZ)

'''
Set the threshold of interrupt source 1 interrupt
threshold Threshold(g),范围是设置好的的测量量程
'''
acce.set_int1_th(5);

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
acce.enable_int_event(acce.INT_1,acce.Z_HIGHERTHAN_TH)
time.sleep(1)

while True:
   
   if(int_pad_Flag == True):
     #Check whether the interrupt event is generated in interrupt 1
     if acce.get_int1_event(acce.Y_HIGHERTHAN_TH) == True:
        print("The acceleration in the y direction is greater than the threshold")
     
     if acce.get_int1_event(acce.Z_HIGHERTHAN_TH) == True:
       print("The acceleration in the z direction is greater than the threshold")
      
     if acce.get_int1_event(acce.X_HIGHERTHAN_TH) == True:
       print("The acceleration in the x direction is greater than the threshold")
     
     int_pad_Flag = False
   #Get the acceleration in the three directions of xyz
   #测量的量程为±100g或±200g,通过set_range()函数设置
   x,y,z = acce.read_acce_xyz()
   print("Acceleration [X = %.2f g,Y = %.2f g,Z = %.2f g]"%(x,y,z))
   time.sleep(0.1)