# DFRobot_LIS2DW12
The IIS2DLPC is an ultra-low-power high-performance 
three-axis linear accelerometer with digital I²C/SPI 
output interface which leverages on the robust and 
mature manufacturing processes already used for the 
production of micromachined accelerometers.<br>
The IIS2DLPC has user-selectable full scales of 
±2g/±4g/±8g/±16g and is capable of measuring 
accelerations with output data rates from 1.6 Hz to 
1600 Hz.<br>

The LIS2DW12 is an ultra-low-power high-performance three-axis linear
accelerometer belonging to the “femto” family which leverages on the robust and
mature manufacturing processes already used for the production of micromachined
accelerometers.
The LIS2DW12 has user-selectable full scales of ±2g/±4g/±8g/±16g and is capable of
measuring accelerations with output data rates from 1.6 Hz to 1600 Hz.


## DFRobot_LIS2DW12 Library for Arduino
---------------------------------------------------------

Provide an Arduino library to get Three-axis acceleration by reading data from IIS2DLPC and LIS2DW12.

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary


Provide an Arduino library to get Three-axis acceleration by reading data from IIS2DLPC and LIS2DW12.


## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++

  DFRobot_LIS2DW12();
  
  /**
   * @brief Initialize the function
   * @return Return 0 indicates a successful initialization, while other values indicates failure and return to error code.
   */
  uint8_t begin(void);
 
  /**
   * @brief Get chip id
   * @return Returns the 8 bit serial number
   */
  uint8_t getID();
 
  /**
   * @brief Software reset to restore the value of all registers to the default value
   */
  void softReset();
  
  /**
   * @brief Choose whether to continuously let the chip collect data
   * @param enable  true(持续采集数据)/false(单次采集数据)
   */
  void continRefresh(bool enable);
  
  /**
   * @brief Set the filter processing mode
   * @param fds  Three modes of filtering
                 eLpfOnOut        = 0x00,/<Low pass filter>/
                 eHighPassOnOut   = 0x10,/<High pass filter>/
   */
  void setFilterPath(eFds_t fds);

  /**
   * @brief Set the  bandwidth of the data
   * @param bw   eOdrDiv_2     = 0,/<ODR/2 (up to ODR = 800 Hz, 400 Hz when ODR = 1600 Hz)>/
                 eOdrDiv_4     = 1,/<ODR/4 (High Power/Low power)>*
                 eOdrDiv_10    = 2,/<ODR/10 (HP/LP)>/
                 eOdrDiv_20    = 3,/< ODR/20 (HP/LP)>/
   */
  void setFilterBandwidth(eBWfilter_t bw);
  
  /**
   * @brief Set power mode
   * @param mode: 16 power modes to choose from
                 eHighPerformance                   = 0x04, /<High-Performance Mode>/
                 eContLowPwr_4                      = 0x03,/<Continuous measurement,Low-Power Mode 4(14-bit resolution)>/
                 eContLowPwr_3                      = 0x02,/<Continuous measurement,Low-Power Mode 3(14-bit resolution)>/
                 eContLowPwr_2                      = 0x01,/<Continuous measurement,Low-Power Mode 2(14-bit resolution)>/
                 eContLowPwr_12bit                  = 0x00,/<Continuous measurement,Low-Power Mode 1(12-bit resolution)>/
                 eSingleLowPwr_4                    = 0x0b,/<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)>/
                 eSingleLowPwr_3                    = 0x0a,/<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution)>/
                 eSingleLowPwr_2                    = 0x09,/<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)>/
                 eSingleLowPwr_12bit                = 0x08,/<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)>/
                 eHighPerformanceLowNoise           = 0x14,/<High-Performance Mode,Low-noise enabled>/
                 eContLowPwrLowNoise_4              = 0x13,/<Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)>/
                 eContLowPwrLowNoise_3              = 0x12,/<Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)>/
                 eContLowPwrLowNoise_2              = 0x11,/<Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)>/
                 eContLowPwrLowNoise_12bit          = 0x10,/<Continuous measurement,Low-Power Mode 1(14-bit resolution,Low-noise enabled)>/
                 eSingleLowPwrLowNoise_4           = 0x1b,/<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled>/
                 eSingleLowPwrLowNoise_3           = 0x1a,/<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled>/
                 eSingleLowPwrLowNoise_2           = 0x19,/<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled>/
                 eSingleLowLowNoisePwr_12bit       = 0x18,/<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled>/
   */
  void setPowerMode(ePowerMode_t mode);
  
  /**
   * @brief Chip data collection rate setting
   * @param mode  0-1600hz selection
                  eOdr_0hz         
                  eOdr_1hz6_lp_only
                  eOdr_12hz5       
                  eOdr_25hz        
                  eOdr_50hz        
                  eOdr_100hz       
                  eOdr_200hz       
                  eOdr_400hz       
                  eOdr_800hz       
                  eOdr_1k6hz       
                  eSetSwTrig       
                  eSetPinTrig      
   */
  void setDataRate(eOdr_t odr);
  
  /**
   * @brief 设置自由落体时间
   * @param dur  Free fall duration (0~31), the larger the value, the longer the free fall time is needed to be detected
     @n 1 LSB = 1 * 1/ODR (measurement frequency)
     @n example：
     |                                       参数与时间之间的线性关系                                         |
     |--------------------------------------------------------------------------------------------------------|
     |                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
     |   dur          |Data rate = 25 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 800 Hz  |
     |--------------------------------------------------------------------------------------------------------|
     |  n             |n*(1s/25)= n*40ms|  n*(1s/100)= n*10ms  |  n*(1s/400)= n*2.5ms |  n*(1s/800)= n*1.25ms |
     |--------------------------------------------------------------------------------------------------------|
   */
  void setFrDur(uint8_t dur);
  
  /**
   * @brief Set the interrupt source of the int1 pin
   * @param event  Several interrupt events, after setting, when an event is generated, a level transition will be generated on the int1 pin
                   eDoubleTap = 0x08,/< Double-tap recognition is routed to INT1 pad>/
                   eFfEvent = 0x10,/< Free-fall recognition is routed to INT1 pad>/
                   eWakeupEvent = 0x20,/<Wakeup recognition is routed to INT1 pad>/
                   eSingleTap = 0x40,/<Single-tap recognition is routed to INT1 pad.>/
                   eTnt16d  = 0x80,/<6D recognition is routed to INT1 pad>/
   */
  void setPinInt1Route(eInt1Event_t event);
  
  /**
   * @brief Set interrupt source of int2 pin
   * @param event  Several interrupt events, after setting, when an event is generated, a level transition will be generated on the int2 pin
                   eBoot = 0x20,/< Boot state routed to INT2 pad.>/
                   eSleepChange = 0x40,/<Enable routing of SLEEP_STATE on INT2 pad>/
                   eSleepState  = 0x80,/<Sleep change status routed to INT2 pad>/
   */
  void setPinInt2Route(eInt2Event_t event);
  
  /**
   * @brief Latch interrupt
   * @param enable  Latched Interrupt. Switches between latched ('1'-logic) and pulsed ('0'-logic) mode for 
      function source signals and interrupts routed to pins (wakeup, single/double-tap).
   */
  void latchInterrupt(bool enable);
  
  /**
   * @brief Set the wake-up duration
   * @param dur Wakeup duration (0~3)
     @n 1 LSB = 1 * 1/ODR (measurement frequency)
     @n example：
     |                                       参数与时间之间的线性关系                                         |
     |--------------------------------------------------------------------------------------------------------|
     |                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
     |   dur          |Data rate = 25 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 800 Hz  |
     |--------------------------------------------------------------------------------------------------------|
     |  n             |n*(1s/25)= n*40ms|  n*(1s/100)= n*10ms  |  n*(1s/400)= n*2.5ms |  n*(1s/800)= n*1.25ms |
     |--------------------------------------------------------------------------------------------------------|
   */
  void setWakeupDur(uint8_t dur);

  /**
   * @brief Set the wake-up Threshold
   * @param th:unit(g),数值是在量程之内
   */
  void setWakeupThreshold(float th);
  
  /**
   * @brief Sets the mode of motion detection
   * @param th:    eNoDetection 
                   eDetectActInact  
                   eDetectStatMotion
   */
  void setActMode(eSleepOn_t mode);
  
  /**
   * @brief Set the range
   * @param range: e2_g     = 0, /<±2g>/
                   e4_g     = 1, /<±4g>/
                   e8_g     = 2, /<±8g>/
                   e16_g    = 3, /< ±16g>/
   */
  void setRange(eRange_t range);
  
  /**
   * @brief Set to detect click events in the Z direction
   * @param enable:ture(使能点击检测)\false(禁用点击检测)
   */
  void enableTapDetectionOnZ(bool enable);
  
  /**
   * @brief Set to detect click events in the Y direction
   * @param enable:ture(使能点击检测)\false(禁用点击检测)
   */
  void enableTapDetectionOnY(bool enable);

  /**
   * @brief Set to detect click events in the X direction
   * @param enable:ture(使能点击检测)\false(禁用点击检测)
   */
  void enableTapDetectionOnX(bool enable);

  /**
   * @brief Set the click threshold in the X direction
   * @param th:Threshold(g),Can only be used in the range of ±2g
   */
  void setTapThresholdOnX(float th);
  
  /**
   * @brief Set the click threshold in the Y direction
   * @param th:Threshold(g),Can only be used in the range of ±2g
   */
  void setTapThresholdOnY(float th);

  /**
   * @brief Set the click threshold in the Z direction
   * @param th:Threshold(g),Can only be used in the range of ±2g
   */
  void setTapThresholdOnZ(float th);
  
  /**
   * @brief 设置双击的两次点击之间的间隔时间
   * @param th 1 LSB = 32 * 1/ODR(0~15)
     @n ODR:Data acquisition frequency
     @n example 
     |                                       参数与时间之间的线性关系                                         |
     |--------------------------------------------------------------------------------------------------------|
     |                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
     |   dur          |Data rate = 25 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 800 Hz  |
     |--------------------------------------------------------------------------------------------------------|
     |  n             |n*(1s/25)= n*40ms|  n*(1s/100)= n*10ms  |  n*(1s/400)= n*2.5ms |  n*(1s/800)= n*1.25ms |
     |--------------------------------------------------------------------------------------------------------|
   */
  void setTapDur(uint8_t dur);
  
  /**
   * @brief Set the click detection mode
   * @param mode     eOnlySingle   //检测单击
                      eBothSingleDouble //检测单击和双击
   */
  void setTapMode(sTapMode_t mode);

  /**
   * @brief Set Thresholds for 4D/6D，当转动的阈值大于指定角度时,就发生方向转变的事件
   * @param degree:  eDegrees80   80°
                     eDegrees70   70°
                     eDegrees60   60°
                     eDegrees50   50°
   */
  void set6dThreshold(s6dTH_t degree);

  /**
   * @brief Read the acceleration in the x direction
   * @return Acceleration data(g)
   */
  float readAccX();
  
  /**
   * @brief Read the acceleration in the y direction
   * @return  Acceleration data(g)
   */
  float readAccY();
  
  /**
   * @brief Read the acceleration in the z direction
   * @return Acceleration data(g)
   */
  float readAccZ();
  
  /**
   * @brief 检测是否有运动产生
   * @return true(产生运动)/false(传感器未运动)
   */
  bool actDetect();
  
  /**
   * @brief 自由落体运动检测
   * @return true(检测到自由落体运动)/false(未检测到自由落体运动)
   */
  bool freeFallDetect();
  
  /**
   * @brief Source of change in position portrait/landscape/face-up/face-down.
   * @return true( no event detected)/false(a change in position is detected)
   */
  bool ia6dDetect();
  
  /**
   * @brief 获取传感器现在的位置
   * @return    eXdown = 0 ,/<X is now down>/
                eXup   = 1 ,/<X is now up>/
                eYdown = 2 ,/<Y is now down>/
                eYup   = 3 ,/<Y is now up>/
                eZdown = 4 ,/<Z is now down>/
                eZup   = 5 ,/<Z is now up>/
   */
  eOrient_t getOrient();
  
  /**
   * @brief 点击检测
   * @return   eSingleClick  = 0 ,/<click>/
               eDoubleClick      ,/<double click>/
               eNoClick,          //没有点击产生
                */
  eTap_t tapDetect();
  
  /**
   * @brief 点击方向的源头检测
   * @return   eDirXup   = 0,/<从 X 正方向发生的点击事件>/
               eDirXdown = 1,/<从 X 负方向发生的点击事件>/
               eDirYup   = 2,/<从 Y 正方向发生的点击事件>/
               eDirYdown = 3,/<从 Y 负方向发生的点击事件>/
               eDirZup   = 4,/<从 Z 正方向发生的点击事件>/
               eDirZdown = 5,/<从 Z 负方向发生的点击事件>/
   */
  eTapDir_t getTapDirection();
  
  /**
   * @brief 唤醒的运动方向检测
   * @return   eDirX = 0,/<X方向的运动唤醒芯片>/
               eDirY = 1,/<Y方向的运动唤醒芯片>/
               eDirZ = 2,/<Z方向的运动唤醒芯片>/
               eDirError,
   */
  eWakeupDir_t getWakeupDir();

```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
FireBeetle-ESP8266        |      √       |              |             | 
FireBeetle-ESP32        |      √       |              |             | 
Arduino MEGA2560        |      √       |              |             | 
Arduino Leonardo|      √       |              |             | 
microbit        |      √       |              |             | 
FireBeetle-M0        |      √       |              |             | 
raspberry pi 3      |      √       |              |             | 

CHIP                | Work Well    | Work Wrong  | Remarks
------------------ | :----------: | :----------| -----
LIS2DW12       |      √       |              |             
IIS2DLPC      |      √       |              |              
## History

- data 2020-12-31
- version V1.0


## Credits

Written by(li.feng@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))
