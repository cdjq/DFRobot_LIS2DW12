# -*- coding:utf-8 -*-
"""
   @file getAcceleration.ino
   @brief 获取 x,y,z方向上的加速度
   @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   @licence     The MIT License (MIT)
   @author [fengli](li.feng@dfrobot.com)
   @version  V1.0
   @date  2021-01-16
   @get from https://www.dfrobot.com
   @https://github.com/DFRobot/DFRobot_H3LIS200DL
"""

import sys
sys.path.append("../..") # set system path to top

from DFRobot_H3LIS200DL import *
import time

# peripheral params
RASPBERRY_SPI_BUS = 0
RASPBERRY_PIN_CS = 27
I2C_MODE         = 0x01            # default use I2C1
ADDRESS_0        = 0x19

#acce = DFRobot_H3LIS200DL_SPI(RASPBERRY_SPI_BUS,RASPBERRY_PIN_CS)
#
acce = DFRobot_H3LIS200DL_I2C(I2C_MODE ,ADDRESS_0)
# clear screen
acce.begin()
print("chip id :")
#获取芯片id
print(acce.getID())
#time.sleep(1)
#设置测量量程
acce.setRange(acce.E_ONE_HUNDRED)
#设置数据采集频率
acce.setAcquireRate(acce.E_NORMAL_50HZ)
time.sleep(1000)

while True:
    #获取三个方向上的加速度数据
    x = acce.readACCFromX()
    y = acce.readACCFromy()
    z = acce.readACCFromZ()
    time.sleep(300)
    
    
    print("Acceleration [X = %.2f mg,Y = %.2f mg,Z = %.2f mg]"%(x,y,z))
