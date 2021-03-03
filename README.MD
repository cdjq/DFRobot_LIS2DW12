# DFRobot_LIS
LIS系列三轴加速度传感器

CHIP                | Work Well    | Work Wrong  | Remarks
------------------ | :----------: | :----------| -----
H3LIS200DL       |      √       |              |             
LIS331HH      |      √       |              |  

![正反面svg效果图](https://github.com/cdjq/DFRobot_LIS/raw/master/resources/images/SEN0245svg1.png)
![正反面svg效果图](https://github.com/cdjq/DFRobot_LIS/raw/master/resources/images/SEN0245svg2.png)
![正反面svg效果图](https://github.com/cdjq/DFRobot_LIS/raw/master/resources/images/SEN0245svg3.png)
![正反面svg效果图](https://github.com/cdjq/DFRobot_LIS/raw/master/resources/images/SEN0245svg4.png)
## 产品链接（链接到英文商城）
    SKU：产品名称
    SKU：产品名称
    SKU：产品名称
    SKU：产品名称
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

Provide an Arduino library to get Three-axis acceleration by reading data from LIS.

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
  DFRobot_LIS();
  /**
   * @brief Initialize the function
   * @return true(成功)/false(失败)
   */
  bool begin(void);
 
  /**
   * @brief Get chip id
   * @return 8 bit serial number
   */
  uint8_t getID();
  
  /**
   * @brief Enable interrupt
   * @param source Interrupt pin selection
              eINT1 = 0,/<int1 >/
              eINT2,/<int2>/
   * @param event Interrupt event selection
                   eXLowerThanTh ,/<The acceleration in the x direction is less than the threshold>/
                   eXHigherThanTh ,/<The acceleration in the x direction is greater than the threshold>/
                   eYLowerThanTh,/<The acceleration in the y direction is less than the threshold>/
                   eYHigherThanTh,/<The acceleration in the y direction is greater than the threshold>/
                   eZLowerThanTh,/<The acceleration in the z direction is less than the threshold>/
                   eZHigherThanTh,/<The acceleration in the z direction is greater than the threshold>/
   */
  void enableInterruptEvent(eInterruptSource_t source, eInterruptEvent_t event);
  
  /**
   * @brief Set the measurement range
   * @param range Range(g)
                  eH3lis200dl_100g, //±100g
                  eH3lis200dl_200g, //±200g
                  
                  eLis331hh_6g = 6,//±6g
                  eLis331hh_12g = 12 //±12g
                  eLis331hh_24g = 24 //±24g  
    @return true(设置成功)/false(设置失败)
   */
  bool setRange(eRange_t range);
  
  /**
   * @brief Set data measurement rate
   * @param rate rate(HZ)
                  ePowerDown_0HZ   //测量关闭
                  eLowPower_halfHZ //0.5 hz
                  eLowPower_1HZ
                  eLowPower_2HZ
                  eLowPower_5HZ
                  eLowPower_10HZ
                  eNormal_50HZ
                  eNormal_100HZ
                  eNormal_400HZ
                  eNormal_1000HZ
   */
  void setAcquireRate(ePowerMode_t rate);
  
  /**
   * @brief Set data filtering mode
   * @param mode Four modes
                 eCutOffMode1 = 0,
                 eCutOffMode2,
                 eCutOffMode3,
                 eCutOffMode4,
                 eShutDown,  无过滤
     eg：在50HZ的频率下,选择eCutOffMode1,滤波后的频率为 1 HZ
   *|---------------------------High-pass filter cut-off frequency configuration-----------------------------|
   *|--------------------------------------------------------------------------------------------------------|
   *|                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
   *|   mode         |Data rate = 50 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 1000 Hz |
   *|--------------------------------------------------------------------------------------------------------|
   *|  eCutOffMode1  |     1           |         2            |            8         |             20        |
   *|--------------------------------------------------------------------------------------------------------|
   *|  eCutOffMode2  |    0.5          |         1            |            4         |             10        |
   *|--------------------------------------------------------------------------------------------------------|
   *|  eCutOffMode3  |    0.25         |         0.5          |            2         |             5         |
   *|--------------------------------------------------------------------------------------------------------|
   *|  eCutOffMode4  |    0.125        |         0.25         |            1         |             2.5       |
   *|--------------------------------------------------------------------------------------------------------|
   */
  void setHFilterMode(eHighPassFilter_t mode);

  /**
   * @brief Set the threshold of interrupt source 1 interrupt
   * @param threshold 设置的阈值在量程之内(unit:g)
   */
  void setInt1Th(uint8_t threshold);

  /**
   * @brief Set interrupt source 2 interrupt generation threshold
   * @param threshold 设置的阈值在量程之内(unit:g）
   */
  void setInt2Th(uint8_t threshold);

  /**
   * @brief Enable sleep wake function
   * @param enable true(enable)\false(disable)
   * @return false 表示使能失败/true 表示使能成功
   */
  bool enableSleep(bool enable);
  
  /**
   * @brief Check whether the interrupt event'event' is generated in interrupt 1
   * @param event Interrupt event
                   eXLowerThanTh ,/<The acceleration in the x direction is less than the threshold>/
                   eXHigherThanTh ,/<The acceleration in the x direction is greater than the threshold>/
                   eYLowerThanTh,/<The acceleration in the y direction is less than the threshold>/
                   eYHigherThanTh,/<The acceleration in the y direction is greater than the threshold>/
                   eZLowerThanTh,/<The acceleration in the z direction is less than the threshold>/
                   eZHigherThanTh,/<The acceleration in the z direction is greater than the threshold>/
   * @return true 产生了此事件
             false 未产生此事件
   */
  bool getInt1Event(eInterruptEvent_t event);

  /**
   * @brief Check whether the interrupt event'event' is generated in interrupt 2
   * @param event Interrupt event
                   eXLowerThanTh ,/<The acceleration in the x direction is less than the threshold>/
                   eXHigherThanTh ,/<The acceleration in the x direction is greater than the threshold>/
                   eYLowerThanTh,/<The acceleration in the y direction is less than the threshold>/
                   eYHigherThanTh,/<The acceleration in the y direction is greater than the threshold>/
                   eZLowerThanTh,/<The acceleration in the z direction is less than the threshold>/
                   eZHigherThanTh,/<The acceleration in the z direction is greater than the threshold>/
   * @return true 产生了此事件
             false 未产生此事件
   */
  bool getInt2Event(eInterruptEvent_t event);
  
  /**
   * @brief Get the acceleration in the x direction
   * @return acceleration from x 
   */
  long readAccX();
  
  /**
   * @brief Get the acceleration in the y direction
   * @return acceleration from y
   */
  long readAccY();
  
  /**
   * @brief Get the acceleration in the z direction
   * @return acceleration from z
   */
  long readAccZ();
  
  /**
   * @brief Get the acceleration in the three directions of xyz
   * @param accx 储存x方向加速度的变量
   * @param accy 储存y方向加速度的变量
   * @param accz 储存z方向加速度的变量
   * @return true(成功获取数据)/false(数据未准备好)
   */
  bool getAcceFromXYZ(long &accx,long &accy,long &accz);

  /**
   * @brief 获取传感器是否处于睡眠模式
   * @return true(处于睡眠模式)/false(处于正常模式)
   */
  bool getSleepState();
  
  /**
   * @brief 设置睡眠状态的标志
   * @param into true(将现在的模式标记为睡眠模式)
                 false(将现在的模式标记为正常模式)
   */
  void setSleepFlag(bool into);
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |      √       |              |             | 
FireBeetle-ESP8266        |      √       |              |             | 
FireBeetle-ESP32        |      √       |              |             | 
Arduino MEGA2560        |      √       |              |             | 
Arduino Leonardo|      √       |              |             | 
Micro:bit        |      √       |              |             | 
FireBeetle-M0        |      √       |              |             | 
Raspberry Pi      |      √       |              |             | 

## History

- data 2021-2-1
- version V1.0


## Credits

Written by(li.feng@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))
