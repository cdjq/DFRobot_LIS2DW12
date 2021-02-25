/*!
 * @file DFRobot_LIS2DW12.h
 * @brief Define the basic structure of class DFRobot_LIS2DW12
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2020-12-23
 * @get from https://www.dfrobot.com
 * @https://github.com/DFRobot/DFRobot_LIS2DW12
 */

#ifndef DFROBOT_LIS2DW12_H
#define DFROBOT_LIS2DW12_H
 #include "Arduino.h"

#include <Wire.h>
#include <SPI.h>
//#define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define LIS2DW12_I2C_ADDR  (0x19)  /*LIS2DW12 IIC address*/
#define IIS2DLPC_I2C_ADDR  (0x19)  /*IIS2DLPC IIC address*/

#define ERR_OK              0      //ok
#define ERR_DATA_BUS       -1      //error in data bus
#define ERR_IC_VERSION     -2      //chip version mismatch


class DFRobot_LIS2DW12
{
public:
  #define REG_CARD_ID      0x0F     /*The chip id*/
  #define REG_CTRL_REG1    0x20     /*Control register 1*/
  #define REG_CTRL_REG4    0x23     /*Control register 2*/
  #define REG_CTRL_REG2    0x21     /*Control register 3*/
  #define REG_CTRL_REG3    0x22     /*Control register 4*/
  #define REG_CTRL_REG5    0x24     /*Control register 5*/
  #define REG_CTRL_REG6    0x25     /*Control register 6*/
  #define REG_CTRL_REG7    0x3F     /*Control register 7*/
  #define REG_STATUS_REG   0x27     /*Status register*/
  #define REG_OUT_X_L      0x28     /*The low order of the X-axis acceleration register*/
  #define REG_OUT_X_H      0x29     /*The high point of the X-axis acceleration register*/
  #define REG_OUT_Y_L      0x2A     /*The low order of the Y-axis acceleration register*/
  #define REG_OUT_Y_H      0x2B     /*The high point of the Y-axis acceleration register*/
  #define REG_OUT_Z_L      0x2C     /*The low order of the Z-axis acceleration register*/
  #define REG_OUT_Z_H      0x2D     /*The high point of the Z-axis acceleration register*/
  #define REG_WAKE_UP_DUR  0x35   
  #define REG_FREE_FALL    0x36     /*Free fall event register*/
  #define REG_STATUS_DUP   0x37     /*Interrupt event status register*/
  #define REG_WAKE_UP_SRC  0x38     /*Wakeup source register*/
  #define REG_TAP_SRC      0x39     /*Tap source register*/
  #define REG_SIXD_SRC     0x3A     /*6D source register*/
  #define REG_ALL_INT_SRC  0x3B     /*Reading this register, all related interrupt function flags routed to the INT pads are reset simultaneously*/
  
  #define REG_TAP_THS_X    0x30     /*4D configuration enable and TAP threshold configuration .*/
  #define REG_TAP_THS_Y    0x31     /*Threshold for tap recognition @ FS = ±2 g on Y direction*/
  #define REG_TAP_THS_Z    0x32     /*Threshold for tap recognition @ FS = ±2 g on Z direction*/
  #define REG_INT_DUR      0x33     /*Interrupt duration registe*/
  #define REG_WAKE_UP_THS  0x34     /*Wakeup threshold register*/

public:


/**
   Power mode
*/
typedef enum{
  
  eHighPerformance                   = 0x04, /**<High-Performance Mode>*/
  eContLowPwr_4                      = 0x03,/**<Continuous measurement,Low-Power Mode 4(14-bit resolution)>*/
  eContLowPwr_3                      = 0x02,/**<Continuous measurement,Low-Power Mode 3(14-bit resolution)>*/
  eContLowPwr_2                      = 0x01,/**<Continuous measurement,Low-Power Mode 2(14-bit resolution)>*/
  eContLowPwr_12bit                  = 0x00,/**<Continuous measurement,Low-Power Mode 1(12-bit resolution)>*/
  eSingleLowPwr_4                    = 0x0b,/**<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)>*/
  eSingleLowPwr_3                    = 0x0a,/**<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution)>*/
  eSingleLowPwr_2                    = 0x09,/**<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)>*/
  eSingleLowPwr_12bit                = 0x08,/**<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)>*/
  eHighPerformanceLowNoise           = 0x14,/**<High-Performance Mode,Low-noise enabled>*/
  eContLowPwrLowNoise_4              = 0x13,/**<Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)>*/
  eContLowPwrLowNoise_3              = 0x12,/**<Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)>*/
  eContLowPwrLowNoise_2              = 0x11,/**<Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)>*/
  eContLowPwrLowNoise_12bit          = 0x10,/**<Continuous measurement,Low-Power Mode 1(14-bit resolution,Low-noise enabled)>*/
  eSingleLowPwrLowNoise_4            = 0x1b,/**<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled>*/
  eSingleLowPwrLowNoise_3            = 0x1a,/**<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled>*/
  eSingleLowPwrLowNoise_2            = 0x19,/**<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled>*/
  eSingleLowLowNoisePwr_12bit        = 0x18,/**<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled>*/
}ePowerMode_t;

/**
  Sensor range
*/
typedef enum{
  e2_g     = 0, /**<±2g>*/
  e4_g     = 1, /**<±4g>*/
  e8_g     = 2, /**<±8g>*/
  e16_g    = 3, /**< ±16g>*/
}eRange_t;

/**
  Filtering mode
*/
typedef enum {
  eLpfOnOut        = 0x00,/**<Low pass filter>*/
  eHighPassOnOut   = 0x10,/**<High pass filter>*/
} eFds_t;

/**
   bandwidth of collected data
*/
typedef enum {
  eOdrDiv_2     = 0,/**<ODR/2 >*/
  eOdrDiv_4     = 1,/**<ODR/4 (High Power/Low power)>*/
  eOdrDiv_10    = 2,/**<ODR/10 (HP/LP)>*/
  eOdrDiv_20    = 3,/**< ODR/20 (HP/LP)>*/
}eBWfilter_t;

/**
  Data collection rate
*/
typedef enum {
  eOdr_0hz            = 0x00,
  eOdr_1hz6_lp_only   = 0x01,
  eOdr_12hz5          = 0x02,
  eOdr_25hz           = 0x03,
  eOdr_50hz           = 0x04,
  eOdr_100hz          = 0x05,
  eOdr_200hz          = 0x06,
  eOdr_400hz          = 0x07,
  eOdr_800hz          = 0x08,
  eOdr_1k6hz          = 0x09,
  eSetSwTrig          = 0x12,
  eSetPinTrig         = 0x22,
} eOdr_t;

/**
  Free fall threshold@ ±2 g FS
*/
typedef enum {
  eFfTsh5LSbFS2g  = 0, /**<5 LSB>*/
  eFfTsh7LSbFS2g  = 1, /**<7 LSB>*/
  eFfTsh8LSbFS2g  = 2, /**<8 LSB>*/
  eFfTsh10LSbFS2g = 3, /**<10 LSB>*/
  eFfTsh11LSbFS2g = 4, /**<11 LSB>*/
  eFfTsh13LSbFS2g = 5, /**<13 LSB>*/
  eFfTsh15LSbFS2g = 6, /**<15 LSB>*/
  eFfTsh16LSbFS2g = 7, /**<16 LSB>*/
} eFfThs_t;

/**
  Motion detection mode
*/
typedef enum {
  eNoDetection        = 0,/**<No detection>*/
  eDetectActInact     = 1,/**<Detect movement>*/
  eDetectStatMotion   = 3,/**<Detect Motion>*/
} eSleepOn_t;

/**
  Interrupt source 1 trigger event setting
*/
typedef enum{
  eDoubleTap   = 0x08,/**< Double-tap recognition is routed to INT1 pad>*/
  eFfEvent     = 0x10,/**< Free-fall recognition is routed to INT1 pad>*/
  eWakeupEvent = 0x20,/**<Wakeup recognition is routed to INT1 pad>*/
  eSingleTap   = 0x40,/**<Single-tap recognition is routed to INT1 pad.>*/
  eTnt16d      = 0x80,/**<6D recognition is routed to INT1 pad>*/
}eInt1Event_t;

/**
  Interrupt source 2 trigger event setting
*/
typedef enum{
  eBoot        = 0x20,/**< Boot state routed to INT2 pad.>*/
  eSleepChange = 0x40,/**<Enable routing of SLEEP_STATE on INT2 pad>*/
  eSleepState  = 0x80,/**<Sleep change status routed to INT2 pad>*/
}eInt2Event_t;

/**
  Click detection mode
*/
typedef enum {
  eOnlySingle          = 0,/**<Only detect click events.>*/
  eBothSingleDouble    = 1,/**<Both single-click and double-click events are detected.>*/
} sTapMode_t;

/**
  位置检测角度转变阈值
*/
typedef enum {
  eDegrees80          = 0,/**<80 degrees.>*/
  eDegrees70             ,/**<70 degrees.>*/
  eDegrees60             ,/**<60 degrees.>*/
  eDegrees50             ,/**<50 degrees.>*/
} s6dTH_t;

/**
  Click or double click
*/
typedef enum {
  eSingleClick  = 0 ,/**<click>*/
  eDoubleClick      ,/**<double click>*/
  eNoClick,
} eTap_t;

/**
  which direction is tap event detected
*/
typedef enum {
  eDirXup = 0,  /**<从 X 正方向发生的点击事件>*/
  eDirXdown = 1,/**<从 X 负方向发生的点击事件>*/
  eDirYup = 2,/**<从 Y 正方向发生的点击事件>*/
  eDirYdown = 3,/**<从 Y 负方向发生的点击事件>*/
  eDirZup = 4,/**<从 Z 正方向发生的点击事件>*/
  eDirZdown = 5,/**<从 Z 负方向发生的点击事件>*/
  eDirNone,
}eTapDir_t;

/**
  which direction is wake up event detected
*/
typedef enum {
  eDirX = 0,/**<X方向的运动唤醒芯片>*/
  eDirY = 1,/**<Y方向的运动唤醒芯片>*/
  eDirZ = 2,/**<Z方向的运动唤醒芯片>*/
  eDirError,
}eWakeupDir_t;

/**
  orientation
*/
typedef enum {
  eXdown = 0,/**<X is now down>*/
  eXup  = 1 ,/**<X is now up>*/
  eYdown = 2 ,/**<Y is now down>*/
  eYup = 3 , /**<Y is now up>*/
  eZdown = 4 , /**<Z is now down>*/
  eZup = 5 , /**<Z is now up>*/
} eOrient_t;
public:
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
   * @return  Acceleration data from x(mg)
   */
  float readAccX();
  
  /**
   * @brief Read the acceleration in the y direction
   * @return  Acceleration data from y(mg)
   */
  float readAccY();
  
  /**
   * @brief Read the acceleration in the z direction
   * @return  Acceleration data from z(mg)
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

protected:

  /**
   * @brief read data from sensor chip register
   * @param reg chip register 
   * @param pBuf  buf for store data to read 
   * @param size  number of data to read
   * @return 成功读数据的个数
   */
  virtual uint8_t readReg(uint8_t reg,uint8_t * pBuf ,size_t size) = 0;
  
  /**
   * @brief Write data to sensor register 
   * @param reg register
   * @param pBuf  buf for store data to write 
   * @param size  The number of the data in pBuf
   * @return 成功发送数据的个数
   */
  virtual uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size)= 0; 
  uint8_t _interface = 0;
  float   _range     = e2_g;
  uint8_t _range1    = 0;
private:

  /**
   * @brief set quiet time after a tap detection: this register represents
     @n the time after the first detected tap in which there must not be any overthreshold event.
   * @param quiet quiet time
   */
  void setTapQuiet(uint8_t quiet);
  
  /**
   * @brief Set the maximum time of an over-threshold signal detection to be recognized as a tap event.
   * @param shock  shock time
   */
  void setTapShock(uint8_t shock);
  
  /**
   * @brief Set 6d filtered data source
   * @param data 0: ODR/2 low pass filtered data sent to 6D interrupt function (default)
                 1: LPF2 output data sent to 6D interrupt function)
   */
  void set6dFeedData(uint8_t data);
  
  /**
   * @brief Set Free-fall threshold
   * @param th threshold
   */
  void setFfThreshold(eFfThs_t th);
  
  /**
   * @brief Set duration to go in sleep mode.
   * @param dur  duration
   */
  void setActSleepDur(uint8_t dur);
};

class DFRobot_IIS2DLPC_I2C : public DFRobot_LIS2DW12{
public:
  /*!
   * @brief Constructor 
   * @param pWire I2c controller
   * @param addr  I2C address(0x19/0x18)
   */
  DFRobot_IIS2DLPC_I2C(TwoWire * pWire = &Wire,uint8_t addr = IIS2DLPC_I2C_ADDR);
  /**
   * @brief init function
   * @return Return 1 if initialization succeeds, otherwise return non-zero and error code.
   */
  uint8_t begin(void);

protected:

  /**
   * @brief read data from sensor chip register
   * @param reg chip register 
   * @param pBuf  buf for store data to read 
   * @param size  number of data to read
   * @return 成功读数据的个数
   */
  uint8_t readReg(uint8_t reg,uint8_t * pBuf ,size_t size);
  
  /**
   * @brief Write data to sensor register 
   * @param reg register
   * @param pBuf  buf for store data to write 
   * @param size  The number of the data in pBuf
   * @return 成功发送数据的个数
   */
  uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size); 
private:
    uint8_t _deviceAddr;
    TwoWire *_pWire;
};

class DFRobot_IIS2DLPC_SPI : public DFRobot_LIS2DW12{

public:
  /*!
   * @brief Constructor 
   * @param cs : Chip selection pinChip selection pin
   * @param spi :SPI controller
   */
  DFRobot_IIS2DLPC_SPI(uint8_t cs = 3,SPIClass *spi=&SPI);
  
  /**
   * @brief init function
   * @return Return 1 if initialization succeeds, otherwise return non-zero and error code.
   */
  uint8_t begin(void);
protected:

  /**
   * @brief read data from sensor chip register
   * @param reg chip register 
   * @param pBuf  buf for store data to read 
   * @param size  number of data to read
   * @return 成功读数据的个数
   */
  uint8_t readReg(uint8_t reg,uint8_t * pBuf ,size_t size);
  
  /**
   * @brief Write data to sensor register 
   * @param reg register
   * @param pBuf  buf for store data to write 
   * @param size  The number of the data in pBuf
   * @return 成功发送数据的个数
   */
  uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size); 
private:
    SPIClass *_pSpi;
    uint8_t _cs = 0;
};

class DFRobot_LIS2DW12_I2C : public DFRobot_LIS2DW12{
public:
  /*!
   * @brief Constructor 
   * @param pWire I2c controller
   * @param addr  I2C address(0x19/0x18)
   */
  DFRobot_LIS2DW12_I2C(TwoWire * pWire = &Wire,uint8_t addr = LIS2DW12_I2C_ADDR);
  
  /**
   * @brief init function
   * @return Return 1 if initialization succeeds, otherwise return non-zero and error code.
   */
  uint8_t begin(void);

protected:
  
  /**
   * @brief read data from sensor chip register
   * @param reg chip register 
   * @param pBuf  buf for store data to read 
   * @param size  number of data to read
   * @return 成功读数据的个数
   */
  uint8_t readReg(uint8_t reg,uint8_t * pBuf ,size_t size);

  /**
   * @brief Write data to sensor register 
   * @param reg register
   * @param pBuf  buf for store data to write 
   * @param size  The number of the data in pBuf
   * @return 成功发送数据的个数
   */
  uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size); 
private:
    uint8_t _deviceAddr;
    TwoWire *_pWire;
};

class DFRobot_LIS2DW12_SPI : public DFRobot_LIS2DW12{

public:
  /*!
   * @brief Constructor 
   * @param cs : Chip selection pinChip selection pin
   * @param spi :SPI controller
   */
  DFRobot_LIS2DW12_SPI(uint8_t cs = 3,SPIClass *spi=&SPI);
  
  /**
   * @brief init function
   * @return Return 1 if initialization succeeds, otherwise return non-zero and error code.
   */
  uint8_t begin(void);
protected:

  /**
   * @brief read data from sensor chip register
   * @param reg chip register 
   * @param pBuf  buf for store data to read 
   * @param size  number of data to read
   * @return 成功读数据的个数
   */
  uint8_t readReg(uint8_t reg,uint8_t * pBuf ,size_t size);
  
  /**
   * @brief Write data to sensor register 
   * @param reg register
   * @param pBuf  buf for store data to write 
   * @param size  The number of the data in pBuf
   * @return 成功发送数据的个数
   */
  uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size); 
private:
    SPIClass *_pSpi;
    uint8_t _cs = 0;
};
#endif