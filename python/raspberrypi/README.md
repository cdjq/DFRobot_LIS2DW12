# DFRobot_LIS
The H3LIS200DL is a low-power high performance 3-axis linear accelerometer 
belonging to the “nano” family, with digital I2C/SPI 
serial interface standard output. <br>
The device features ultra-low-power operational 
modes that allow advanced power saving and 
smart sleep-to-wakeup functions.<br>
The H3LIS200DL has dynamically user selectable full scales of ±100g/±200g and is 
capable of measuring accelerations with output 
data rates from 0.5 Hz to 1 kHz.<br>
The H3LIS200DL is available in a small thin 
plastic land grid array package (LGA) and is 
guaranteed to operate over an extended 
temperature range from -40 °C to +85 °C.<br>

The LIS331HH is an ultra low-power high 
performance high full-scale three axes linear 
accelerometer belonging to the “nano” family, with 
digital I2C/SPI serial interface standard output. 
The device features ultra low-power operational 
modes that allow advanced power saving and 
smart sleep to wake-up functions. 
The LIS331HH has dynamically user selectable 
full scales of ±6g/±12g/±24g and it is capable of 
measuring accelerations with output data rates 
from 0.5 Hz to 1 kHz. The self-test capability 
allows the user to check the funct

CHIP                | Work Well    | Work Wrong  | Remarks
------------------ | :----------: | :----------| -----
H3LIS200DL       |      √       |              |             
LIS331HH      |      √       |              |   
## DFRobot_LIS Library for RaspberryPi
---------------------------------------------------------

Provide an RaspberryPi library to get Three-axis acceleration by reading data from H3LIS200DL and LIS331HH.

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

Provide an RaspberryPi library to get Three-axis acceleration by reading data from H3LIS200DL and LIS331HH.

## Installation

下载DFRobot_LIS文件到树莓派文件目录下,然后运行下面两行命令行，使用此传感器:
```
cd DFRobot_LIS/python/raspberry/examples/LIS331HH/get_acceleration
python get_acceleration.py
```


## Methods

```python
  '''
    @brief Initialize the function
    @return return True(成功)/False(失败)
  '''
  begin(self)
  
  '''
    @brief get chip id
    @return 8 bit serial number
  '''
  get_id(self)

  '''
    @brief Set the measurement range
    @param range Range(g)
                 H3LIS200DL_100G = 100 #±100G
                 H3LIS200DL_200G = 200 #±200G
                 LIS331HH_6G     #±6G
                 LIS331HH_12G    #±12G
                 LIS331HH_24G    #±24G
  '''
  set_range(self,range_r)

  '''
    @brief Set data measurement rate
    @param rate rate(HZ)
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
  set_acquire_rate(self, rate)

  '''
    @brief Set the threshold of interrupt source 1 interrupt
    @param threshold Threshold(g)
  '''
  set_int1_th(self,threshold)

  '''
    @brief Set interrupt source 2 interrupt generation threshold
    @param threshold Threshold(g)
  '''
  set_int2_th(self,threshold)
  
  '''
    @brief Enable interrupt
    @source Interrupt pin selection
             INT_1 = 0,/<int pad 1 >/
             INT_2,/<int pad 2>/
    @param event Interrupt event selection
             X_LOWERTHAN_TH     = 0x1<The acceleration in the x direction is less than the threshold>
             X_HIGHERTHAN_TH  = 0x2<The acceleration in the x direction is greater than the threshold>
             Y_LOWERTHAN_TH     = 0x4<The acceleration in the y direction is less than the threshold>
             Y_HIGHERTHAN_TH  = 0x8<The acceleration in the y direction is greater than the threshold>
             Z_LOWERTHAN_TH     = 0x10<The acceleration in the z direction is less than the threshold
             Z_HIGHERTHAN_TH  = 0x20<The acceleration in the z direction is greater than the threshold>
             EVENT_ERROR      = 0 <No event>
  '''
  enable_int_event(self,source,event)

  '''
    @brief Check whether the interrupt event'event' is generated in interrupt 1
    @param event Interrupt event
             X_LOWERTHAN_TH     = 0x1<The acceleration in the x direction is less than the threshold>
             X_HIGHERTHAN_TH  = 0x2<The acceleration in the x direction is greater than the threshold>
             Y_LOWERTHAN_TH     = 0x4<The acceleration in the y direction is less than the threshold>
             Y_HIGHERTHAN_TH  = 0x8<The acceleration in the y direction is greater than the threshold>
             Z_LOWERTHAN_TH     = 0x10<The acceleration in the z direction is less than the threshold
             Z_HIGHERTHAN_TH  = 0x20<The acceleration in the z direction is greater than the threshold>
             EVENT_ERROR      = 0 <No event>
    @return True ：产生了此事件
            False：未产生此事件
  '''
  get_int1_event(self,event)
         
  '''
    @brief Check whether the interrupt event'event' is generated in interrupt 2
    @param event Interrupt event
             X_LOWERTHAN_TH     = 0x1<The acceleration in the x direction is less than the threshold>
             X_HIGHERTHAN_TH  = 0x2<The acceleration in the x direction is greater than the threshold>
             Y_LOWERTHAN_TH     = 0x4<The acceleration in the y direction is less than the threshold>
             Y_HIGHERTHAN_TH  = 0x8<The acceleration in the y direction is greater than the threshold>
             Z_LOWERTHAN_TH     = 0x10<The acceleration in the z direction is less than the threshold
             Z_HIGHERTHAN_TH  = 0x20<The acceleration in the z direction is greater than the threshold>
             EVENT_ERROR      = 0 <No event>
    @return True ：产生了此事件
            False：未产生此事件
  '''
  get_int2_event(self,source)

  '''
    @brief Enable sleep wake function
    @param enable True(enable)/False(disable)
  '''
  enable_sleep(self, enable)
  
  '''
    @brief Set data filtering mode
    @param mode Four modes
                CUTOFF_MODE1 = 0
                CUTOFF_MODE2 = 1
                CUTOFF_MODE3 = 2
                CUTOFF_MODE4 = 3
     eg：在50HZ的频率下,选择eCutOffMode1,滤波后的频率为 1 HZ
                            High-pass filter cut-off frequency configuration
    |--------------------------------------------------------------------------------------------------------|
    |                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
    |   mode         |Data rate = 50 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 1000 Hz |
    |--------------------------------------------------------------------------------------------------------|
    |  CUTOFF_MODE1  |     1           |         2            |            8         |             20        |
    |--------------------------------------------------------------------------------------------------------|
    |  CUTOFF_MODE2  |    0.5          |         1            |            4         |             10        |
    |--------------------------------------------------------------------------------------------------------|
    |  CUTOFF_MODE3  |    0.25         |         0.5          |            2         |             5         |
    |--------------------------------------------------------------------------------------------------------|
    |  CUTOFF_MODE4  |    0.125        |         0.25         |            1         |             2.5       |
    |--------------------------------------------------------------------------------------------------------|
  '''
  set_filter_mode(self,mode)

  '''
    @brief Get the acceleration in the three directions of xyz
    @return Three-axis acceleration 
  '''
  read_acce_xyz(self)

```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Raspberry Pi              |      √         |            |             | 



## History

- data 2021-1-26
- version V1.0


## Credits

Written by(li.feng@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))
