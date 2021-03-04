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

CHIP                | Work Well    | Work Wrong  | Remarks
------------------ | :----------: | :----------| -----
LIS2DW12       |      √       |              |             
IIS2DLPC      |      √       |              |             

![正反面svg效果图](https://github.com/cdjq/DFRobot_LIS2DW12/raw/master/resources/images/SEN0245svg1.png)
![正反面svg效果图](https://github.com/cdjq/DFRobot_LIS2DW12/raw/master/resources/images/SEN0245svg2.png)
![正反面svg效果图](https://github.com/cdjq/DFRobot_LIS2DW12/raw/master/resources/images/SEN0245svg3.png)
![正反面svg效果图](https://github.com/cdjq/DFRobot_LIS2DW12/raw/master/resources/images/SEN0245svg4.png)
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
   * @return true(初始化成功)/fasle(初始化失败)
   */
  bool begin(void);
 
  /**
   * @brief Get chip id
   * @return 8 bit serial number
   */
  uint8_t getID();
 
  /**
   * @brief Software reset to restore the value of all registers to the default value
   */
  void softReset();
  
  /**
   * @brief 使芯片持续采集数据
   * @param enable  true(continuous update)/false( output registers not updated until MSB and LSB read)
   */
  void continRefresh(bool enable);
  
  /**
   * @brief Set the filter processing mode
   * @param path path of filtering
                 eLpfOnOut   = 0x00,/< low-pass filter path selected>/
                 eHpfOnOut   = 0x10,/<high-pass filter path selected>/
   */
  void setFilterPath(eFds_t path);

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
   * @param mode  16 power modes to choose from
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
   * @param freq  0-1600hz selection
                  eOdr_0hz            <测量关闭>
                  eOdr_1hz6_lp_only   <1.6hz>
                  eOdr_12hz5          <12.5hz>
                  eOdr_25hz        
                  eOdr_50hz        
                  eOdr_100hz       
                  eOdr_200hz       
                  eOdr_400hz       
                  eOdr_800hz       
                  eOdr_1k6hz       
   */
  void setDataRate(eFreq_t freq);
  
  /**
   * @brief 设置自由落体时间(或可以称作自由落体样本个数，只有产生足够多的自由落体样本，才会产生自由落体事件)
   * @param dur (0 ~ 31)
   * @n time = dur * (1/ODR)(unit:s)
     |                                  参数与时间之间的线性关系的示例                                                        |
     |------------------------------------------------------------------------------------------------------------------------|
     |                |                     |                          |                          |                           |
     |   frequen      |Data rate = 25 Hz    |   Data rate = 100 Hz     |  Data rate = 400 Hz      |   Data rate = 800 Hz      |
     |------------------------------------------------------------------------------------------------------------------------|
     |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
     |------------------------------------------------------------------------------------------------------------------------|
   */
  void setFreeFallDur(uint8_t dur);
  
  /**
   * @brief 选择在中断1引脚产生的中断事件
   * @param event  中断事件,当此事件产生会在中断1引脚产生电平跳变
                   eDoubleTap = 0x08,/< Double-tap recognition is routed to INT1 pad>/
                   eFFEvent = 0x10,/< Free-fall recognition is routed to INT1 pad>/
                   eWakeUpEvent = 0x20,/<Wakeup recognition is routed to INT1 pad>/
                   eSingleTap = 0x40,/<Single-tap recognition is routed to INT1 pad.>/
                   eTnt16d  = 0x80,/<6D recognition is routed to INT1 pad>/
   */
  void setPinInt1Route(eInt1Event_t event);
  
  /**
   * @brief 选择在中断2引脚产生的中断事件
   * @param event 中断事件,当此事件产生会在中断2引脚产生电平跳变
                   eBoot = 0x20,/< Boot state routed to INT2 pad.>/
                   eSleepChange = 0x40,/<Enable routing of SLEEP_STATE on INT2 pad>/
                   eSleepState  = 0x80,/<Sleep change status routed to INT2 pad>/
   */
  void setPinInt2Route(eInt2Event_t event);
  
  /**
   * @brief Latch interrupt Switches between latched ('1'-logic) and pulsed ('0'-logic) mode for 
     @n function source signals and interrupts routed to pins (wakeup, single/double-tap).
   * @param enable  true latched interrupt.
                    false pulsed interrupt
   */
  void latchInterrupt(bool enable);
  
  /**
   * @brief Set the wake-up duration
   * @param dur (0 ~ 3)
     @n time = dur * (1/ODR)(unit:s)
     |                                  参数与时间之间的线性关系的示例                                                        |
     |------------------------------------------------------------------------------------------------------------------------|
     |                |                     |                          |                          |                           |
     |   frequen      |Data rate = 25 Hz    |   Data rate = 100 Hz     |  Data rate = 400 Hz      |   Data rate = 800 Hz      |
     |------------------------------------------------------------------------------------------------------------------------|
     |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
     |------------------------------------------------------------------------------------------------------------------------|
   */
  void setWakeUpDur(uint8_t dur);

  /**
   * @brief Set the wake-up Threshold
   * @param th:unit(g),数值是在量程之内
   */
  void setWakeUpThreshold(float th);
  
  /**
   * @brief Sets the mode of motion detection
   * @param mode 运动检测模式
                eNoDetection        = 0,/<No detection>/
                eDetectActInact     = 1,/<Detect movement,the chip automatically goes to 12.5 Hz ODR in the low-power mode>/
                eDetectStatMotion   = 3,/<Detect Motion, the chip detects acceleration below a fixed threshold but does not change either ODR or operating mode>/
   */
  void setActMode(eSleepOn_t mode);
  
  /**
   * @brief Set the range
   * @param range  e2_g     = 2, /<±2g>/
                   e4_g     = 4, /<±4g>/
                   e8_g     = 8, /<±8g>/
                   e16_g    = 16, /< ±16g>/
   */
  void setRange(eRange_t range);
  
  /**
   * @brief enable detect click events in the Z direction
   * @param enable ture(使能点击检测)\false(禁用点击检测)
   */
  void enableTapDetectionOnZ(bool enable);
  
  /**
   * @brief enable detect click events in the Y direction
   * @param enable:ture(使能点击检测)\false(禁用点击检测)
   */
  void enableTapDetectionOnY(bool enable);

  /**
   * @brief enable detect click events in the X direction
   * @param enable ture(使能点击检测)\false(禁用点击检测)
   */
  void enableTapDetectionOnX(bool enable);

  /**
   * @brief Set the click threshold in the X direction
   * @param th Threshold(g),Can only be used in the range of ±2g
   */
  void setTapThresholdOnX(int32_t th);
  
  /**
   * @brief Set the click threshold in the Y direction
   * @param th Threshold(g),Can only be used in the range of ±2g
   */
  void setTapThresholdOnY(int32_t th);

  /**
   * @brief Set the click threshold in the Z direction
   * @param th Threshold(g),Can only be used in the range of ±2g
   */
  void setTapThresholdOnZ(int32_t th);
  
  /**
   * @brief Duration of maximum time gap for double-tap recognition. When double-tap 
   * @n recognition is enabled, this register expresses the maximum time between two 
   * @n successive detected taps to determine a double-tap event.
   * @param dur (0 ~ 15)
   * @n time = dur * (1/ODR)(unit:s)
     |                                  参数与时间之间的线性关系的示例                                                        |
     |------------------------------------------------------------------------------------------------------------------------|
     |                |                     |                          |                          |                           |
     |   frequen      |Data rate = 25 Hz    |   Data rate = 100 Hz     |  Data rate = 400 Hz      |   Data rate = 800 Hz      |
     |------------------------------------------------------------------------------------------------------------------------|
     |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
     |------------------------------------------------------------------------------------------------------------------------|
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
   * @param degree   eDegrees80   80°
                     eDegrees70   70°
                     eDegrees60   60°
                     eDegrees50   50°
   */
  void set6dThreshold(s6dTH_t degree);

  /**
   * @brief Read the acceleration in the x direction
   * @return  Acceleration data from x(mg),测量的量程为±2g,±4g,±8g或±16g,通过setRange()函数设置
   */
  int32_t readAccX();
  
  /**
   * @brief Read the acceleration in the y direction
   * @return  Acceleration data from y(mg),测量的量程为±2g,±4g,±8g或±16g,通过setRange()函数设置
   */
  int32_t readAccY();
  
  /**
   * @brief Read the acceleration in the z direction
   * @return  Acceleration data from z(mg),测量的量程为±2g,±4g,±8g或±16g,通过setRange()函数设置
   */
  int32_t readAccZ();
  
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
  eWakeupDir_t getWakeUpDir();

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
Raspberry Pi       |      √       |              |             | 


## History

- data 2021-3-4
- version V1.0


## Credits

Written by(li.feng@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))
