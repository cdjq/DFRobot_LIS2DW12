# -*- coding: utf-8 -*
""" 
  @file DFRobot_H3LIS200DL.py
  @brief Define the basic structure of class DFRobot_H3LIS200DL 
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @licence     The MIT License (MIT)
  @author [fengli](li.feng@dfrobot.com)
  @version  V1.0
  @date  2020-12-23
  @get from https://www.dfrobot.com
  @url https://github.com/DFRobot/DFRobot_H3LIS200DL
"""
import serial
import time
import smbus
import spidev
H3LIS200DL_I2C_ADDR = 0x19        #/*sensor IIC address*/
H3LIS200DL_REG_CARD_ID = 0x0F     #/*芯片id*/
H3LIS200DL_REG_CTRL_REG1 = 0x20     #/*控制寄存器1*/
H3LIS200DL_REG_CTRL_REG4 = 0x23     #/*控制寄存器4*/
H3LIS200DL_REG_CTRL_REG2 = 0x21     #/*控制寄存器2*/
H3LIS200DL_REG_CTRL_REG3 = 0x22     #/*中断控制寄存器*/
H3LIS200DL_REG_CTRL_REG5 = 0x24     #/*控制寄存器5*/
H3LIS200DL_REG_CTRL_REG6 = 0x25     #/*控制寄存器6*/
H3LIS200DL_REG_STATUS_REG = 0x27     #/*状态寄存器*/
H3LIS200DL_REG_OUT_X = 0x29     #/*控制寄存器1*/
H3LIS200DL_REG_OUT_Y = 0x2B     #/*控制寄存器1*/
H3LIS200DL_REG_OUT_Z = 0x2D     #/*控制寄存器1*/
H3LIS200DL_REG_INT1_THS = 0x32     #/*中断源1阈值*/
H3LIS200DL_REG_INT2_THS = 0x36     #/*中断源2阈值*/
H3LIS200DL_REG_INT1_CFG = 0x30     #/*中断源1配置寄存器*/
H3LIS200DL_REG_INT2_CFG = 0x34     #/*中断源2配置寄存器*/
H3LIS200DL_REG_INT1_SRC = 0x31     #/*中断源1状态寄存器*/
H3LIS200DL_REG_INT2_SRC = 0x35     #/*中断源2状态寄存器*/
I2C_MODE                  = 0x01
SPI_MODE                 = 0x02
E_POWER_DOWN = 0
E_LOWPOWER_HALFHZ = 1 
E_LOWPOWER_1HZ = 2
E_LOWPOWER_2HZ = 3
E_LOWPOWER_5HZ = 4
E_LOWPOWER_10HZ = 5 
E_NORMAL_50HZ = 6
E_NORMAL_100HZ = 7
E_NORMAL_400HZ = 8
E_NORMAL_1000HZ = 9


E_ONE_HUNDRED =0
E_TWO_HUNDRED = 1

E_CUTOFF_MODE1 = 0
E_CUTOFF_MODE2 = 1
E_CUTOFF_MODE3 = 2
E_CUTOFF_MODE4 = 3
E_SHUTDOWN = 4,

E_X_LOWTHAN_TH = 0
E_X_HIGHERTHAN_TH  = 1
E_Y_LOWTHAN_TH = 2
E_Y_HIGHERTHAN_TH = 3
E_Z_LOWTHAN_TH = 4
E_Z_HIGHERTHAN_TH = 5
E_EVENT_ERROR = 6

eINT1 = 0,
eINT2 = 1,
ERROR                     = -1

class SPI:

  MODE_1 = 1
  MODE_2 = 2
  MODE_3 = 3
  MODE_4 = 4

  def __init__(self, bus, dev, speed = 3900000, mode = MODE_4):
    self._bus = spidev.SpiDev()
    self._bus.open(0, 0)
    self._bus.no_cs = True
    self._bus.max_speed_hz = speed
    self._bus.threewire  = True

  def transfer(self, buf):
    if len(buf):
      return self._bus.writebytes(buf)
    return []
  def readData(self, cmd):
    return self._bus.readbytes(cmd)
  
class DFRobot_H3LIS200DL(object):
  __m_flag   = 0                # mode flag
  __count    = 0                # acquisition count    
  __txbuf        = [0]          # i2c send buffer
  __alcoholdata  = [0]*101      # alcohol data
  __uart_i2c     =  0
  __range = 100
  def __init__(self ,bus ,Baud):
    if bus != 0:
      self.i2cbus = smbus.SMBus(bus)
      self.__uart_i2c = I2C_MODE;
    else:
      self.ser = serial.Serial("/dev/ttyAMA0" ,baudrate=Baud,stopbits=1, timeout=0.5)
      self.__uart_i2c = UART_MODE;



  '''
    @brief set the mode to read the data
    @param mode MEASURE_MODE_AUTOMATIC or MEASURE_MODE_PASSIVE
  '''
  def begin(self):
    identifier = self.read_reg(self.H3LIS200DL_REG_CARD_ID)
    if identifier == 0x32:
      print("identifier = :")
      print(identifier)
      return 0
    else 
      return 1
  
  def getID(self):
    identifier = self.read_reg(self.H3LIS200DL_REG_CARD_ID)
    return identifier
  def setRange(self,range_r):
    reg = self.read_reg(self.H3LIS200DL_REG_CTRL_REG4)
    if range_r == self.E_ONE_HUNDRED:
     reg = reg & (~0x10);
     self.__range = 100;
    else:
     reg = reg | 0x10;
     self.__range = 200;
    #print(reg)
    self.write_reg(self.H3LIS200DL_REG_CTRL_REG4,reg)


  def setAcquireRate(self, rate):
    reg = self.read_reg(self.H3LIS200DL_REG_CTRL_REG1)
    if rate == self.E_POWER_DOWN:
      reg = reg & (~(0x7 << 5))
    elif rate == self.E_LOWPOWER_HALFHZ:
      reg = reg & (~(0x7 << 5))
      reg = reg | (0x02 << 5)
    elif rate == self.E_LOWPOWER_1HZ:
      reg = reg & (~(0x7 << 5))
      reg = reg | (0x03 << 5)
    elif rate == self.E_LOWPOWER_2HZ:
      reg = reg & (~(0x7 << 5))
      reg = reg | (0x04 << 5)
    elif rate == self.E_LOWPOWER_5HZ:
      reg = reg & (~(0x7 << 5))
      reg = reg | (0x05 << 5)
    elif rate == self.E_LOWPOWER_10HZ:
      reg = reg & (~(0x7 << 5))
      reg = reg | (0x06 << 5)
    elif rate == self.E_NORMAL_50HZ:
      reg = reg & (~(0x7 << 5))
      reg = reg | (0x01 << 5)
      reg = reg & (~(0x3 << 3))
    elif rate == self.E_NORMAL_100HZ:
      reg = reg & (~(0x7 << 5))
      reg = reg | (0x01 << 5)
      reg = reg & (~(0x3 << 3))
      reg = reg | (0x01 << 3)
    elif rate == self.E_NORMAL_400HZ:
      reg = reg & (~(0x7 << 5))
      reg = reg | (0x01 << 5)
      reg = reg & (~(0x3 << 3))
      reg = reg | (0x02 << 3)
    elif rate == self.E_NORMAL_1000HZ:
      reg = reg & (~(0x7 << 5))
      reg = reg | (0x01 << 5)
      reg = reg & (~(0x3 << 3))
      reg = reg | (0x03 << 3)
    #print(reg);
    self.write_reg(self.H3LIS200DL_REG_CTRL_REG1,reg);
  
  
  
  def setIntOneTh(self,threshold):
    reg = (threshold * 128)/self.__range
    #print(reg)
    self.write_reg(self.H3LIS200DL_REG_INT1_THS,reg)
  '''
    @brief get the alcohol data ,units of PPM
    @param collectnum Collect the number
    @return  alcohol concentration, (units PPM)
  '''
  def setIntTwoTh(self,threshold):
    reg = (threshold * 128)/self.__range
    #print(reg)
    self.write_reg(self.H3LIS200DL_REG_INT2_THS,reg)


  def enableInterruptEvent(self,source,event):
    reg = 0
    if source == self.eINT1:
      reg = self.read_reg(self.H3LIS200DL_REG_INT1_CFG)
    else:
      reg = self.read_reg(self.H3LIS200DL_REG_INT2_CFG)
    
    if event == self.E_X_LOWTHAN_TH:
      reg = reg | 0x01
    elif event == self.E_X_HIGHERTHAN_TH:
      reg = reg | 0x02
    elif event == self.E_Y_LOWTHAN_TH:
      reg = reg | 0x04
    elif event == self.E_Y_HIGHERTHAN_TH:
      reg = reg | 0x08
    elif event == self.E_Z_LOWTHAN_TH:
      reg = reg | 0x10      
    elif event == self.E_Z_HIGHERTHAN_TH:
      reg = reg | 0x20
      
    #print(reg)
    if source == self.eINT1:
      self.write_reg(self.H3LIS200DL_REG_INT1_CFG,reg)
    else:
      self.write_reg(self.H3LIS200DL_REG_INT2_CFG,reg)
  def getInterruptEvent(self,source):
    reg = 0
    if source == self.eINT1:
      reg = self.read_reg(self.H3LIS200DL_REG_INT1_SRC)
    else:
      reg = self.read_reg(self.H3LIS200DL_REG_INT2_SRC)
    if(reg & 0x41) > 0x40 :
      return self.E_X_LOWTHAN_TH
    elif(reg & 0x42) > 0x40:
      return self.E_X_HIGHERTHAN_TH
    elif(reg & 0x44) > 0x40:
     return self.E_Y_LOWTHAN_TH
    elif(reg & 0x48) > 0x40:
     return self.E_Y_HIGHERTHAN_TH
    elif(reg & 0x50) > 0x40:
     return self.E_Z_LOWTHAN_TH
    elif(reg & 0x60) > 0x40:
     return self.E_Z_HIGHERTHAN_TH
    return self.E_EVENT_ERROR
  
  def enableSleep(self, enable):
    reg = 0
    if enable == True:
      reg = 3
    else
      reg = 0
    self.write_reg(self.H3LIS200DL_REG_CTRL_REG5,reg)
    
    return 0


  def setHFilterMode(self,mode):
    
    reg = self.read_reg(self.H3LIS200DL_REG_CTRL_REG1)
    if mode == self.E_SHUTDOWN:
      reg = reg & (~0x10)
      return 0
    else:
      reg = reg | 0x10
    reg = reg & (~3)
    reg = reg | mode
    #print(reg)
    self.write_reg(self.H3LIS200DL_REG_CTRL_REG1,reg)


  def enableXYZ(self):
    reg = self.read_reg(self.H3LIS200DL_REG_CTRL_REG1)
    reg = reg | 0x07
    self.write_reg(self.H3LIS200DL_REG_CTRL_REG1,reg)
  
  
  def readACCFromX(self):

    ACCX = 0;
    reg = self.read_reg(self.H3LIS200DL_REG_STATUS_REG)
    if(reg & 0x01) == 1:
       return self.read_reg(self.H3LIS200DL_REG_OUT_X)
    else:
       return 0
       
  def readACCFromy(self):

    ACCY = 0;
    reg = self.read_reg(self.H3LIS200DL_REG_STATUS_REG)
    if(reg & 0x02) == 1:
       return self.read_reg(self.H3LIS200DL_REG_OUT_Y)
    else:
       return 0

  def readACCFromZ(self):

    ACCZ = 0;
    reg = self.read_reg(self.H3LIS200DL_REG_STATUS_REG)
    if(reg & 0x04) == 1:
       return self.read_reg(self.H3LIS200DL_REG_OUT_Z)
    else:
       return 0
  
'''
  @brief An example of an i2c interface module
'''
class DFRobot_H3LIS200DL_I2C(DFRobot_Alcohol): 
  def __init__(self ,bus ,addr):
    self.__addr = addr;
    super(DFRobot_H3LIS200DL_I2C, self).__init__(bus,0)

  '''
    @brief writes data to a register
    @param reg register address
    @param value written data
  '''
  def write_reg(self, reg, data):
    data1 = [0]
    data1[0] = data
    while 1:
      try:
        self.i2cbus.write_i2c_block_data(self.__addr ,reg ,data1)
        return
      except:
        print("please check connect!")
        time.sleep(1)
  '''
    @brief read the data from the register
    @param reg register address
    @param value read data
  '''
  def read_reg(self, reg):
    try:
      rslt = self.i2cbus.read_i2c_block_data(self.__addr ,reg ,1)
    except:
      rslt = -1
    return rslt

class DFRobot_H3LIS200DL_SPI(DFRobot_H3LIS200DL_SPI): 


  def __init__(self ,bus,cs):
    super(DFRobot_H3LIS200DL_SPI, self).__init__(0,__cs)
    #DFRobot_H3LIS200DL.__init__(0,0)
    #self._busy = GPIO(busy, GPIO.IN)
    self.__cs = GPIO(cs, GPIO.OUT)
    self.__cs.setOut(GPIO.LOW)
    self._spi = SPI(bus, 0)

    
  '''
    @brief writes data to a register
    @param reg register address
    @param value written data
  '''
  def write_reg(self, reg, data):
     self._spi.transfer(reg)
     self._spi.transfer(data)
  '''
    @brief read the data from the register
    @param reg register address
    @param value read data
  '''
  def read_reg(self, reg):
     self._spi.transfer(reg)
     time.sleep(0.01);
     return self._spi.readData(1);