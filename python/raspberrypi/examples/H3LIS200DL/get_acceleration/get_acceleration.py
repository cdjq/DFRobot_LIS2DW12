# -*- coding:utf-8 -*-
"""
  @file get_acceleration.py
  @brief 获取x,y,z三个方向的加速度值,加速度的测量的量程可选择±6g,±12g或±24g
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

#如果你想要用SPI驱动此模块，打开下面两行的注释,并通过SPI连接好模块和树莓派
#RASPBERRY_PIN_CS =  27              #Chip selection pin when SPI is selected
#acce = DFRobot_H3LIS200DL_SPI(RASPBERRY_PIN_CS)

#如果你想要应IIC驱动此模块，打开下面三行的注释，并通过I2C连接好模块和树莓派,可通过板子上的拨码开关（gravity版本）或SDO引脚（Breakout版本）切换I2C地址
I2C_BUS         = 0x01            #default use I2C1
#ADDRESS_0       = 0x18            #传感器地址0
ADDRESS_1       = 0x19            #传感器地址1
acce = DFRobot_H3LIS200DL_I2C(I2C_BUS ,ADDRESS_1)

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
Set data measurement rate(hz)
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
time.sleep(0.1)

while True:
    #Get the acceleration in the three directions of xyz
    #测量的量程为±100g或±200g,通过set_range()函数设置
    x,y,z = acce.read_acce_xyz()
    print("Acceleration [X = %.2d g,Y = %.2d g,Z = %.2d g]"%(x,y,z))
    time.sleep(1)