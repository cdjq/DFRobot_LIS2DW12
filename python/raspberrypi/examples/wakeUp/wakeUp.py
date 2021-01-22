# -*- coding:utf-8 -*-
"""
   @file wakeUp.ino
   @brief 让芯片进入睡眠状态，可以降低功耗，当产生中断事件，芯片从睡眠状态回复正常状态，从而正常采集数据
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
print(acce.getID())
#time.sleep(1)
acce.setRange(acce.E_ONE_HUNDRED)
acce.setAcquireRate(acce.E_NORMAL_50HZ)
#设置唤醒阈值
acce.setIntOneTh(20);#0 - 100 / 0 - 200 
#进入睡眠状态
acce.enableSleep(True);
time.sleep(1000)

while True:
    #获取三个方向上的加速度数据
    x = acce.readACCFromX()
    y = acce.readACCFromy()
    z = acce.readACCFromZ()

    time.sleep(100)

    print("Acceleration [X = %.2f mg,Y = %.2f mg,Z = %.2f mg]"%(x,y,z))
