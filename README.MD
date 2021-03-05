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
                 eLPF   = 0x00,/< low-pass filter path selected>/
                 eHPF   = 0x10,/<high-pass filter path selected>/
   */
  void setFilterPath(ePath_t path);

  /**
   * @brief Set the  bandwidth of the data
   * @param bw   eRateDiv_2     = 0,/<Rate/2 (up to Rate = 800 Hz, 400 Hz when Rate = 1600 Hz)>/
                 eRateDiv_4     = 1,/<Rate/4 (High Power/Low power)>*
                 eRateDiv_10    = 2,/<Rate/10 (HP/LP)>/
                 eRateDiv_20    = 3,/< Rate/20 (HP/LP)>/
   */
  void setFilterBandwidth(eBWfilter_t bw);
  
  /**
   * @brief Set power mode
   * @param mode  16 power modes to choose from
                 eHighPerformance_14bit                   = 0x04,/<High-Performance Mode,14-bit resolution>/
                 eContLowPwr4_14bit                      = 0x03,/<Continuous measurement,Low-Power Mode 4(14-bit resolution)>/
                 eContLowPwr3_14bit                      = 0x02,/<Continuous measurement,Low-Power Mode 3(14-bit resolution)>/
                 eContLowPwr2_14bit                      = 0x01,/<Continuous measurement,Low-Power Mode 2(14-bit resolution)/
                 eContLowPwr1_12bit                  = 0x00,/<Continuous measurement,Low-Power Mode 1(12-bit resolution)>/
                 eSingleLowPwr4_14bit                    = 0x0b,/<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)>/
                 eSingleLowPwr3_14bit                    = 0x0a,/<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution)>/
                 eSingleLowPwr2_14bit                    = 0x09,/<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)>/
                 eSingleLowPwr1_12bit                = 0x08,/<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)>/
                 eHighPerformanceLowNoise_14bit           = 0x14,/<High-Performance Mode,Low-noise enabled,14-bit resolution>/
                 eContLowPwrLowNoise4_14bit              = 0x13,/<Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)>/
                 eContLowPwrLowNoise3_14bit              = 0x12,/<Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)>/
                 eContLowPwrLowNoise2_14bit              = 0x11,/<Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)>/
                 eContLowPwrLowNoise1_12bit          = 0x10,/<Continuous measurement,Low-Power Mode 1(12-bit resolution,Low-noise enabled)>/
                 eSingleLowPwrLowNoise4_14bit            = 0x1b,/<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled>/
                 eSingleLowPwrLowNoise3_14bit            = 0x1a,/<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled>/
                 eSingleLowPwrLowNoise2_14bit            = 0x19,/<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled>/
                 eSingleLowLowNoisePwr1_12bit        = 0x18,/<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled>/
                  */
  void setPowerMode(ePowerMode_t mode);
  
  /**
   * @brief Chip data collection rate setting
   * @param rate  0-1600hz selection
                  eRate_0hz            <测量关闭>
                  eRate_1hz6_lp_only   <1.6hz>
                  eRate_12hz5          <12.5hz>
                  eRate_25hz        
                  eRate_50hz        
                  eRate_100hz       
                  eRate_200hz       
                  eRate_400hz       
                  eRate_800hz       
                  eRate_1k6hz       
   */
  void setDataRate(eRate_t rate);
  
  /**
   * @brief 设置自由落体时间,也可以称作自由落体样本个数，只有产生足够多的自由落体样本，才会产生自由落体事件
   * @param dur duration(0 ~ 3)
   * @n time = dur * (1/rate)(unit:s)
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
               eDoubleTap   = 0x08,/< Double-tap recognition is routed to INT1 pad>/
               eFreeFall     = 0x10,/< Free-fall recognition is routed to INT1 pad>/
               eWakeUp = 0x20,/<Wakeup recognition is routed to INT1 pad>/
               eSingleTap   = 0x40,/<Single-tap recognition is routed to INT1 pad.>/
               e6D      = 0x80,/<6D recognition is routed to INT1 pad>/
   */
  void setInt1Event(eInt1Event_t event);
  
  /**
   * @brief 选择在中断2引脚产生的中断事件
   * @param event 中断事件,当此事件产生会在中断2引脚产生电平跳变
                 eSleepChange = 0x40,/<Sleep change status routed to INT2 pad>/
                 eSleepState  = 0x80,/<Enable routing of SLEEP_STATE on INT2 pad>/
   */
  void setInt2Event(eInt2Event_t event);
  
  /**
   * @brief lock interrupt Switches between latched ('1'-logic) and pulsed ('0'-logic) mode for 
     @n function source signals and interrupts routed to pins (wakeup, single/double-tap).
   * @param enable  true lock interrupt.
                    false pulsed interrupt
   */
  void lockInterrupt(bool enable);
  
  /**
   * @brief Set the wake-up duration
   * @param dur duration(0 ~ 3)
     @n time = dur * (1/rate)(unit:s)
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
   * @param th:unit(mg),数值是在量程之内
   */
  void setWakeUpThreshold(float th);
  
  /**
   * @brief Sets the mode of motion detection
   * @param mode 运动检测模式
                eNoDetection        = 0,/<No detection>/
                eDetectAct     = 1,/<Detect movement,the chip automatically goes to 12.5 Hz rate in the low-power mode>/
                eDetectStatMotion   = 3,/<Detect Motion, the chip detects acceleration below a fixed threshold but does not change either rate or operating mode>/
   */
  void setActMode(eActDetect_t mode);
  
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
   * @param th Threshold(mg),Can only be used in the range of 0~2g
   */
  void setTapThresholdOnX(float th);
  
  /**
   * @brief Set the click threshold in the Y direction
   * @param th Threshold(mg),Can only be used in the range of 0~2g
   */
  void setTapThresholdOnY(float th);

  /**
   * @brief Set the click threshold in the Z direction
   * @param th Threshold(mg),Can only be used in the range of 0~2g
   */
  void setTapThresholdOnZ(float th);
  
  /**
   * @brief Duration of maximum time gap for double-tap recognition. When double-tap 
   * @n recognition is enabled, this register expresses the maximum time between two 
   * @n successive detected taps to determine a double-tap event.
   * @param dur duration(0 ~ 3)
   * @n time = dur * (1/rate)(unit:s)
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
   * @param degree   eDegrees80   (80°)
                     eDegrees70   (70°)
                     eDegrees60   (60°)
                     eDegrees50   (50°)
   */
  void set6DThreshold(e6DTh_t degree);

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
   * @return true(a change in position is detected)/false(no event detected)
   */
  bool ia6DDetect();
  
  /**
   * @brief 获取传感器现在的位置
   * @return    eXDown  /<X is now down>/
                eXUp    /<X is now up>/
                eYDown  /<Y is now down>/
                eYUp    /<Y is now up>/
                eZDown  /<Z is now down>/
                eZUp    /<Z is now up>/
   */
  eOrient_t getOrient();
  
  /**
   * @brief 点击检测
   * @return   eSingleClick       /<Single click>/
               eDoubleClick       /<double click>/
               eNoClick,          //没有点击产生
                */
  eTap_t tapDetect();
  
  /**
   * @brief 点击方向的源头检测
   * @return   eDirXUp   /<从 X 正方向发生的点击事件>/
               eDirXDown /<从 X 负方向发生的点击事件>/
               eDirYUp   /<从 Y 正方向发生的点击事件>/
               eDirYDown /<从 Y 负方向发生的点击事件>/
               eDirZUp   /<从 Z 正方向发生的点击事件>/
               eDirZDown /<从 Z 负方向发生的点击事件>/
   */
  eTapDir_t getTapDirection();
  
  /**
   * @brief 唤醒的运动方向检测
   * @return   eDirX    /<X方向的运动唤醒芯片>/
               eDirY    /<Y方向的运动唤醒芯片>/
               eDirZ    /<Z方向的运动唤醒芯片>/
               eDirError,
   */
  eWakeUpDir_t getWakeUpDir();

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
