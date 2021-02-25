# -*- coding: utf-8 -*
""" 
  @file DFRobot_LIS2DW12.py
  @brief Define the basic structure of class DFRobot_LIS2DW12 
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @licence     The MIT License (MIT)
  @author [fengli](li.feng@dfrobot.com)
  @version  V1.0
  @date  2021-1-29
  @get from https://www.dfrobot.com
  @url https://github.com/DFRobot/DFRobot_LIS2DW12
"""
import struct
import serial
import time
import smbus
import spidev
import numpy as np
import RPi.GPIO as RPIGPIO
I2C_MODE                  = 0x01
SPI_MODE                  = 0x02

class DFRobot_LIS2DW12(object):
  REG_CARD_ID      = 0x0F     #/*The chip id*/
  REG_CTRL_REG1    = 0x20     #/*Control register 1*/
  REG_CTRL_REG4    = 0x23     #/*Control register 2*/
  REG_CTRL_REG2    = 0x21     #/*Control register 3*/
  REG_CTRL_REG3    = 0x22     #/*Control register 4*/
  REG_CTRL_REG5    = 0x24     #/*Control register 5*/
  REG_CTRL_REG6    = 0x25     #/*Control register 6*/
  REG_CTRL_REG7    = 0x3F     #/*Control register 7*/
  REG_STATUS_REG   = 0x27     # /*Status register*/
  REG_OUT_X_L      = 0x28     # /*The low order of the X-axis acceleration register*/
  REG_OUT_X_H      = 0x29     #/*The high point of the X-axis acceleration register*/
  REG_OUT_Y_L      = 0x2A     #/*The low order of the Y-axis acceleration register*/
  REG_OUT_Y_H      = 0x2B     #/*The high point of the Y-axis acceleration register*/
  REG_OUT_Z_L      = 0x2C     #/*The low order of the Z-axis acceleration register*/
  REG_OUT_Z_H      = 0x2D     #/*The high point of the Z-axis acceleration register*/
  REG_WAKE_UP_DUR  = 0x35     #/*Wakeup and sleep duration configuration register (r/w).*/
  REG_FREE_FALL    = 0x36     #/*Free fall event register*/
  REG_STATUS_DUP   = 0x37     # /*Interrupt event status register*/
  REG_STATUS_DUP   = 0x37     # /*Interrupt event status register*/
  REG_WAKE_UP_SRC  = 0x38     # /*Wakeup source register*/
  REG_TAP_SRC      = 0x39     # /*Tap source register*/
  REG_SIXD_SRC     = 0x3A     # /*6D source register*/
  REG_ALL_INT_SRC  = 0x3B     # /*Reading this register, all related interrupt function flags routed to the INT pads are reset simultaneously
  
  REG_TAP_THS_X  =  0x30
  REG_TAP_THS_Y  =  0x31
  REG_TAP_THS_Z  =  0x32
  REG_INT_DUR    =  0x33
  REG_WAKE_UP_THS = 0x34
  
  __range =  0.061
  __reset = 0
  __range_d = 0
  '''
   Power mode
  '''
  HIGH_PERFORMANCE                   = 0X04#High-Performance Mode
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
    Sensor range
  '''
  RANGE_2G     = 2   #/**<±2g>*/
  RANGE_4G     = 4   #/**<±4g>*/
  RANGE_8G     = 8   #/**<±8g>*/
  RANGE_16G    = 16  #/**< ±16g>*/
  
  '''
    Filtering mode
  '''
  LPF_ON_OUT         = 0x00 #/**<Low pass filter>*/
  HIGH_PASS_ON_OUT    = 0x10 #/**<High pass filter>*/

  '''
     bandwidth of collected data
  '''
  ODR_DIV_2     = 0  #/**<ODR/2 (up to ODR = 800 Hz, 400 Hz when ODR = 1600 Hz)>*/
  ODR_DIV_4     = 1  #/**<ODR/4 (HP/LP)>*/
  ODR_DIV_10    = 2  #/**<ODR/10 (HP/LP)>*/
  ODR_DIV_20    = 3  #/**< ODR/20 (HP/LP)>*/

  '''
  Data collection rate
  '''
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
    free fall threshold@ ±2 G FS
  '''
  FFTSH_5LSB_FS2G  = 0  #/**<5 LSB>*/
  FFTSH_7LSB_FS2G  = 1  #/**<7 LSB>*/
  FFTSH_8LSB_FS2G  = 2  #/**<8 LSB>*/
  FFTSH_10LSB_FS2G = 3  #/**<10 LSB>*/
  FFTSH_11LSB_FS2G = 4  #/**<11 LSB>*/
  FFTSH_13LSB_FS2G = 5  #/**<13 LSB>*/
  FFTSH_15LSB_FS2G = 6  #/**<15 LSB>*/
  FFTSH_16LSB_FS2G = 7  #/**<16 LSB>*/

  '''
    Motion detection mode
  '''
  NO_DETECTION        = 0 #/**<No detection>*/
  DETECT_ACTINACT     = 1 #/**<Detect movement>*/
  DETECT_STATMOTION   = 3 #/**<Detect Motion>*/


  '''
  Interrupt source 1 trigger event setting
  '''
  DOUBLE_TAP = 0x08   #/**< Double-tap recognition is routed to INT1 pad>*/
  FF_EVENT = 0x10     #/**< Free-fall recognition is routed to INT1 pad>*/
  WAKEUP_EVENT = 0x20 #/**<Wakeup recognition is routed to INT1 pad>*/
  SINGLE_TAP = 0x40   #/**<Single-tap recognition is routed to INT1 pad.>*/
  TNT_16D  = 0x80     #/**<6D recognition is routed to INT1 pad>*/

  '''
  Interrupt source 2 trigger event setting
  '''

  BOOT = 0x20         #/**< Boot state routed to INT2 pad.>*/
  SLEEP_CHANGE = 0x40 #/**<Enable routing of SLEEP_STATE on INT2 pad>*/
  SLEEP_STATE  = 0x80 # /**<Sleep change status routed to INT2 pad>*/
  
  '''
  Click or double click
  '''
  SINGLE_CLICK  = 0  #/**<Click>*/
  DOUBLE_CLICK  = 1  #/**<double click>*/
  NO_CLICK      = 2  #/**<no click>*/
  
  #which direction is tap event detected
  DIR_X_UP   = 0 #在X 正方向发生的点击事件
  DIR_X_DOWN = 1 #在X 负方向发生的点击事件
  DIR_Y_UP   = 2 #在Y 正方向发生的点击事件
  DIR_Y_DOWN = 3 #在Y 负方向发生的点击事件
  DIR_Z_UP   = 4 #在Z 正方向发生的点击事件
  DIR_Z_DOWN = 5 #在Z 负方向发生的点击事件
  
  #which direction is wake up event detected
  DIR_X = 0 #X方向的运动唤醒芯片
  DIR_Y = 1 #Y方向的运动唤醒芯片
  DIR_Z = 2 #Z方向的运动唤醒芯片
  
  
  #Click detection mode

  ONLY_SINGLE          = 0 #/**<Only detect click events.>*/
  BOTH_SINGLE_DOUBLE   = 1 #/**<Both single-click and double-click events are detected.>*/

  '''
  位置检测
  '''
  DEGREES_80          = 0 #/**<80 degrees.>*/
  DEGREES_70          = 1 #/**<.>*/
  DEGREES_60          = 2 #/**<.>*/
  DEGREES_50          = 3 #/**<.>*/
  
  #orientation
  X_DOWN = 0  #/**<X is now down>*/
  X_UP   = 1  #/**<X is now up>*/
  Y_DOWN = 2  #/**<Y is now down>*/
  Y_UP   = 3  #/**<Y is now up>*/
  Z_DOWN = 4  #/**<Z is now down>*/
  Z_UP   = 5  #/**<Z is now up>*/

  def __init__(self):
    __reset = 1

  '''
    @brief Initialize the function
    @return Return 0 indicates a successful initialization, while other values indicates failure and return to error code.
  '''
  def begin(self):
    identifier = 0 
    identifier = self.read_reg(self.REG_CARD_ID)
    #print(identifier)
    if identifier == 0x44:
      #print("identifier = :")
      #print(identifier)
      return 0
    else:
      return 1
      
  '''
    @brief Get chip id
    @return Returns the eight-digit serial number
  '''
  def get_id(self):
    identifier = 0 
    identifier = self.read_reg(self.REG_CARD_ID)
    return identifier
  '''
    @brief Software reset to restore the value of all registers to the default value
  '''
  def soft_reset(self):
    reg = 0
    reg = self.read_reg(self.REG_CTRL_REG2)
    reg = reg | (1<<6)
    #print(reg)
    self.write_reg(self.REG_CTRL_REG2,reg)
    
    
  '''
    @brief Set the measurement range
    @param range:Range(g)
                 RANGE_2G     #/**<±2g>*/
                 RANGE_4G     #/**<±4g>*/
                 RANGE_8G     #/**<±8g>*/
                 RANGE_16G    #/**< ±16g>*/
  '''
  def set_range(self,range_r):
    reg = self.read_reg(self.REG_CTRL_REG6)
    self.__range_d = range_r
    if range_r == self.RANGE_2G:
      #print("2g")
      reg = reg & (~(3<<4))
      reg = reg | 0
      self.__range = 0.061
    elif range_r == self.RANGE_4G:
      self._range = 0.122
      reg = reg &(~(3<<4))
      reg = reg | (1<<4)
    elif range_r == self.RANGE_8G:
      self._range = 0.244
      reg = reg &(~(3<<4))
      reg = reg | (2<<4)
    elif range_r == self.RANGE_16G:
      self._range = 0.488
      reg = reg &(~(3<<4))
      reg = reg | (3<<4)
    self.write_reg(self.REG_CTRL_REG6,reg)
    
  '''
    @brief Choose whether to continuously let the chip collect data
    @param enable  True(持续采集数据)/False(单次采集数据)
  '''
  def contin_refresh(self,enable):
    reg = self.read_reg(self.REG_CTRL_REG2)
    if enable == True:
       reg = reg | (1<<3)
    else:
       reg = reg &(~(1<<3))
    self.write_reg(self.REG_CTRL_REG2,reg)
  
  '''
    @brief Set the filter processing mode
    @param fds  Three modes of filtering
                LPF_ON_OUT        = 0x00,/<Low pass filter>/
                HIGH_PASS_ON_OUT   = 0x10,/<High pass filter>/
  '''
  def set_filter_path(self,fds):
    reg = self.read_reg(self.REG_CTRL_REG6)
    enable = fds & 0x10
    if(enable > 0):
       enable = 1
    reg = reg & (~(3<<2))
    reg = reg | (enable << 3)
    #print(reg)
    self.write_reg(self.REG_CTRL_REG6,reg)
    reg = self.read_reg(self.REG_CTRL_REG7)
    enable = (fds & 0x10)
    if(enable > 0):
      enable = 1
    reg = reg &(~(1<<4))
    reg = reg | enable << 4
    #print(reg)
    self.write_reg(self.REG_CTRL_REG7,reg)

  '''
    @brief Set the  bandwidth of the data
    @param bw   ODR_DIV_2     = 0,/<ODR/2 (up to ODR = 800 Hz, 400 Hz when ODR = 1600 Hz)>/
                ODR_DIV_4     = 1,/<ODR/4 (High Power/Low power)>*
                ODR_DIV_10    = 2,/<ODR/10 (HP/LP)>/
                ODR_DIV_20    = 3,/< ODR/20 (HP/LP)>/
  '''
  def set_filter_bandwidth(self,bw):
    reg = self.read_reg(self.REG_CTRL_REG6)
    reg = reg & (~(3 << 6))
    reg = reg | (bw << 6)
    #print(reg)
    self.write_reg(self.REG_CTRL_REG6,reg)
    
  '''
    @brief Set power mode
    @param mode 16 power modes to choose from
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
  def set_power_mode(self,mode):
    reg = self.read_reg(self.REG_CTRL_REG1)
    reg = reg & (~0x0f)
    reg = reg | (mode & 0xf)
    self.write_reg(self.REG_CTRL_REG1,reg)
    #print("set_power_mode")
    #print(reg)
    reg = self.read_reg(self.REG_CTRL_REG6)
    enable = mode >> 4
    reg = reg & (~(1 << 2))
    reg = reg | (enable << 2)
    #print(reg)
    self.write_reg(self.REG_CTRL_REG6,reg)
    
  '''
    @brief Set data measurement rate
    @param range rate(g)
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
  def set_data_rate(self, odr):
    reg = self.read_reg(self.REG_CTRL_REG1)
    reg = reg & (~(0xf << 4))
    reg = reg | (odr << 4)
    #print("set_data_rate")
    #print(reg)
    self.write_reg(self.REG_CTRL_REG1,reg)
    reg = self.read_reg(self.REG_CTRL_REG3)
    enable = (odr&0x30) >> 4
    
    reg = reg & (~3)
    reg = reg | enable
    #print(reg)
    self.write_reg(self.REG_CTRL_REG3,reg)
    
  '''
    @brief 自由落体时间
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
  def set_ff_Dur(self,dur):
    reg1 = self.read_reg(self.REG_WAKE_UP_DUR)
    reg2 = self.read_reg(self.REG_FREE_FALL)
    
    reg1 = reg1 & (~0x80)
    reg2 = reg2 & (~0xf8)
    reg2 = reg2 | (dur << 3)
    #print(reg1)
    self.write_reg(self.REG_WAKE_UP_DUR,reg1)
    #print(reg2)
    self.write_reg(self.REG_FREE_FALL,reg2)
    self.set_ff_threshold(self.FFTSH_10LSB_FS2G)
  '''
    @brief Set Free-fall threshold
    @param th threshold
  '''
  def set_ff_threshold(self,th):
    reg = self.read_reg(self.REG_FREE_FALL)
    reg = reg & (~0x07)
    reg = reg | (th & 0x07)
    #print(reg)
    self.write_reg(self.REG_FREE_FALL,reg)
  
  '''
    @brief Set the interrupt source of the int1 pin
    @param event  Several interrupt events, after setting, when an event is generated, a level transition will be generated on the int1 pin
                DOUBLE_TAP = 0x08 #/**< Double-tap recognition is routed to INT1 pad>*/
                FF_EVENT = 0x10 #/**< Free-fall recognition is routed to INT1 pad>*/
                WAKEUP_EVENT = 0x20 #/**<Wakeup recognition is routed to INT1 pad>*/
                SINGLE_TAP = 0x40  #/**<Single-tap recognition is routed to INT1 pad.>*/
                TNT_16D  = 0x80  #/**<6D recognition is routed to INT1 pad>*/
    
  '''
  def set_int1_route(self,event):
    reg1 = self.read_reg(self.REG_CTRL_REG4)
    reg2 = self.read_reg(self.REG_CTRL_REG5)
    reg3 = self.read_reg(self.REG_CTRL_REG7)
    reg3 = reg3 & (~0x20)
    reg3 = reg3 | 0x20
    reg1 = reg1 | event
    self.write_reg(self.REG_CTRL_REG4,reg1)
    self.write_reg(self.REG_CTRL_REG7,reg3)
    
  '''
    @brief Set the wake-up duration
    @param dur Wakeup duration (0~3)
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
  def set_wakeup_dur(self,dur):
    
    reg = self.read_reg(self.REG_WAKE_UP_DUR)
    reg = reg & (~0x60)
    reg = reg | ((dur << 5) & 0x60)
    
    #print(reg)
    self.write_reg(self.REG_WAKE_UP_DUR,reg)
  '''
    @brief Set duration to go in sleep mode.
    @param dur  duration
  '''
  def set_act_sleep_dur(self,dur):
    reg = self.read_reg(self.REG_WAKE_UP_DUR)
    
    dur = dur & 0x0f
    reg = reg & (~0x0f)
    reg = reg | dur
    #print(reg)
    self.write_reg(self.REG_WAKE_UP_DUR,reg)

  '''
    @brief Sets the mode of motion detection
    @param th:     NO_DETECTION        = 0 #/**<No detection>*/
                   DETECT_ACTINACT     = 1 #/**<Detect movement>*/
                   DETECT_STATMOTION   = 3 #/**<Detect Motion>*/
  '''
  def set_act_mode(self,mode):
    reg1 = self.read_reg(self.REG_WAKE_UP_THS)
    reg2 = self.read_reg(self.REG_WAKE_UP_DUR)
    reg1 = reg1 & (~0x01)
    reg2 = reg2 & (~0x02)
    reg1 = reg1 | (mode & 0x01)
    reg2 = reg2 | (mode & 0x02)
    #print(reg1)
    #print(reg2)
    self.write_reg(self.REG_WAKE_UP_THS,reg1)
    self.write_reg(self.REG_WAKE_UP_DUR,reg2)

  '''
    @brief Set the wake-up Threshold
    @param th:unit(g),数值是在量程之内
  '''
  def set_wakeup_threshold(self,th):
    th1 = (float(th)/self.__range_d) * 64
    reg = self.read_reg(self.REG_WAKE_UP_THS)
    reg = reg &(~0x3f)
    #print(int(th1))
    reg = reg | (int(th1) & 0x3f)
    #print(reg)
    self.write_reg(self.REG_WAKE_UP_THS,reg)
  '''
    @brief Latch interrupt
    @param enable  Latched Interrupt. Switches between latched ('1'-logic) and pulsed ('0'-logic) mode for 
     function source signals and interrupts routed to pins (wakeup, single/double-tap).
  '''
  def latch_interrupt(self,enable):
    reg = self.read_reg(self.REG_CTRL_REG3)
    reg = reg & (~0x10)
    reg = reg | (enable << 4)
    self.write_reg(self.REG_CTRL_REG3,reg)
    
  '''
    @brief Set to detect click events in the Z direction
    @param enable:Ture(使能点击检测\False(禁用点击检测)
  '''
  def enable_tap_detection_on_z(self, enable):
    reg = self.read_reg(self.REG_TAP_THS_Z)
    reg = reg & (~(1<<5))
    reg = reg | (enable << 5)
    #print("enable_tap_detection_on_z")
    #print(reg)
    self.write_reg(self.REG_TAP_THS_Z,reg)
  
  '''
    @brief Set to detect click events in the Y direction
    @param enable:Ture(使能点击检测\False(禁用点击检测)
  '''
  def enable_tap_detection_on_y(self, enable):
    reg = self.read_reg(self.REG_TAP_THS_Z)
    reg = reg & (~(1<<6))
    reg = reg | (enable << 6)
    #print("enable_tap_detection_on_y")
    #print(reg)
    self.write_reg(self.REG_TAP_THS_Z,reg)
    
  '''
    @brief Set to detect click events in the X direction
    @param enable:Ture(使能点击检)\False(禁用点击检)
  '''
  def enable_tap_detection_on_x(self, enable):
    reg = self.read_reg(self.REG_TAP_THS_Z)
    reg = reg & (~(1<<7))
    reg = reg | (enable << 7)
    #print("enable_tap_detection_on_x")
    #print(reg)
    self.write_reg(self.REG_TAP_THS_Z,reg)

  '''
    @brief Set the click threshold in the X direction
    @param th:Threshold(g),Can only be used in the range of ±2g
  '''
  def set_tap_threshold_on_x(self,th):
    
    th1 = (float(th)/self.__range_d) * 32
    reg = self.read_reg(self.REG_TAP_THS_X)
    reg = reg & (~0x1f)
    reg = reg | (int(th1) & 0x1f)
    #print("set_tap_threshold_on_x")
    #print(reg)
    self.write_reg(self.REG_TAP_THS_X,reg)
  
  '''
    @brief Set the click threshold in the Y direction
    @param th:Threshold(g),Can only be used in the range of ±2g
  '''
  def set_tap_threshold_on_y(self,th):
    th1 = (float(th)/self.__range_d) * 32
    reg = self.read_reg(self.REG_TAP_THS_Y)
    reg = reg & (~0x1f)
    reg = reg | (int(th1) & 0x1f)
    #print("set_tap_threshold_on_y")
    #print(reg)
    self.write_reg(self.REG_TAP_THS_Y,reg)
    
  '''
    @brief Set the click threshold in the Z direction
    @param th:Threshold(g),Can only be used in the range of ±2g
  '''
  def set_tap_threshold_on_z(self,th):
    th1 = (float(th)/self.__range_d) * 32
    reg = self.read_reg(self.REG_TAP_THS_Z)
    reg = reg & (~0x1f)
    reg = reg | (int(th1) & 0x1f)
    #print("set_tap_threshold_on_z")
    #print(reg)
    self.write_reg(self.REG_TAP_THS_Z,reg)
    
  '''
    @brief 双击的两次点击之间的间隔时间
    @param th 1 LSB = 32 * 1/ODR(0~15)
    @n ODR:Data acquisition frequency
    @n example
    |                           High-pass filter cut-off frequency configuration                             |
    |--------------------------------------------------------------------------------------------------------|
    |                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
    |   dur          |Data rate = 25 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 800 Hz  |
    |--------------------------------------------------------------------------------------------------------|
    |  n             |n*(1s/25)= n*40ms|  n*(1s/100)= n*10ms  |  n*(1s/400)= 2.5*nms |  n*(1s/800)= n*1.25ms |
    |--------------------------------------------------------------------------------------------------------|
  '''
  def set_tap_dur(self,dur):
    reg = self.read_reg(self.REG_INT_DUR)
    reg = reg & (~0xf0)
    reg = reg | (dur << 4)
    #print("set_tap_dur")
    #print(reg)
    self.write_reg(self.REG_INT_DUR,reg)
    self.set_tap_quiet(2);
    self.set_tap_shock(2);
  '''
    @brief set quiet time after a tap detection: this register represents
    @n the time after the first detected tap in which there must not be any overthreshold event.
    @param quiet quiet time
  '''
  def set_tap_quiet(self,quiet):
    reg = self.read_reg(self.REG_INT_DUR)
    reg = reg & (~0x0C)
    quiet = quiet & 0x03
    reg = reg | (quiet<<2)
    #print("set_tap_quiet")
    #print(reg)
    self.write_reg(self.REG_INT_DUR,reg)
  
  '''
    @brief Set the maximum time of an over-threshold signal detection to be recognized as a tap event.
    @param shock  shock time
  '''
  def set_tap_shock(self,shock):
    reg = self.read_reg(self.REG_INT_DUR)
    reg = reg & (~0x03)
    shock = shock & 0x03
    reg = reg | (shock)
    #print("set_tap_shock")
    #print(reg)
    self.write_reg(self.REG_INT_DUR,reg)
  
  '''
    @brief Set the click detection mode
    @param mode      ONLY_SINGLE   //检测单击
                     BOTH_SINGLE_DOUBLE //检测单击和双击
  '''
  def set_tap_mode(self,mode):
    reg = self.read_reg(self.REG_WAKE_UP_THS)
    reg = reg & (~0x80)
    reg = reg | (mode << 7)
    #print("set_tap_mode")
    #print(reg)
    self.write_reg(self.REG_WAKE_UP_THS,reg)

  '''
    @brief Set Thresholds for 4D/6D，当转动的阈值大于指定角度时,就发生方向转变的事件
    @param degree:  DEGREES_80   80°
                    DEGREES_70   70°
                    DEGREES_60   60°
                    DEGREES_50   50°
  '''
  def set_6d_threshold(self,degree):
    reg = self.read_reg(self.REG_TAP_THS_X)
    reg = reg & (~0x60)
    reg = reg | (degree << 5)
    #print("set_6d_threshold")
    #print(reg)
    self.write_reg(self.REG_TAP_THS_X,reg)
    self.set_6d_feed_data(1)
    
  '''
    @brief Set interrupt source of int2 pin
    @param event  Several interrupt events, after setting, when an event is generated, a level transition will be generated on the int2 pin
                  BOOT = 0x20,/< Boot state routed to INT2 pad.>/
                  SLEEP_CHANGE = 0x40,/<Enable routing of SLEEP_STATE on INT2 pad>/
                  SLEEP_STATE  = 0x80,/<Sleep change status routed to INT2 pad>/
  '''
  def set_int2_route(self,event):
    reg1 = self.read_reg(self.REG_CTRL_REG4)
    reg2 = self.read_reg(self.REG_CTRL_REG5)
    reg3 = self.read_reg(self.REG_CTRL_REG7)
    
    reg3 = reg3 & (~0x20)
    reg3 = reg3 | 0x20
    
    reg2 = reg2 | event
    #print(reg2)
    #print(reg3)
    self.write_reg(self.REG_CTRL_REG5,reg2)
    self.write_reg(self.REG_CTRL_REG7,reg3)

  '''
    @brief Set 6d filtered data source
    @param data 0: ODR/2 low pass filtered data sent to 6D interrupt function (default)
                1: LPF2 output data sent to 6D interrupt function)
  '''
  def set_6d_feed_data(self,data):
    reg = self.read_reg(self.REG_CTRL_REG7)
    reg = reg & (~1)
    reg = reg | data
    print(reg)
    self.write_reg(self.REG_CTRL_REG7,reg)
  '''
    @brief Read the acceleration in the x direction
    @return Acceleration data(g)
  '''
  def read_acc_x(self):
    reg1 = self.read_reg(self.REG_OUT_X_L)
    reg2 = self.read_reg(self.REG_OUT_X_L+1)
    acc_x = np.int8(reg2)*256 + np.int8(reg1)
    acc_x = acc_x * self.__range
    return acc_x

  '''
    @brief Read the acceleration in the y direction
    @return  Acceleration data(g)
  '''
  def read_acc_y(self):
    reg1 = self.read_reg(self.REG_OUT_Y_L)
    reg2 = self.read_reg(self.REG_OUT_Y_L+1)
    acc_y = np.int8(reg2)*256 + np.int8(reg1)
    acc_y = acc_y * self.__range
    return acc_y

  '''
    @brief Read the acceleration in the z direction
    @return Acceleration data(g)
  '''
  def read_acc_z(self):
    reg1 = self.read_reg(self.REG_OUT_Z_L)
    reg2 = self.read_reg(self.REG_OUT_Z_L+1)
    acc_z = np.int8(reg2)*256 + np.int8(reg1)
    acc_z = acc_z * self.__range
    return acc_z
  
  '''
    @brief 检测是否有运动产生
    @return True(产生运动)/False(传感器未运动)
  '''
  def act_detect(self):
    reg = self.read_reg(self.REG_WAKE_UP_SRC)
    if(reg & 0x08) > 0:
      return True
    else:
      return False
      
  '''
    @brief 自由落体运动检测
    @return True(检测到自由落体运动)/False(未检测到自由落体运动)
  '''
  def free_fall_detect(self):
    reg = self.read_reg(self.REG_WAKE_UP_SRC)
    if(reg & 0x20) > 0:
      return True
    return False
  '''
    @brief Source of change in position portrait/landscape/face-up/face-down.
    @return True( no event detected)/False(a change in position is detected)
  '''
  def ia6d_detect(self):
    reg = self.read_reg(self.REG_SIXD_SRC)
    if(reg & 0x40) > 0:
      return True
    else:
      return False
      
  '''
  @brief 获取传感器现在的位置
  @return      X_DOWN = 0 #/**<X is now down>*/
               X_UP  = 1 #/**<X is now up>*/
               Y_DOWN = 2 #/**<Y is now down>*/
               Y_UP = 3  #/**<Y is now up>*/
               Z_DOWN = 4  #/**<Z is now down>*/
               Z_UP = 5  #/**<Z is now up>*/
  '''
  def get_orient(self):
   reg = self.read_reg(self.REG_SIXD_SRC)
   if(reg & 0x1) > 0:
     return self.X_DOWN
   elif(reg & 0x2) > 0:
     return self.X_UP
   elif(reg & 0x4) > 0:
     return self.Y_DOWN
   elif(reg & 0x8) > 0:
     return self.Y_UP
   elif(reg & 0x10) > 0:
     return self.Z_DOWN
   elif(reg & 0x20) > 0:
     return self.Z_UP
   else:
     return 0xff
     
  '''
    @brief 点击检测
    @return   SINGLE_CLICK  = 0 ,/<click>/
              DOUBLE_CLICK   ,/<double click>/
              NO_CLICK,      //没有点击产生
  '''
  def tap_detect(self):
   reg = self.read_reg(self.REG_TAP_SRC)
   #print(reg)
   if(reg & 0x20) > 0:
     return self.SINGLE_CLICK
   elif(reg & 0x10) > 0:
     return self.DOUBLE_CLICK
   else:
     return 0XFF
   #Wakeup event detection status on X-axis

  '''
    @brief 点击方向的源头检测
    @return     DIR_X_UP = 0#在X 正方向发生的点击事件
                DIR_X_DOWN = 1#在X 负方向发生的点击事件
                DIR_Y_UP = 2#在Y 正方向发生的点击事件
                DIR_Y_DOWN = 3#在Y 负方向发生的点击事件
                DIR_Z_UP = 4#在Z 正方向发生的点击事件
                DIR_Z_DOWN = 5#在Z 负方向发生的点击事件
  '''
  def get_tap_direction(self):
   reg = self.read_reg(self.REG_TAP_SRC)
   #print(reg)
   positive = reg & 0x08
   if(reg & 0x4)>0 and positive > 0:
     return self.DIR_X_UP
   elif(reg & 0x4)>0 and positive == 0:
     return self.DIR_X_DOWN
   elif(reg & 0x2)>0 and positive > 0:
     return self.DIR_Y_UP
   elif(reg & 0x2)>0 and positive == 0:
     return self.DIR_Y_DOWN
   elif(reg & 0x1)>0 and positive > 0:
     return self.DIR_Z_UP
   elif(reg & 0x1)>0 and positive == 0:
     return self.DIR_Z_DOWN
   return 0XFF
  '''
    @brief 唤醒的运动方向检测
    @return    DIR_X = 0#X方向的运动唤醒芯片
               DIR_Y = 1#Y方向的运动唤醒芯片
               DIR_Z = 2#Z方向的运动唤醒芯片
               eDirError,
  '''
  def get_wake_up_dir(self):
    reg = self.read_reg(self.REG_WAKE_UP_SRC)
    if(reg & 0x01) > 0:
      return self.DIR_Z
    elif(reg & 0x02) > 0:
      return self.DIR_Y
    elif(reg & 0x04) > 0:
      return self.DIR_X
    else:
      return 0xFF

'''
  @brief An example of an i2c interface module
'''
class DFRobot_IIS2DLPC_I2C(DFRobot_LIS2DW12): 
  def __init__(self ,bus ,addr):
    self.__addr = addr;
    super(DFRobot_IIS2DLPC_I2C, self).__init__()
    self.i2cbus = smbus.SMBus(bus)
    RPIGPIO.setmode(RPIGPIO.BCM)
    RPIGPIO.setwarnings(False)
  '''
    @brief writes data to a register
    @param reg register address
    @param value written data
  '''
  def write_reg(self, reg, data):
        data1 = [0]
        data1[0] = data
        self.i2cbus.write_i2c_block_data(self.__addr ,reg,data1)
        #self.i2cbus.write_byte(self.__addr ,reg)
        #self.i2cbus.write_byte(self.__addr ,data)
  '''
    @brief read the data from the register
    @param reg register address
    @param value read data
  '''
  def read_reg(self, reg):
    self.i2cbus.write_byte(self.__addr,reg)
    time.sleep(0.01)
    rslt = self.i2cbus.read_byte(self.__addr)
    #print(rslt)
    return rslt
    
  '''
    @brief  Set External Interrupt
    @param pin Interrupt pin
    @param cb Interrupt service function
    @param mode Interrupt trigger mode
  '''
  def attach_interrupt(self,pin, cb,mode):
    RPIGPIO.setup(pin, RPIGPIO.IN)
    if mode != RPIGPIO.RISING and mode != RPIGPIO.FALLING and mode != RPIGPIO.BOTH:
      return
    RPIGPIO.add_event_detect(pin, mode, cb)
    
class DFRobot_IIS2DLPC_SPI(DFRobot_LIS2DW12): 
  def __init__(self ,cs, bus = 0, dev = 0,speed = 100000):
    super(DFRobot_IIS2DLPC_SPI, self).__init__()
    RPIGPIO.setmode(RPIGPIO.BCM)
    RPIGPIO.setwarnings(False)
    self.__cs = cs
    RPIGPIO.setup(self.__cs, RPIGPIO.OUT)
    RPIGPIO.output(self.__cs, RPIGPIO.LOW)
    self.__spi = spidev.SpiDev()
    self.__spi.open(bus, dev)
    self.__spi.no_cs = True
    self.__spi.max_speed_hz = speed
    
  '''
    @brief writes data to a register
    @param reg register address
    @param value written data
  '''
  def write_reg(self, reg, data):
     data1 =[reg,data]
     RPIGPIO.output(self.__cs, RPIGPIO.LOW)
     self.__spi.writebytes(data1)
     RPIGPIO.output(self.__cs, RPIGPIO.HIGH)
     #self._spi.transfer(data)
  '''
    @brief read the data from the register
    @param reg register address
    @return value read data
  '''
  def read_reg(self, reg):
     data1 =[reg+0x80]
     RPIGPIO.output(self.__cs, RPIGPIO.LOW)
     self.__spi.writebytes(data1)
     time.sleep(0.01)
     data = self.__spi.readbytes(1)
     RPIGPIO.output(self.__cs, RPIGPIO.HIGH)
     return  data[0]
  
  '''
    @brief  Set External Interrupt
    @param pin Interrupt pin
    @param cb Interrupt service function
    @param mode Interrupt trigger mode
  '''
  def attach_interrupt(self,pin, cb,mode):
    RPIGPIO.setup(pin, RPIGPIO.IN)
    if mode != RPIGPIO.RISING and mode != RPIGPIO.FALLING and mode != RPIGPIO.BOTH:
      return
    RPIGPIO.add_event_detect(pin, mode, cb)

'''
  @brief An example of an i2c interface module
'''
class DFRobot_LIS2DW12_I2C(DFRobot_LIS2DW12): 
  def __init__(self ,bus ,addr):
    self.__addr = addr;
    super(DFRobot_LIS2DW12_I2C, self).__init__()
    self.i2cbus = smbus.SMBus(bus)
    RPIGPIO.setmode(RPIGPIO.BCM)
    RPIGPIO.setwarnings(False)
  '''
    @brief writes data to a register
    @param reg register address
    @param value written data
  '''
  def write_reg(self, reg, data):
        data1 = [0]
        data1[0] = data
        self.i2cbus.write_i2c_block_data(self.__addr ,reg,data1)
        #self.i2cbus.write_byte(self.__addr ,reg)
        #self.i2cbus.write_byte(self.__addr ,data)

  '''
    @brief read the data from the register
    @param reg register address
    @param value read data
  '''
  def read_reg(self, reg):
    self.i2cbus.write_byte(self.__addr,reg)
    time.sleep(0.01)
    rslt = self.i2cbus.read_byte(self.__addr)
    #print(rslt)
    return rslt
  '''
    @brief  Set External Interrupt
    @param pin Interrupt pin
    @param cb Interrupt service function
    @param mode Interrupt trigger mode
  '''
  def attach_interrupt(self,pin, cb,mode):
    RPIGPIO.setup(pin, RPIGPIO.IN)
    if mode != RPIGPIO.RISING and mode != RPIGPIO.FALLING and mode != RPIGPIO.BOTH:
      return
    RPIGPIO.add_event_detect(pin, mode, cb)
    
class DFRobot_LIS2DW12_SPI(DFRobot_LIS2DW12): 
  def __init__(self ,cs, bus = 0, dev = 0,speed = 1000000):
    super(DFRobot_LIS2DW12_SPI, self).__init__()
    RPIGPIO.setmode(RPIGPIO.BCM)
    RPIGPIO.setwarnings(False)
    self.__cs = cs
    RPIGPIO.setup(self.__cs, RPIGPIO.OUT)
    RPIGPIO.output(self.__cs, RPIGPIO.LOW)
    self.__spi = spidev.SpiDev()
    self.__spi.open(bus, dev)
    self.__spi.no_cs = True
    self.__spi.max_speed_hz = speed
  '''
    @brief writes data to a register
    @param reg register address
    @param value written data
  '''
  def write_reg(self, reg, data):
     data1 =[reg,data]
     RPIGPIO.output(self.__cs, RPIGPIO.LOW)
     self.__spi.writebytes(data1)
     RPIGPIO.output(self.__cs, RPIGPIO.HIGH)
     #self._spi.transfer(data)
  '''
    @brief read the data from the register
    @param reg register address
    @return value read data
  '''
  def read_reg(self, reg):
     data1 =[reg+0x80]
     RPIGPIO.output(self.__cs, RPIGPIO.LOW)
     self.__spi.writebytes(data1)
     time.sleep(0.01)
     data = self.__spi.readbytes(1)
     RPIGPIO.output(self.__cs, RPIGPIO.HIGH)
     #print(data)
     return  data[0]
  
  '''
    @brief  Set External Interrupt
    @param pin Interrupt pin
    @param cb Interrupt service function
    @param mode Interrupt trigger mode
  '''
  def attach_interrupt(self,pin, cb,mode):
    RPIGPIO.setup(pin, RPIGPIO.IN)
    if mode != RPIGPIO.RISING and mode != RPIGPIO.FALLING and mode != RPIGPIO.BOTH:
      return
    RPIGPIO.add_event_detect(pin, mode, cb)